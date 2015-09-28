// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * InsertGlobalQuantityRowsCommand.cpp
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModelValue.h"
#include "model/CModel.h"
#include "CQGlobalQuantityDM.h"

#include "InsertGlobalQuantityRowsCommand.h"
#include "UndoGlobalQuantityData.h"

#include "InsertGlobalQuantityRowsCommand.h"

InsertGlobalQuantityRowsCommand::InsertGlobalQuantityRowsCommand(int position, int rows, CQGlobalQuantityDM *pGlobalQuantityDM, const QModelIndex& index)
  : CCopasiUndoCommand("Global Quantity", GLOBALQUANTITY_INSERT)
  , mpGlobalQuantityDM(pGlobalQuantityDM)
  , mRows(rows)
  , mPosition(position)
  , mIndex(index)
  , mpGlobalQuantityData(new UndoGlobalQuantityData())
  , firstTime(true)
{
  this->setText(insertRowsText());
}

void InsertGlobalQuantityRowsCommand::redo()
{
  if (firstTime)
    {
      mpGlobalQuantityDM->insertNewGlobalQuantityRow(mPosition, mRows, QModelIndex());
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
      assert(pDataModel != NULL);
      CModel * pModel = pDataModel->getModel();
      assert(pModel != NULL);

      CModelValue *pGlobalQuantity = pModel->getModelValues()[mPosition];
      mpGlobalQuantityData->setName(pGlobalQuantity->getObjectName());
      mpGlobalQuantityData->setKey(pGlobalQuantity->getKey());
      mpGlobalQuantityData->setInitialValue(pGlobalQuantity->getInitialValue());
      mpGlobalQuantityData->setStatus(pGlobalQuantity->getStatus());
      firstTime = false;
    }
  else
    {
      mpGlobalQuantityDM->addGlobalQuantityRow(mpGlobalQuantityData);
    }

  setUndoState(true);
  setAction("Add to list");
  setName(mpGlobalQuantityData->getName());
}

void InsertGlobalQuantityRowsCommand::undo()
{
  mpGlobalQuantityDM->deleteGlobalQuantityRow(mpGlobalQuantityData);
  setUndoState(false);
  setAction("Remove from list");
}

QString InsertGlobalQuantityRowsCommand::insertRowsText() const
{
  return QObject::tr(": Inserted new global quantity");
}

UndoData *InsertGlobalQuantityRowsCommand::getUndoData() const
{
  return mpGlobalQuantityData;
}

InsertGlobalQuantityRowsCommand::~InsertGlobalQuantityRowsCommand()
{
  pdelete(mpGlobalQuantityData);
}
