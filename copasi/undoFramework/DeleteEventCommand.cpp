// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * DeleteEventCommand.cpp
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CEvent.h"
#include "model/CModel.h"
#include "UI/CQEventWidget1.h"

#include "UndoEventData.h"
#include "UndoEventAssignmentData.h"

#include "DeleteEventCommand.h"

DeleteEventCommand::DeleteEventCommand(CQEventWidget1 *pEVentWidget1)
  : CCopasiUndoCommand("Event", EVENTDELETE)
  , mFirstTime(true)
  , mpEventData(new UndoEventData())
  , mpEVentWidget1(pEVentWidget1)
{

  const std::string& sName = mpEVentWidget1->mpEvent->getObjectName();
  mpEventData->setName(sName);
  setName(sName);

  CCopasiVector< CEventAssignment >::const_iterator it = mpEVentWidget1->mpEvent->getAssignments().begin();
  CCopasiVector< CEventAssignment >::const_iterator end = mpEVentWidget1->mpEvent->getAssignments().end();

  for (; it != end; ++it)
    {
      const CModelEntity * pEntity = dynamic_cast< CModelEntity * >(CCopasiRootContainer::getKeyFactory()->get((*it)->getTargetKey()));
      UndoEventAssignmentData *eventAssignData = new UndoEventAssignmentData();
      eventAssignData->setName(pEntity->getObjectName());
      eventAssignData->setExpression((*it)->getExpression());
      mpEventData->getEventAssignmentData()->append(eventAssignData);
    }

  mpEventData->setTriggerExpression(mpEVentWidget1->mpEvent->getTriggerExpression());
  mpEventData->setDelayExpression(mpEVentWidget1->mpEvent->getDelayExpression());
  mpEventData->setPriorityExpression(mpEVentWidget1->mpEvent->getPriorityExpression());

  this->setText(deleteEventText(sName));
}

void DeleteEventCommand::redo()
{
  if (mFirstTime)
    {
      mpEVentWidget1->deleteEvent();
      mFirstTime = false;
    }
  else
    {
      mpEVentWidget1->deleteEvent(mpEventData);
    }

  setUndoState(true);
  setAction("Delete");
}

void DeleteEventCommand::undo()
{
  mpEVentWidget1->addEvent(mpEventData);
  setUndoState(false);
  setAction("Undelete");
}

QString DeleteEventCommand::deleteEventText(const std::string &name) const
{
//  std::string myEntityName(": Delete Event " + name);
//  char* entityName = (char*)myEntityName.c_str();
//  return QObject::tr(entityName);
  return QString(": Deleted event %1").arg(name.c_str());
}

UndoData *DeleteEventCommand::getUndoData() const
{
  return mpEventData;
}

DeleteEventCommand::~DeleteEventCommand()
{
  pdelete(mpEventData);
}