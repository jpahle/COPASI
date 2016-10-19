// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "LineSegmentHandler.h"

/**
 * Replace LineSegment with the name type of the handler and implement the
 * three methods below.
 */
LineSegmentHandler::LineSegmentHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::LineSegment)
{
  init();
}

// virtual
LineSegmentHandler::~LineSegmentHandler()
{}

// virtual
CXMLHandler * LineSegmentHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool LineSegmentHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * LineSegmentHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"LineSegment", LineSegment, {BEFORE}},
    {"BEFORE", BEFORE, {LineSegment, BEFORE}}
  };

  return Elements;
}