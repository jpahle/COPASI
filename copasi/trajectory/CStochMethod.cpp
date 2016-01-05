// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
#endif  // WIN32

#include <limits.h>

#include <vector>
#include <numeric>
#include <limits>
#include <set>

#include "copasi.h"
#include "CStochMethod.h"
#include "CStochDirectMethod.h"
#include "CStochNextReactionMethod.h"
#include "utilities/CCopasiVector.h"
#include "function/CFunction.h"
#include "randomGenerator/CRandom.h"
#include "CTrajectoryMethod.h"
#include "CTrajectoryProblem.h"
#include "math/CMathContainer.h"
#include "math/CMathReaction.h"
#include "model/CModel.h"

C_INT32 CStochMethod::checkModel(CModel * C_UNUSED(pmodel))
{
  // Here several checks will be performed to validate the model
  return 2; // suggest next reaction method
}

CStochMethod::CStochMethod(const CCopasiContainer * pParent,
                           const CTaskEnum::Method & methodType,
                           const CTaskEnum::Task & taskType):
  CTrajectoryMethod(pParent, methodType, taskType),
  mpRandomGenerator(NULL),
  mA0(0.0),
  mNumReactions(0),
  mReactions(),
  mPropensityObjects(),
  mAmu(),
  mUpdateSequences(),
  mMaxSteps(0),
  mMaxStepsReached(false),
  mNextReactionTime(0.0),
  mNextReactionIndex(C_INVALID_INDEX),
  mNumReactionSpecies(0),
  mFirstReactionSpeciesIndex(C_INVALID_INDEX),
  mDG()
{
  initializeParameter();
  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
}

CStochMethod::CStochMethod(const CStochMethod & src,
                           const CCopasiContainer * pParent):
  CTrajectoryMethod(src, pParent),
  mpRandomGenerator(NULL),
  mA0(0.0),
  mNumReactions(0),
  mReactions(),
  mPropensityObjects(),
  mAmu(),
  mUpdateSequences(),
  mMaxSteps(0),
  mMaxStepsReached(false),
  mNextReactionTime(0.0),
  mNextReactionIndex(C_INVALID_INDEX),
  mNumReactionSpecies(0),
  mFirstReactionSpeciesIndex(C_INVALID_INDEX),
  mDG()
{
  initializeParameter();
  mpRandomGenerator = CRandom::createGenerator(CRandom::mt19937);
}

CStochMethod::~CStochMethod()
{}

void CStochMethod::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Max Internal Steps", CCopasiParameter::INT, (C_INT32) 1000000);
  assertParameter("Subtype", CCopasiParameter::UINT, (unsigned C_INT32) 2);
  assertParameter("Use Random Seed", CCopasiParameter::BOOL, false);
  assertParameter("Random Seed", CCopasiParameter::UINT, (unsigned C_INT32) 1);

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("STOCH.MaxSteps")) != NULL)
    {
      setValue("Max Internal Steps", pParm->getValue< C_INT32 >());
      removeParameter("STOCH.MaxSteps");

      if ((pParm = getParameter("STOCH.Subtype")) != NULL)
        {
          setValue("Subtype", pParm->getValue< unsigned C_INT32 >());
          removeParameter("STOCH.Subtype");
        }

      if ((pParm = getParameter("STOCH.UseRandomSeed")) != NULL)
        {
          setValue("Use Random Seed", pParm->getValue< bool >());
          removeParameter("STOCH.UseRandomSeed");
        }

      if ((pParm = getParameter("STOCH.RandomSeed")) != NULL)
        {
          setValue("Random Seed", pParm->getValue< unsigned C_INT32 >());
          removeParameter("STOCH.RandomSeed");
        }
    }
}

bool CStochMethod::elevateChildren()
{
  initializeParameter();
  return true;
}

CTrajectoryMethod::Status CStochMethod::step(const double & deltaT)
{
  // write the current state to the model:
  //mpProblem->getModel()->setState(mpCurrentState); //?

  // check for possible overflows:
  size_t i;
  size_t imax;

  // do several steps:
  C_FLOAT64 time = *mpContainerStateTime;
  C_FLOAT64 endtime = time + deltaT;

  size_t Steps = 0;

  while (time < endtime)
    {
      time = doSingleStep(time, endtime);
      *mpContainerStateTime = time;

      if (++Steps > mMaxSteps)
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 12);
        }

      if (mpProblem->getAutomaticStepSize()) break;
    }

  *mpContainerStateTime = time;

  return NORMAL;
}

