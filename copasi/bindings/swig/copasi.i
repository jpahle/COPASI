%module COPASI

%{

#define COPASI_MAIN
#include "copasi.h"
#undef COPASI_MAIN

%}

%import "copasi.h"

%include std_string.i
%include std_vector.i

%include "CCopasiObjectName.i"
%include "CCopasiObject.i"
%include "CCopasiContainer.i"
%include "CCopasiParameter.i"
%include "CCopasiParameterGroup.i"
%include "CMoiety.i"
%include "CModelValue.i"
%include "CMetab.i"
%include "CCompartment.i"
%include "CCopasiVector.i"
%include "CMatrix.i"
%include "CState.i"
%include "CReaction.i"
%include "CModel.i"
%include "CVersion.i"
%include "CCopasiMethod.i"
%include "CCopasiProblem.i"
%include "CCopasiTask.i"
%include "CCopasiDataModel.i"
%include "CTimeSeries.i"
%include "CTrajectoryProblem.i"
%include "CTrajectoryMethod.i"
%include "CTrajectoryTask.i"

%init %{

#include "report/CCopasiContainer.h"
// Taken from CopasiSE.cpp

// Create the root container
CCopasiContainer::init();

// Create the global data model
CCopasiDataModel::Global = new CCopasiDataModel;

%}

