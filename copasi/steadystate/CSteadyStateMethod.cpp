/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CSteadyStateMethod.cpp,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/09 12:15:49 $
   End CVS Header */

/**
 *  CSteadyStateMethod class.
 *  This class describes the interface to all steady state methods.
 *  The variaous method like Newton have to be derived from
 *  this class.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"

#include "utilities/CCopasiVector.h"
#include "CSteadyStateMethod.h"
#include "CSteadyStateProblem.h"
#include "CEigen.h"

#include "model/CModel.h"
#include "model/CState.h"
#include "model/CCompartment.h"

CSteadyStateMethod *
CSteadyStateMethod::createSteadyStateMethod(CCopasiMethod::SubType subType)
{
  CSteadyStateMethod * pMethod = NULL;

  switch (subType)
    {
    case unset:
    case Newton:
      pMethod = new CNewtonMethod();
      break;

    default:
      fatalError();
    }

  return pMethod;
}

/**
 *  Default constructor.
 */
CSteadyStateMethod::CSteadyStateMethod(CCopasiMethod::SubType subType,
                                       const CCopasiContainer * pParent):
    CCopasiMethod(CCopasiTask::steadyState, subType, pParent),
    mpProblem(NULL)
{CONSTRUCTOR_TRACE;}

/**
 *  Copy constructor.
 *  @param "const CSteadyStateMethod &" src
 */
CSteadyStateMethod::CSteadyStateMethod(const CSteadyStateMethod & src,
                                       const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent),
    mpProblem(src.mpProblem)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CSteadyStateMethod::~CSteadyStateMethod()
{DESTRUCTOR_TRACE;}

/**
 *  Set a pointer to the problem.
 *  This method is used by CSteadyState 
 *  @param "CSteadyStateProblem *" problem
 */ 
//void CSteadyStateMethod::setProblem(CSteadyStateProblem * problem)
//{mpProblem = problem;}

/**
 * This instructs the method to calculate a the steady state
 * starting with the initialState given.
 * The steady state is returned in the object pointed to by steadyState.
 * @param CState * steadyState
 * @param const CState * initialState
 * @param C_FLOAT64 * jacobian
 * @param CEigen * eigenValues
 * @return CSteadyStateMethod::ReturnCode returnCode
 */
CSteadyStateMethod::ReturnCode
CSteadyStateMethod::process(CState * pState,
                            const CSteadyStateProblem * pProblem,
                            CMatrix< C_FLOAT64 > & jacobian,
                            CEigen * pEigenValues)
{
  mpSteadyState = pState;
  mpProblem = pProblem;
  mpJacobian = & jacobian;
  mpEigenValues = pEigenValues;

  return processInternal();
}

/**
 * This function has to be called at the return of any implementation
 * of the protected function process
 * @param bool success
 * @param const C_FLOAT64 & factor
 * @param const C_FLOAT64 & resolution
 * @return CSteadyStateMethod::ReturnCode returnCode
 */
CSteadyStateMethod::ReturnCode
CSteadyStateMethod::returnProcess(bool steadyStateFound,
                                  const C_FLOAT64 & factor,
                                  const C_FLOAT64 & resolution)
{
  mpProblem->getModel()->setTransitionTimes();

  if (mpProblem->isJacobianRequested() ||
      mpProblem->isStabilityAnalysisRequested())
    mpSteadyState->calculateJacobian(*mpJacobian, factor, resolution);

  /* hack to force the model to reflect the solution */
  CVector< C_FLOAT64 > Derivatives(mpSteadyState->getVariableNumberSize());
  mpProblem->getModel()->getDerivatives_particles(mpSteadyState, Derivatives);

  if (mpProblem->isStabilityAnalysisRequested())
    {
      mpEigenValues->calcEigenValues(*mpJacobian);
      mpEigenValues->stabilityAnalysis(resolution);
    }

  if (!steadyStateFound)
    return CSteadyStateMethod::notFound;

  if (steadyStateFound && isEquilibrium(resolution))
    return CSteadyStateMethod::foundEquilibrium;

  return CSteadyStateMethod::found;
}

/**
 * This instructs the method to calculate a the steady state
 * starting with the initialState given.
 * The steady state is returned in the object pointed to by steadyState.
 * @param CState * steadyState
 * @param const CState * initialState
 * @return CSteadyStateMethod::ReturnCode returnCode
 */
CSteadyStateMethod::ReturnCode
CSteadyStateMethod::processInternal()
{return CSteadyStateMethod::notFound;}

bool CSteadyStateMethod::isEquilibrium(const C_FLOAT64 & resolution)
{
  const CCopasiVectorNS < CReaction > & Reaction =
    mpProblem->getModel()->getReactions();
  unsigned C_INT32 i, imax = Reaction.size();

  for (i = 0; i < imax; i++)
    if (Reaction[i]->getFlux() > resolution)
      return false;

  return true;
}
