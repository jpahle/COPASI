// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/csharp/csharp.i,v $
//   $Revision: 1.1.2.7 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2011/09/28 12:42:51 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * Make COPASI and wrapper constants Mono compile-time
 * constants so they may be used in switch statements.
 */
%include "enumsimple.swg"
%csconst(1);


void initCopasi();

%inline %{

enum CLASS_TYPE
{
  UNDEFINED_CLASS_TYPE
  , AnnotatedFloatMatrix_Type
  , CArrayAnnotation_Type
  , CBiologicalDescription_Type
  , CChemEqElementVector_Type
  , CChemEqElement_Type
  , CChemEq_Type
  , CCompartment_Type
  , CCopasiArray_Type
  , CCopasiAbstractArray_Type
  , CCopasiContainer_Type
  , CCopasiDataModel_Type
  , CCopasiMethod_Type
  , CCopasiObject_Type
  , CCopasiParameterGroup_Type
  , CCopasiParameter_Type
  , CCopasiProblem_Type
  , CCopasiReportSeparator_Type
  , CCopasiRootContainer_Type
  , CCopasiStaticString_Type
  , CCopasiTask_Type
  , CCreator_Type
  , CEvaluationTreeVectorN_Type
  , CEvaluationTreeVector_Type
  , CEvaluationTree_Type
  , CEventAssignment_Type
  , CEvent_Type
  , CExperimentObjectMap_Type
  , CExperimentSet_Type
  , CExperiment_Type
  , CFitConstraint_Type
  , CFitItem_Type
  , CFitMethod_Type
  , CFitProblem_Type
  , CFitTask_Type
  , CFittingPoint_Type
  , CFunctionDB_Type
  , CFunctionParameter_Type
  , CFunctionParameters_Type
  , CFunction_Type
  , CLyapMethod_Type
  , CLyapProblem_Type
  , CLyapTask_Type
  , CMCAMethod_Type
  , CMCAProblem_Type
  , CMCATask_Type
  , CMIRIAMInfo_Type
  , CMetab_Type
  , CModelEntity_Type
  , CModelValue_Type
  , CModel_Type
  , CModification_Type
  , CMoiety_Type
  , CNewtonMethod_Type
  , COptItem_Type
  , COptMethod_Type
  , COptProblem_Type
  , COptTask_Type
  , CReaction_Type
  , CReference_Type
  , CReportDefinition_Type
  , CScanMethod_Type
  , CScanProblem_Type
  , CScanTask_Type
  , CSensMethod_Type
  , CSensProblem_Type
  , CSensTask_Type
  , CSteadyStateMethod_Type
  , CSteadyStateProblem_Type
  , CSteadyStateTask_Type
  , CTrajectoryMethod_Type
  , CTrajectoryProblem_Type
  , CTrajectoryTask_Type
  , CompartmentVectorNS_Type
  , CompartmentVectorN_Type
  , CompartmentVector_Type
  , EventAssignmentVectorN_Type
  , EventAssignmentVector_Type
  , EventVectorN_Type
  , EventVector_Type
  , MetabVectorNS_Type
  , MetabVectorN_Type
  , MetabVector_Type
  , ModelValueVectorN_Type
  , ModelValueVector_Type
  , MoietyVector_Type
  , ReactionVectorNS_Type
  , ReactionVectorN_Type
  , ReactionVector_Type
  , ReportDefinitionVectorN_Type
  , ReportDefinitionVector_Type
  , TaskVectorN_Type
  , TaskVector_Type
};

class CCompartment;
class CCopasiAbstractArray;
class CCopasiArray;
class CCopasiContainer;
class CCopasiMethod;
class CCopasiObject;
class CCopasiParameter;
class CCopasiParameterGroup;
class CCopasiProblem;
class CCopasiRootContainer;
class CCopasiTask;
class CCopasiTask;
class CEvaluationTree;
class CFitConstraint;
class CFitItem;
class CFitMethod;
class CFitProblem;
class CModelEntity;
class COptItem;
class COptMethod;
class COptProblem;
class COptTask;
class CTrajectoryTask;

// Determine type CCopasiAbstractArray
int GetType_CCopasiAbstractArray(CCopasiAbstractArray* pPointer);

// Determine type for CCopasiContainer
int GetType_CCopasiContainer(CCopasiContainer* pPointer);

// Determine type for CCopasiMethod
int GetType_CCopasiMethod(CCopasiMethod* pPointer);

// Determine type for CCopasiObject
int GetType_CCopasiObject(CCopasiObject* pPointer);

// Determine type for CCopasiParameter
int GetType_CCopasiParameter(CCopasiParameter* pPointer);

// Determine type for CCopasiParameterGroup
int GetType_CCopasiParameterGroup(CCopasiParameterGroup* pPointer);

// Determine type for CCopasiProblem
int GetType_CCopasiProblem(CCopasiProblem* pPointer);

// Determine type for CCopasiTask
int GetType_CCopasiTask(CCopasiTask* pPointer);

// Determine type for CEvaluationTree
int GetType_CEvaluationTree(CEvaluationTree* pPointer);

// Determine type for CFitItem
int GetType_CFitItem(CFitItem* pPointer);

// Determine type for CModelEntity
int GetType_CModelEntity(CModelEntity* pPointer);

// Determine type for COptItem
int GetType_COptItem(COptItem* pPointer);

// Determine type for COptMethod
int GetType_COptMethod(COptMethod* pPointer);

// Determine type for COptProblem
int GetType_COptProblem(COptProblem* pPointer);

// Determine type for COptTask
int GetType_COptTask(COptTask* pPointer);


%}