void CStochMethod::start()
{
  CTrajectoryMethod::start();

  mpRandomGenerator = &mpContainer->getRandomGenerator();

  bool useRandomSeed = getValue< bool >("Use Random Seed");
  unsigned C_INT32 randomSeed = getValue< unsigned C_INT32 >("Random Seed");

  if (useRandomSeed) mpRandomGenerator->initialize(randomSeed);

  mMaxSteps = getValue< C_INT32 >("Max Internal Steps");

  //initialize the vector of ints that contains the particle numbers
  //for the discrete simulation. This also floors all particle numbers in the model.

  // Size the arrays
  mReactions.initialize(mpContainer->getReactions());
  mNumReactions = mReactions.size();
  mAmu.initialize(mpContainer->getPropensities());
  mPropensityObjects.initialize(mAmu.size(), mpContainer->getMathObject(mAmu.array()));
  mUpdateSequences.resize(mNumReactions);

  CMathReaction * pReaction = mReactions.array();
  CMathReaction * pReactionEnd = pReaction + mNumReactions;
  CObjectInterface::UpdateSequence * pUpdateSequence = mUpdateSequences.array();
  CMathObject * pPropensityObject = mPropensityObjects.array();
  CMathObject * pPropensityObjectEnd = pPropensityObject + mPropensityObjects.size();
  CObjectInterface::ObjectSet Requested;

  for (; pPropensityObject != pPropensityObjectEnd; ++pPropensityObject)
    {
      Requested.insert(pPropensityObject);
    }

  CObjectInterface::ObjectSet Changed;
  CObjectInterface * pTimeObject = mpContainer->getMathObject(mpContainerStateTime);
  pPropensityObject = mPropensityObjects.array();

  for (; pReaction  != pReactionEnd; ++pReaction, ++pUpdateSequence, ++pPropensityObject)
    {
      Changed = pReaction->getChangedObjects();

      // The time is always updated
      Changed.insert(pTimeObject);

      pUpdateSequence->clear();
      mpContainer->getTransientDependencies().getUpdateSequence(*pUpdateSequence, CMath::Default, Changed, Requested);
    }

  mNumReactionSpecies = mpContainer->getCountIndependentSpecies() + mpContainer->getCountDependentSpecies();
  mFirstReactionSpeciesIndex = mpContainer->getCountFixedEventTargets() + mpContainer->getCountODEs();

  C_FLOAT64 * pSpecies = mContainerState.array() + mFirstReactionSpeciesIndex;
  C_FLOAT64 * pSpeciesEnd = pSpecies + mNumReactionSpecies;

  for (; pSpecies != pSpeciesEnd; ++pSpecies)
    {
      *pSpecies = floor(*pSpecies + 0.5);
    }

  // The container state is now up to date we just need to calculate all values needed for simulation.
  mpContainer->updateSimulatedValues(false); //for assignments

  pPropensityObject = mPropensityObjects.array();
  C_FLOAT64 * pAmu = mAmu.array();
  mA0 = 0.0;

  // Update the propensity
  for (; pPropensityObject != pPropensityObjectEnd; ++pPropensityObject, ++pAmu)
    {
      pPropensityObject->calculateValue();
      mA0 += *pAmu;
    }

  mMaxStepsReached = false;
  mNextReactionTime = *mpContainerStateTime;
  mNextReactionIndex = C_INVALID_INDEX;

  setupDependencyGraph();

  initMethod();
}

size_t CStochMethod::generateReactionIndex()
{
  C_FLOAT64 sum = 0.0;
  C_FLOAT64 rand = mpRandomGenerator->getRandomOO() * mA0;

  const C_FLOAT64 * pAmu = mAmu.array();
  const C_FLOAT64 * pAmuEnd = pAmu + mNumReactions;

  for (; (sum < rand) && (pAmu != pAmuEnd); ++pAmu, ++mNextReactionIndex)
    {
      sum += *pAmu;
    }

  mNextReactionIndex--;

  return mNextReactionIndex;
}

C_FLOAT64 CStochMethod::generateReactionTime()
{
  if (mA0 == 0) return std::numeric_limits<C_FLOAT64>::infinity();

  C_FLOAT64 rand2 = mpRandomGenerator->getRandomOO();
  return - 1 * log(rand2) / mA0;
}

C_FLOAT64 CStochMethod::generateReactionTime(size_t reaction_index)
{
  if (mAmu[reaction_index] == 0) return std::numeric_limits<C_FLOAT64>::infinity();

  C_FLOAT64 rand2 = mpRandomGenerator->getRandomOO();
  return - 1 * log(rand2) / mAmu[reaction_index];
}

void CStochMethod::setupDependencyGraph()
{
  mDG.clear();

  CObjectInterface::ObjectSet Requested;
  CObjectInterface::UpdateSequence UpdateSequence;

  const CMathReaction * pReaction = mReactions.array();
  const CMathReaction * pReactionEnd = pReaction + mReactions.size();
  const CMathObject * pPropensity = mPropensityObjects.array();
  const CMathObject * pPropensityEnd = pPropensity + mPropensityObjects.size();

  for (size_t i = 0; pReaction != pReactionEnd; ++pReaction, ++i)
    {
      size_t j = 0;
      pPropensity = mPropensityObjects.array();

      for (; pPropensity != pPropensityEnd; ++pPropensity, ++j)
        {
          mpContainer->getTransientDependencies().getUpdateSequence(UpdateSequence, CMath::Default, pReaction->getChangedObjects(), Requested);

          if (UpdateSequence.size() > 0)
            {
              mDG.addDependent(i, j);
            }
        }
    }
}

//virtual
bool CStochMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CTrajectoryMethod::isValidProblem(pProblem)) return false;

  const CTrajectoryProblem * pTP = dynamic_cast<const CTrajectoryProblem *>(pProblem);

  if (pTP->getDuration() < 0.0)
    {
      //back integration not possible
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 9);
      return false;
    }

  // check for ODEs
  if (mpContainer->getCountODEs() > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 28);
    }

  //TODO: rewrite CModel::suitableForStochasticSimulation() to use
  //      CCopasiMessage
  std::string message = mpContainer->getModel().suitableForStochasticSimulation();

  if (message != "")
    {
      //model not suitable, message describes the problem
      CCopasiMessage(CCopasiMessage::ERROR, message.c_str());
      return false;
    }

  if (getValue< C_INT32 >("Max Internal Steps") <= 0)
    {
      //max steps should be at least 1
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 15);
      return false;
    }

  return true;
}
