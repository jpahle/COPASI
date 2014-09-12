// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CStochDirectMethod
#define COPASI_CStochDirectMethod

#include <set>
#include <vector>

#include "copasi/trajectory/CTrajectoryMethod.h"
#include "copasi/trajectory/CStochMethod.h"
#include "copasi/utilities/CDependencyGraph.h"
#include "copasi/model/CState.h"

class CModel;
class CMetab;
class CTrajectoryProblem;
class CRandom;
class CMathReaction;
class FDescent;

class CStochDirectMethod : public CTrajectoryMethod
{
  friend CTrajectoryMethod *
  CTrajectoryMethod::createMethod(CCopasiMethod::SubType subType);

private:
protected:
  /**
   * Default constructor.
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CStochDirectMethod(const CCopasiContainer * pParent = NULL);

  /**
   * Fire the next reaction if it fire before the endTime
   * @param C_FLOAT64 startTime
   * @param const C_FLOAT64 & endTime
   * @return C_FLOAT64 deltaT
   */
  C_FLOAT64 doSingleStep(C_FLOAT64 startTime, const C_FLOAT64 & endTime);

public:
  /**
   * Copy constructor.
   * @param const CStochDirectMethod & src,
   * @param const CCopasiContainer * pParent (Default: NULL)
   */
  CStochDirectMethod(const CStochDirectMethod & src,
                     const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  ~CStochDirectMethod();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  /**
   *  This instructs the method to calculate a time step of deltaT
   *  starting with the current state, i.e., the result of the previous
   *  step.
   *  The new state (after deltaT) is expected in the current state.
   *  The return value is the actual timestep taken.
   *  @param "const double &" deltaT
   *  @return Status status
   */
  virtual Status step(const double & deltaT);

  /**
   *  This instructs the method to prepare for integration
   *  starting with the initialState given.
   *  @param "const CState *" initialState
   */
  virtual void start(CVectorCore< C_FLOAT64 > & initialState);

  /**
  * Check if the method is suitable for this problem
  * @return bool suitability of the method
  */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

  /**
   * Inform the trajectory method that the state has changed outside
   * its control
   * @param const CMath::StateChange & change
   */
  virtual void stateChange(const CMath::StateChange & change);

  /**
   * Calculate the root value for the given time
   * @param const C_FLOAT64 & time
   * @return const C_FLOAT64 rootValue
   */
  C_FLOAT64 rootValue(const C_FLOAT64 & time);

private:
  /**
   * Initialize the method parameter
   */
  void initializeParameter();

  /**
   * Check whether finds a root
   */
  bool checkRoots();

protected:

  /**
   * The random number generator
   */
  CRandom *mpRandomGenerator;

  /**
   * The particle and reaction numbers
   */
  size_t mNumReactions;

  /**
   * the number of internal steps to done in one step()
   */
  size_t mSteps;

  /**
   * max number of single stochastic steps to do in one step()
   */
  size_t mMaxSteps;

  /**
   * The time the next reaction fires
   */
  C_FLOAT64 mNextReactionTime;

  /**
   * The index of the next reaction which fires
   */
  size_t mNextReactionIndex;

  /**
   * Total propensity (sum over mAmu[i])
   */
  C_FLOAT64 mA0;

  /**
   * A vector referencing the math container's reactions
   */
  CVectorCore< CMathReaction > mReactions;

  /**
   * A vector referencing the math container's propensity objects
   */
  CVectorCore< CMathObject > mPropensityObjects;

  /**
   * A vector referencing the math container's propensity values
   */
  CVectorCore< C_FLOAT64 > mAmu;

  /**
   * A vector containing the update sequence required to update all propensity values.
   */
  CVector< CObjectInterface::UpdateSequence > mUpdateSequences;

  /**
   * The sequence required to update time dependent roots.
   */
  CObjectInterface::UpdateSequence mUpdateTimeDependentRoots;

  /**
   * Boolean value indicating whether we have time dependent roots
   */
  bool mHaveTimeDependentRoots;

  /**
   * Functor pointing to the Brent root finding method.
   */
  FDescent * mpRootValueCalculator;

  /**
   * A boolean flag indicating whether the maximum steps have been reached. This
   * is used to avoid multiple messages.
   */
  bool mMaxStepsReached;

  /**
   * The status of the integrator
   */
  Status mStatus;

  //========Arguments for Roots========
  /**
   * A double value recording time at which step() stops
   */
  C_FLOAT64 mTargetTime;

  /**
   * An integer, referring number of roots
   */
  size_t mNumRoot;

  /**
   * 2 Vector for storing root value
   */
  CVector< C_FLOAT64 > mRootsA;
  CVector< C_FLOAT64 > mRootsB;
  CVector< C_FLOAT64 > mRootsNonZero;

  /**
   * Pointer to the vector holding the previously calculated roots
   */
  CVector< C_FLOAT64 > *mpRootValueOld;

  /**
   * Pointer to the vector holding the newly calculated roots
   */
  CVector< C_FLOAT64 > *mpRootValueNew;
};

#endif // COPASI_CStochDirectMethod