// The build system has to call SWIG with the -DSWIG_CSHARP_NO_IMCLASS_STATIC_CONSTRUCTOR
// otherwise newer versions of SWIG will create a static constructor which conflicts with
// the one below
// Since I have no clue about C#, I don't know any other way to make sure that initCopasi
// is called when the module is loaded
%pragma(csharp) imclasscode=
%{

    // the static constructor
    // initializes the COPASI backend
    static $imclassname() {
        initCopasi();
    }

    // typecasting code for polymorphic classes
    // This follows the solution suggested by John McGehee
    // detailed at http://www.voom.net/swig-csharp-java-downcast

    // To make it more efficient I use several methods instead 
    // of just one as described there.

    // CEvaluationTree
    public static CEvaluationTree InstantiateConcrete_CEvaluationTree(IntPtr cPtr, bool owner)
    {
        CEvaluationTree ret = null;
        if (cPtr == IntPtr.Zero) {
            return ret;
        }
        int type = $modulePINVOKE.GetType_CEvaluationTree(new HandleRef(null, cPtr));
        switch (type) {
            case COPASI.UNDEFINED_CLASS_TYPE:
                break;
            case COPASI.CFunction_Type:
                ret = new CFunction(cPtr, owner);
                break;
            case COPASI.CEvaluationTree_Type:
                ret = new CEvaluationTree(cPtr, owner);
                break;
            default:
                System.Diagnostics.Debug.Assert(false,
                        String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                            type.ToString()));
                break;
        }
        return ret;
    }

    // CFitItem
    public static CFitItem InstantiateConcrete_CFitItem(IntPtr cPtr, bool owner)
    {
        CFitItem ret = null;

        if (cPtr != IntPtr.Zero)
        {
            int type = $modulePINVOKE.GetType_CFitItem(new HandleRef(null, cPtr));
            switch(type)
            {
                case COPASI.UNDEFINED_CLASS_TYPE:
                    break;
                case COPASI.CFitConstraint_Type:
                    ret = new CFitConstraint(cPtr, owner);
                    break;
                case COPASI.CEvaluationTree_Type:
                    ret = new CFitItem(cPtr, owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }


    // CModelEntity
    public static CModelEntity InstantiateConcrete_CModelEntity(IntPtr cPtr, bool owner)
    {
        CModelEntity ret = null;

        if (cPtr != IntPtr.Zero)
        {
            int type = $modulePINVOKE.GetType_CModelEntity(new HandleRef(null, cPtr));
            switch(type)
            {
                case COPASI.UNDEFINED_CLASS_TYPE:
                    break;
                case COPASI.CCompartment_Type:
                    // return a CCompartment
                    ret = new CCompartment(cPtr,owner);
                    break;
                case COPASI.CMetab_Type:
                    // return a CMetab
                    ret = new CMetab(cPtr,owner);
                        break;
                case COPASI.CModel_Type:
                    // return a CModel
                    ret = new CModel(cPtr,owner);
                    break;
                case COPASI.CModelValue_Type:
                    // return a CModelValue
                    ret = new CModelValue(cPtr,owner);
                    break;
                case COPASI.CModelEntity_Type:
                    // return a CModelEntity
                    ret = new CModelEntity(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }


    // COptItem
    public static COptItem InstantiateConcrete_COptItem(IntPtr cPtr, bool owner)
    {
        COptItem ret = null;

        if (cPtr != IntPtr.Zero)
        {
            int type = $modulePINVOKE.GetType_COptItem(new HandleRef(null, cPtr));
            switch(type)
            {
                case COPASI.UNDEFINED_CLASS_TYPE:
                    break;
                case COPASI.CFitItem_Type:
                    // return a CFitItem
                    ret = InstantiateConcrete_CFitItem(cPtr,owner);
                    break;
                case COPASI.COptItem_Type:
                    // return a COptItem
                    ret = new COptItem(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }

    // COptMethod
    public static COptMethod InstantiateConcrete_COptMethod(IntPtr cPtr, bool owner)
    {
        COptMethod ret = null;

        if (cPtr != IntPtr.Zero)
        {
            int type = $modulePINVOKE.GetType_COptMethod(new HandleRef(null, cPtr));
            switch(type) {
                case COPASI.UNDEFINED_CLASS_TYPE:
                    break;
                case COPASI.CFitMethod_Type:
                    // return a CFitMethod
                    ret = new CFitMethod(cPtr,owner);
                    break;
                case COPASI.COptMethod_Type:
                    // return a COptMethod
                    ret = new COptMethod(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }

        return ret;
    }

    // COptProblem
    public static COptProblem InstantiateConcrete_COptProblem(IntPtr cPtr, bool owner)
    {
        COptProblem ret = null;

        if (cPtr != IntPtr.Zero)
        {
            int type = $modulePINVOKE.GetType_COptProblem(new HandleRef(null, cPtr));
            switch(type)
            {
                case COPASI.UNDEFINED_CLASS_TYPE:
                    break;
                case COPASI.CFitProblem_Type:
                    // return a CFitProblem
                    ret = new CFitProblem(cPtr,owner);
                    break;
                case COPASI.COptProblem_Type:
                    // return a COptProblem
                    ret = new COptProblem(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }


    // COptTask
    public static COptTask InstantiateConcrete_COptTask(IntPtr cPtr, bool owner)
    {
        COptTask ret = null;

        if (cPtr != IntPtr.Zero)
        {
            int type = $modulePINVOKE.GetType_COptTask(new HandleRef(null, cPtr));
            switch(type)
            {
                case COPASI.UNDEFINED_CLASS_TYPE:
                    break;
                case COPASI.CFitTask_Type:
                    // return a CFitTask
                    ret = new CFitTask(cPtr,owner);
                    break;
                case COPASI.COptTask_Type:
                    // return a COptTask
                    ret = new COptTask(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }

        }
        return ret;
    }

    // CCopasiAbstractArray
    public static CCopasiAbstractArray InstantiateConcrete_CCopasiAbstractArray(IntPtr cPtr, bool owner)
    {
        CCopasiAbstractArray ret = null;

        if (cPtr != IntPtr.Zero)
        {
            int type = $modulePINVOKE.GetType_CCopasiAbstractArray(new HandleRef(null, cPtr));
            switch(type)
            {
                case COPASI.CCopasiArray_Type:
                    // return a CCopasiArray
                    ret = new CCopasiArray(cPtr,owner);
                    break;
                case COPASI.AnnotatedFloatMatrix_Type:
                    // return a AnnotatedFloatMatrix
                    ret = new AnnotatedFloatMatrix(cPtr,owner);
                    break;
                case COPASI.CCopasiAbstractArray_Type:
                    // return a CCopasiAbstractArray
                    ret = new CCopasiAbstractArray(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }


    // Determine type for CCopasiContainer
    public static CCopasiContainer InstantiateConcrete_CCopasiContainer(IntPtr cPtr, bool owner)
    {
        CCopasiContainer ret = null;

        if (cPtr != IntPtr.Zero)
        {
            int type = $modulePINVOKE.GetType_CCopasiContainer(new HandleRef(null, cPtr));
            switch(type)
            {
                case COPASI.UNDEFINED_CLASS_TYPE:
                    break;
                case COPASI.CCopasiRootContainer_Type:
                    // return a CCopasiRootContainer
                    ret = new CCopasiRootContainer(cPtr,owner);
                    break;
                case COPASI.CCopasiDataModel_Type:
                    // return a CCopasiDataModel
                    ret = new CCopasiDataModel(cPtr,owner);
                    break;
                case COPASI.CChemEq_Type:
                    // return a CChemEq
                    ret = new CChemEq(cPtr,owner);
                    break;
                case COPASI.CChemEqElement_Type:
                    // return a CChemEqElement
                    ret = new CChemEqElement(cPtr,owner);
                    break;
                case COPASI.CReference_Type:
                    // return a CReference
                    ret = new CReference(cPtr,owner);
                    break;
                case COPASI.CModification_Type:
                    // return a CModification
                    ret = new CModification(cPtr,owner);
                    break;
                case COPASI.CCreator_Type:
                    // return a CCreator
                    ret = new CCreator(cPtr,owner);
                    break;
                case COPASI.CBiologicalDescription_Type:
                    // return a CBiologicalDescription
                    ret = new CBiologicalDescription(cPtr,owner);
                    break;
                case COPASI.CMIRIAMInfo_Type:
                    // return a CMIRIAMInfo
                    ret = new CMIRIAMInfo(cPtr,owner);
                    break;
                case COPASI.CCopasiTask_Type:
                    ret = InstantiateConcrete_CCopasiTask(cPtr,owner);
                    break;
                case COPASI.CCopasiParameter_Type:
                    ret = InstantiateConcrete_CCopasiParameter(cPtr,owner);
                    break;
                case COPASI.CEvaluationTree_Type:
                    ret = InstantiateConcrete_CEvaluationTree(cPtr,owner);
                    break;
                case COPASI.CFunctionDB_Type:
                    // return a CFunctionDB
                    ret = new CFunctionDB(cPtr,owner);
                    break;
                case COPASI.CFunctionParameter_Type:
                    // return a CFunctionParameter
                    ret = new CFunctionParameter(cPtr,owner);
                    break;
                case COPASI.CFunctionParameters_Type:
                    // return a CFunctionParameters
                    ret = new CFunctionParameters(cPtr,owner);
                    break;
                case COPASI.CEvent_Type:
                    // return a CEvent
                    ret = new CEvent(cPtr,owner);
                    break;
                case COPASI.CEventAssignment_Type:
                    // return a CEventAssignment
                    ret = new CEventAssignment(cPtr,owner);
                    break;
                case COPASI.CModelEntity_Type:
                    ret = InstantiateConcrete_CModelEntity(cPtr,owner);
                    break;
                case COPASI.CMoiety_Type:
                    // return a CMoiety
                    ret = new CMoiety(cPtr,owner);
                    break;
                case COPASI.CReaction_Type:
                    // return a CReaction
                    ret = new CReaction(cPtr,owner);
                    break;
                case COPASI.CFittingPoint_Type:
                    // return a CFittingPoint
                    ret = new CFittingPoint(cPtr,owner);
                    break;
                case COPASI.TaskVectorN_Type:
                    // return a TaskVectorN
                    ret = new TaskVectorN(cPtr,owner);
                    break;
                case COPASI.TaskVector_Type:
                    // return a TaskVector
                    ret = new TaskVector(cPtr,owner);
                    break;
                case COPASI.ModelValueVectorN_Type:
                    // return a ModelValueVectorN
                    ret = new ModelValueVectorN(cPtr,owner);
                    break;
                case COPASI.ModelValueVector_Type:
                    // return a ModelValueVector
                    ret = new ModelValueVector(cPtr,owner);
                    break;
                case COPASI.EventVectorN_Type:
                    // return a CEventVectorN
                    ret = new EventVectorN(cPtr,owner);
                    break;
                case COPASI.EventVector_Type:
                    // return a EventVector
                    ret = new EventVector(cPtr,owner);
                    break;
                case COPASI.EventAssignmentVectorN_Type:
                    // return a EventAssignmentVectorN
                    ret = new EventAssignmentVectorN(cPtr,owner);
                    break;
                case COPASI.EventAssignmentVector_Type:
                    // return a EventAssignmentVector
                    ret = new EventAssignmentVector(cPtr,owner);
                    break;
                case COPASI.ReportDefinitionVectorN_Type:
                    // return a ReportDefinitionVectorN
                    ret = new ReportDefinitionVectorN(cPtr,owner);
                    break;
                case COPASI.ReportDefinitionVector_Type:
                    // return a ReportDefinitionVector
                    ret = new ReportDefinitionVector(cPtr,owner);
                    break;
                case COPASI.MoietyVector_Type:
                    // return a MoietyVector
                    ret = new MoietyVector(cPtr,owner);
                    break;
                case COPASI.MetabVectorNS_Type:
                    // return a MetabVectorNS
                    ret = new MetabVectorNS(cPtr,owner);
                    break;
                case COPASI.MetabVectorN_Type:
                    // return a MetabVectorN
                    ret = new MetabVectorN(cPtr,owner);
                    break;
                case COPASI.MetabVector_Type:
                    // return a MetabVector
                    ret = new MetabVector(cPtr,owner);
                    break;
                case COPASI.CompartmentVectorNS_Type:
                    // return a CompartmentVectorNS
                    ret = new CompartmentVectorNS(cPtr,owner);
                    break;
                case COPASI.CompartmentVectorN_Type:
                    // return a CompartmentVectorN
                    ret = new CompartmentVectorN(cPtr,owner);
                    break;
                case COPASI.CompartmentVector_Type:
                    // return a CompartmentVector
                    ret = new CompartmentVector(cPtr,owner);
                    break;
                case COPASI.ReactionVectorNS_Type:
                    // return a ReactionVectorNS
                    ret = new ReactionVectorNS(cPtr,owner);
                    break;
                case COPASI.ReactionVectorN_Type:
                    // return a ReactionVectorN
                    ret = new ReactionVectorN(cPtr,owner);
                    break;
                case COPASI.ReactionVector_Type:
                    // return a ReactionVector
                    ret = new ReactionVector(cPtr,owner);
                    break;
                case COPASI.CEvaluationTreeVectorN_Type:
                    // return a CEvaluationTreeVectorN
                    ret = new CEvaluationTreeVectorN(cPtr,owner);
                    break;
                case COPASI.CEvaluationTreeVector_Type:
                    // return a CEvaluationTreeVector
                    ret = new CEvaluationTreeVector(cPtr,owner);
                    break;
                case COPASI.CChemEqElementVector_Type:
                    // return a CChemEqElementVector
                    ret = new CChemEqElementVector(cPtr,owner);
                    break;
                case COPASI.CArrayAnnotation_Type:
                    // return a CArrayAnnotation
                    ret = new CArrayAnnotation(cPtr,owner);
                    break;
                case COPASI.CCopasiContainer_Type:
                    // return a CCopasiContainer
                    ret = new CCopasiContainer(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }

        return ret;
    }


    // CCopasiMethod
    public static CCopasiMethod InstantiateConcrete_CCopasiMethod(IntPtr cPtr, bool owner)
    {
        CCopasiMethod ret = null;

        if (cPtr != IntPtr.Zero)
        {
            int type = $modulePINVOKE.GetType_CCopasiMethod(new HandleRef(null, cPtr));
            switch(type)
            {
                case COPASI.UNDEFINED_CLASS_TYPE:
                    break;
                case COPASI.CTrajectoryMethod_Type:
                    // return a CTrajectoryMethod
                    ret = new CTrajectoryMethod(cPtr,owner);
                    break;
                case COPASI.CNewtonMethod_Type:
                    // return a CNewtonMethod
                    ret = new CNewtonMethod(cPtr,owner);
                    break;
                case COPASI.CSteadyStateMethod_Type:
                    // return a CSteadyStateMethod
                    ret = new CSteadyStateMethod(cPtr,owner);
                    break;
                case COPASI.CMCAMethod_Type:
                    // return a CMCAMethod
                    ret = new CMCAMethod(cPtr,owner);
                    break;
                case COPASI.CScanMethod_Type:
                    // return a CScanMethod
                    ret = new CScanMethod(cPtr,owner);
                    break;
                case COPASI.COptMethod_Type:
                    ret = InstantiateConcrete_COptMethod(cPtr,owner);
                    break;
                case COPASI.CLyapMethod_Type:
                    // return a CLyapMethod
                    ret = new CLyapMethod(cPtr,owner);
                    break;
                case COPASI.CSensMethod_Type:
                    // return a CSensMethod
                    ret = new CSensMethod(cPtr,owner);
                    break;
                case COPASI.CCopasiMethod_Type:
                    // return a CCopasiMethod
                    ret = new CCopasiMethod(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }


    // CCopasiObject
    public static CCopasiObject InstantiateConcrete_CCopasiObject(IntPtr cPtr, bool owner)
    {
        CCopasiObject ret = null;

        if (cPtr != IntPtr.Zero)
        {
            int type = $modulePINVOKE.GetType_CCopasiObject(new HandleRef(null, cPtr));
            switch(type)
            {
                case COPASI.UNDEFINED_CLASS_TYPE:
                    break;
                case COPASI.CCopasiContainer_Type:
                    ret = InstantiateConcrete_CCopasiContainer(cPtr, owner);
                    break;
                case COPASI.CReportDefinition_Type:
                    // return a CReportDefinition
                    ret = new CReportDefinition(cPtr,owner);
                    break;
                case COPASI.CCopasiReportSeparator_Type:
                    // return a CCopasiReportSeparator
                    ret = new CCopasiReportSeparator(cPtr,owner);
                    break;
                case COPASI.CCopasiStaticString_Type:
                    // return a CCopasiStaticString
                    ret = new CCopasiStaticString(cPtr,owner);
                    break;
                case COPASI.CCopasiObject_Type:
                    // return a CCopasiObject
                    ret = new CCopasiObject(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }

        return ret;
    }


    // CCopasiParameter
    public static CCopasiParameter InstantiateConcrete_CCopasiParameter(IntPtr cPtr, bool owner)
    {
        CCopasiParameter ret = null;

        if (cPtr != IntPtr.Zero)
        {
            int type = $modulePINVOKE.GetType_CCopasiParameter(new HandleRef(null, cPtr));
            switch(type)
            {
                case COPASI.UNDEFINED_CLASS_TYPE:
                    break;
                case COPASI.CCopasiParameterGroup_Type:
                    ret = InstantiateConcrete_CCopasiParameterGroup(cPtr,owner);
                    break;
                case COPASI.CCopasiParameter_Type:
                    // return a CCopasiParameter
                    ret = new CCopasiParameter(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }

    // CCopasiParameterGroup
    public static CCopasiParameterGroup InstantiateConcrete_CCopasiParameterGroup(IntPtr cPtr, bool owner)
    {
        CCopasiParameterGroup ret = null;

        if (cPtr != IntPtr.Zero)
        {
            int type = $modulePINVOKE.GetType_CCopasiParameterGroup(new HandleRef(null, cPtr));
            switch(type)
            {
                case COPASI.UNDEFINED_CLASS_TYPE:
                    break;
                case COPASI.CCopasiMethod_Type:
                    ret = InstantiateConcrete_CCopasiMethod(cPtr,owner);
                    break;
                case COPASI.CCopasiProblem_Type:
                    ret = InstantiateConcrete_CCopasiProblem(cPtr,owner);
                    break;
                case COPASI.COptItem_Type:
                    ret = InstantiateConcrete_COptItem(cPtr,owner);
                    break;
                case COPASI.CExperiment_Type:
                    // return a CExperiment
                    ret = new CExperiment(cPtr,owner);
                    break;
                case COPASI.CExperimentSet_Type:
                    // return a CExperimentSet
                    ret = new CExperimentSet(cPtr,owner);
                    break;
                case COPASI.CExperimentObjectMap_Type:
                    // return a CExperimentObjectMap
                    ret = new CExperimentObjectMap(cPtr,owner);
                    break;
                case COPASI.CCopasiParameterGroup_Type:
                    // return a CCopasiParameterGroup
                    ret = new CCopasiParameterGroup(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }

    // CCopasiProblem
    public static CCopasiProblem InstantiateConcrete_CCopasiProblem(IntPtr cPtr, bool owner)
    {
        CCopasiProblem ret = null;

        if (cPtr != IntPtr.Zero)
        {
            int type = $modulePINVOKE.GetType_CCopasiProblem(new HandleRef(null, cPtr));
            switch(type)
            {
                case COPASI.UNDEFINED_CLASS_TYPE:
                    break;
                case COPASI.CTrajectoryProblem_Type:
                    // return a CTrajectoryProblem
                    ret = new CTrajectoryProblem(cPtr,owner);
                    break;
                case COPASI.CSteadyStateProblem_Type:
                    // return a CSteadyStateProblem
                    ret = new CSteadyStateProblem(cPtr,owner);
                    break;
                case COPASI.CMCAProblem_Type:
                    // return a CMCAProblem
                    ret = new CMCAProblem(cPtr,owner);
                    break;
                case COPASI.CScanProblem_Type:
                    // return a CScanProblem
                    ret = new CScanProblem(cPtr,owner);
                    break;
                case COPASI.COptProblem_Type:
                    ret = InstantiateConcrete_COptProblem(cPtr,owner);
                    break;
                case COPASI.CLyapProblem_Type:
                    // return a CLyapProblem
                    ret = new CLyapProblem(cPtr,owner);
                    break;
                case COPASI.CSensProblem_Type:
                    // return a CSensProblem
                    ret = new CSensProblem(cPtr,owner);
                    break;
                case COPASI.CCopasiProblem_Type:
                    // return a CCopasiProblem
                    ret = new CCopasiProblem(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }


    // CCopasiTask
    public static CCopasiTask InstantiateConcrete_CCopasiTask(IntPtr cPtr, bool owner)
    {
        CCopasiTask ret = null;

        if (cPtr != IntPtr.Zero)
        {
            int type = $modulePINVOKE.GetType_CCopasiTask(new HandleRef(null, cPtr));
            switch(type)
            {
                case COPASI.UNDEFINED_CLASS_TYPE:
                    break;
                case COPASI.CTrajectoryTask_Type:
                    // return a CTrajectoryTask
                    ret = new CTrajectoryTask(cPtr,owner);
                    break;
                case COPASI.CSteadyStateTask_Type:
                    // return a CSteadyStateTask
                    ret = new CSteadyStateTask(cPtr,owner);
                    break;
                case COPASI.CMCATask_Type:
                    // return a CMCATask
                    ret = new CMCATask(cPtr,owner);
                    break;
                case COPASI.CScanTask_Type:
                    // return a CScanTask
                    ret = new CScanTask(cPtr,owner);
                    break;
                case COPASI.COptTask_Type:
                    ret = InstantiateConcrete_COptTask(cPtr,owner);
                    break;
                case COPASI.CLyapTask_Type:
                    // return a CLyapTask
                    ret = new CLyapTask(cPtr,owner);
                    break;
                case COPASI.CSensTask_Type:
                    // return a CSensTask
                    ret = new CSensTask(cPtr,owner);
                    break;
                case COPASI.CCopasiTask_Type:
                    // return a CCopasiTask
                    ret = new CCopasiTask(cPtr,owner);
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false,
                            String.Format("Encountered type '{0}' that is not known to be a valid COPASI native class type",
                                type.ToString()));
                    break;
            }
        }
        return ret;
    }

%}


// now we need some typemaps that actually use the methods above

// CCopasiObject
%typemap(csout, excode=SWIGEXCODE)
  CCopasiObject *,
  const CCopasiObject *,
  CCopasiObject &,
  const CCopasiObject &
{
    IntPtr cPtr = $imcall;
    $csclassname ret = ($csclassname) $modulePINVOKE.InstantiateConcrete_CCopasiObject(cPtr, $owner);$excode
    return ret;
}

// CCopasiAbstractArray
%typemap(csout, excode=SWIGEXCODE)
  CCopasiAbstractArray *,
  const CCopasiAbstractArray *,
  CCopasiAbstractArray &,
  const CCopasiAbstractArray &
{
    IntPtr cPtr = $imcall;
    $csclassname ret = ($csclassname) $modulePINVOKE.InstantiateConcrete_CCopasiAbstractArray(cPtr, $owner);$excode
    return ret;
}

// CCopasiContainer
%typemap(csout, excode=SWIGEXCODE)
  CCopasiContainer *,
  const CCopasiContainer *,
  CCopasiContainer &,
  const CCopasiContainer &
{
    IntPtr cPtr = $imcall;
    $csclassname ret = ($csclassname) $modulePINVOKE.InstantiateConcrete_CCopasiContainer(cPtr, $owner);$excode
    return ret;
}

// CCopasiParameter
%typemap(csout, excode=SWIGEXCODE)
  CCopasiParameter *,
  const CCopasiParameter *,
  CCopasiParameter &,
  const CCopasiParameter &
{
    IntPtr cPtr = $imcall;
    $csclassname ret = ($csclassname) $modulePINVOKE.InstantiateConcrete_CCopasiParameter(cPtr, $owner);$excode
    return ret;
}

// CCopasiParameterGroup
%typemap(csout, excode=SWIGEXCODE)
  CCopasiParameterGroup *,
  const CCopasiParameterGroup *,
  CCopasiParameterGroup &,
  const CCopasiParameterGroup &
{
    IntPtr cPtr = $imcall;
    $csclassname ret = ($csclassname) $modulePINVOKE.InstantiateConcrete_CCopasiParameterGroup(cPtr, $owner);$excode
    return ret;
}

// CCopasiProblem
%typemap(csout, excode=SWIGEXCODE)
  CCopasiProblem *,
  const CCopasiProblem *,
  CCopasiProblem &,
  const CCopasiProblem &
{
    IntPtr cPtr = $imcall;
    $csclassname ret = ($csclassname) $modulePINVOKE.InstantiateConcrete_CCopasiProblem(cPtr, $owner);$excode
    return ret;
}

// CCopasiMethod
%typemap(csout, excode=SWIGEXCODE)
  CCopasiMethod *,
  const CCopasiMethod *,
  CCopasiMethod &,
  const CCopasiMethod &
{
    IntPtr cPtr = $imcall;
    $csclassname ret = ($csclassname) $modulePINVOKE.InstantiateConcrete_CCopasiMethod(cPtr, $owner);$excode
    return ret;
}

// CCopasiTask
%typemap(csout, excode=SWIGEXCODE)
  CCopasiTask *,
  const CCopasiTask *,
  CCopasiTask &,
  const CCopasiTask &
{
    IntPtr cPtr = $imcall;
    $csclassname ret = ($csclassname) $modulePINVOKE.InstantiateConcrete_CCopasiTask(cPtr, $owner);$excode
    return ret;
}

// CEvaluationTree
%typemap(csout, excode=SWIGEXCODE)
  CEvaluationTree *,
  const CEvaluationTree *,
  CEvaluationTree &,
  const CEvaluationTree &
{
    IntPtr cPtr = $imcall;
    $csclassname ret = ($csclassname) $modulePINVOKE.InstantiateConcrete_CEvaluationTree(cPtr, $owner);$excode
    return ret;
}

// CModelEntity
%typemap(csout, excode=SWIGEXCODE)
  CModelEntity *,
  const CModelEntity *,
  CModelEntity &,
  const CModelEntity &
{
    IntPtr cPtr = $imcall;
    $csclassname ret = ($csclassname) $modulePINVOKE.InstantiateConcrete_CModelEntity(cPtr, $owner);$excode
    return ret;
}



/**
 * C# does not handle exceptions the same way as java. The code below will have to be adjusted
 * once the build system is finished.
 */
%exception CCopasiTask::process %{
    try
    {
        $action
    }
    catch (std::exception &e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.what());
        return $null;
    }
    catch(CCopasiException& e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.getMessage().getText().c_str());
        return $null;
    }
%}


%exception CCopasiDataModel::importSBML %{
    try
    {
        $action
    }
    catch (std::exception &e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.what());
        return $null;
    }
    catch(CCopasiException& e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.getMessage().getText().c_str());
        return $null;
    }
%}


%exception CCopasiDataModel::newModel %{
    try
    {
        $action
    }
    catch (std::exception &e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.what());
        return $null;
    }
    catch(CCopasiException& e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.getMessage().getText().c_str());
        return $null;
    }
%}

%exception CCopasiDataModel::importSBMLFromString %{
    try
    {
        $action
    }
    catch (std::exception &e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.what());
        return $null;
    }
    catch(CCopasiException& e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.getMessage().getText().c_str());
        return $null;
    }
%}

%exception CCopasiDataModel::exportSBMLToString %{
    try
    {
        $action
    }
    catch (std::exception &e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.what());
        return $null;
    }
    catch(CCopasiException& e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.getMessage().getText().c_str());
        return $null;
    }
%}

%exception CCopasiDataModel::exportSBML %{
    try
    {
        $action
    }
    catch (std::exception &e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.what());
        return $null;
    }
    catch(CCopasiException& e)
    {
        SWIG_CSharpSetPendingException(SWIG_CSharpApplicationException, e.getMessage().getText().c_str());
        return $null;
    }
%}



// some general ignore statements that already get rid of most warnings
%ignore *::operator =;
%ignore *::operator [];
%ignore *::operator ();
%ignore *::begin() const;
%ignore *::end() const;

%include "../swig/copasi.i"


