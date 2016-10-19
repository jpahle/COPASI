// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "MetaboliteHandler.h"

/**
 * Replace Metabolite with the name type of the handler and implement the
 * three methods below.
 */
MetaboliteHandler::MetaboliteHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Metabolite)
{
  init();
}

// virtual
MetaboliteHandler::~MetaboliteHandler()
{}

// virtual
CXMLHandler * MetaboliteHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool MetaboliteHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case COPASI:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * MetaboliteHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Metabolite", Metabolite, {BEFORE}},
    {"BEFORE", BEFORE, {Metabolite, BEFORE}}
  };

  return Elements;
}
