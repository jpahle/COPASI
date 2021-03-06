// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLRenderFlattener_H__
#define CLRenderFlattener_H__

#ifdef _WIN32
// disable warning about unimplemented exceptions in VC++
#pragma warning(disable : 4290)
#endif // _WIN32

#include "copasi/layout/CLGlobalRenderInformation.h"
#include "copasi/layout/CLLocalRenderInformation.h"

#include "CLUnresolvedReferenceException.h"

class CLLocalStyle;
class CLGlobalStyle;
class CLRenderInformationBase;

class CLRenderFlattener
{

public:
  /**
   * static method that takes a const reference to a global render
   * information object and resolves all references.
   * The returned object is a new global render information object and the
   * caller is responsible for freeing the memory once it is no longer used.
   * If references can not be resolved, an unresolved_reference_exception is
   * thrown.
   */
  static CLGlobalRenderInformation* flatten_render_information(const CLGlobalRenderInformation& globalRenderInformation, const CCopasiVector<CLGlobalRenderInformation>& globalList) throw(CLUnresolvedReferenceException);

  /**
   * static method that takes a const reference to a local render
   * information object and resolves all references.
   * The returned object is a new local render information object and the
   * caller is responsible for freeing the memory once it is no longer used.
   * If references can not be resolved, an unresolved_reference_exception is
   * thrown.
   */
  static CLLocalRenderInformation* flatten_render_information(const CLLocalRenderInformation& localRenderInformation, const CCopasiVector<CLLocalRenderInformation>& localList, const CCopasiVector<CLGlobalRenderInformation>& globalList) throw(CLUnresolvedReferenceException);

protected:
  /**
   * Takes a reference to any type of render information and two lists. The
   * first list is a list of global render information objects, the second list is a list of local render information objects.
   * If the object that is passed in is a global render information object,
   * the second list is not considered.
   */
  static CLRenderInformationBase* flatten(const CLRenderInformationBase& renderInformation,
                                          const CCopasiVector<CLGlobalRenderInformation>& globalList,
                                          const CCopasiVector<CLLocalRenderInformation>& localList) throw(CLUnresolvedReferenceException);

  /**
   * Method takes a global style object and converts it to a local style
   * object.
   * The caller is responsible for freeing the memory of the returned
   * object once it is no longer needed.
   */
  static CLLocalStyle* convertGlobalToLocalStyle(const CLGlobalStyle* pGlobal);
};

#endif // CLRenderFlattener_H__
