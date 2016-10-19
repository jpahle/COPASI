// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "EventHandler.h"

/**
 * Replace Event with the name type of the handler and implement the
 * three methods below.
 */
EventHandler::EventHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Event)
{
  init();
}

// virtual
EventHandler::~EventHandler()
{}

// virtual
CXMLHandler * EventHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool EventHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * EventHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Event", Event, {BEFORE}},
    {"BEFORE", BEFORE, {Event, BEFORE}}
  };

  return Elements;
}
