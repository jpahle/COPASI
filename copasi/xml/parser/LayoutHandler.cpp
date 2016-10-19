// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "LayoutHandler.h"

/**
 * Replace Layout with the name type of the handler and implement the
 * three methods below.
 */
LayoutHandler::LayoutHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Layout)
{
  init();
}

// virtual
LayoutHandler::~LayoutHandler()
{}

// virtual
CXMLHandler * LayoutHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool LayoutHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * LayoutHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Layout", Layout, {BEFORE}},
    {"BEFORE", BEFORE, {Layout, BEFORE}}
  };

  return Elements;
}
