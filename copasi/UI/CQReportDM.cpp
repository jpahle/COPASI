// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QtCore/QString>
#include <QtCore/QList>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "report/CReportDefinition.h"
#include "report/CReportDefinitionVector.h"

#include "CQMessageBox.h"
#include "CQReportDM.h"
#include "qtUtilities.h"

CQReportDM::CQReportDM(QObject *parent)
  : CQBaseDataModel(parent)
  , mNewName("report")
{
}

int CQReportDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mpDataModel->getReportDefinitionList()->size() + 1;
}
int CQReportDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
{
  return TOTAL_COLS_REPORTS;
}

Qt::ItemFlags CQReportDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (index.column() == COL_NAME_REPORTS)
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  else
    return QAbstractItemModel::flags(index);
}

QVariant CQReportDM::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= rowCount())
    return QVariant();

  if (index.column() > 0 && role == Qt::ForegroundRole && !(flags(index) & Qt::ItemIsEditable))
    return QColor(Qt::darkGray);

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
      if (isDefaultRow(index))
        {
          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(QString(""));

              case COL_NAME_REPORTS:
                return QVariant(QString("New Report"));

              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          CReportDefinition *pRepDef = &mpDataModel->getReportDefinitionList()->operator[](index.row());

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_REPORTS:
                return QVariant(QString(FROM_UTF8(pRepDef->getObjectName())));
            }
        }
    }

  return QVariant();
}

QVariant CQReportDM::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal)
    {
      switch (section)
        {
          case COL_ROW_NUMBER:
            return QVariant(QString("#"));

          case COL_NAME_REPORTS:
            return QVariant(QString("Name"));

          default:
            return QVariant();
        }
    }
  else
    return QString("%1").arg(section + 1);
}

bool CQReportDM::setData(const QModelIndex &index, const QVariant &value,
                         int role)
{
  if (index.isValid() && role == Qt::EditRole)
    {
      bool defaultRow = isDefaultRow(index);

      if (defaultRow)
        {
          if (index.data() != value)
            {
              mNewName = (index.column() == COL_NAME_REPORTS) ? value.toString() : "report";
              insertRow(rowCount(), index);
            }
          else
            return false;
        }

      CReportDefinition *pRepDef = &mpDataModel->getReportDefinitionList()->operator[](index.row());

      if (index.column() == COL_NAME_REPORTS)
        pRepDef->setObjectName(TO_UTF8(value.toString()));

      emit dataChanged(index, index);
      emit notifyGUI(ListViews::REPORT, ListViews::CHANGE, pRepDef->getKey());
    }

  return true;
}

bool CQReportDM::insertRows(int position, int rows, const QModelIndex & source)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      QString Name = createNewName(mNewName, COL_NAME_REPORTS);
      CReportDefinition *pRepDef = mpDataModel->getReportDefinitionList()->createReportDefinition(TO_UTF8(Name), "");
      emit notifyGUI(ListViews::REPORT, ListViews::ADD, pRepDef->getKey());
    }

  endInsertRows();

  mNewName = "report";

  return true;
}

bool CQReportDM::removeRows(int position, int rows)
{
  if (rows <= 0)
    return true;

  if (mpDataModel == NULL)
    return false;

  CCopasiVector< CReportDefinition > * pReportList = mpDataModel->getReportDefinitionList();

  if (pReportList == NULL)
    return false;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      CReportDefinition * pReport = &pReportList->operator[](position);

      if (pReport == NULL)
        continue;

      std::set< const CCopasiObject * > Tasks;
      std::set< const CCopasiObject * > DeletedObjects;
      DeletedObjects.insert(pReport);

      if (mpDataModel->appendDependentTasks(DeletedObjects, Tasks))
        {
          std::set< const CCopasiObject * >::iterator it = Tasks.begin();
          std::set< const CCopasiObject * >::iterator end = Tasks.end();

          for (; it != end; ++it)
            {
              const CCopasiTask * pTask = static_cast< const CCopasiTask *>(*it);
              const_cast< CCopasiTask * >(pTask)->getReport().setReportDefinition(NULL);
            }
        }

      std::string deletedKey = pReport->getKey();
      pReportList->remove(pReport);
      emit notifyGUI(ListViews::REPORT, ListViews::DELETE, deletedKey);
    }

  endRemoveRows();

  return true;
}

bool CQReportDM::removeRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

  assert(mpDataModel != NULL);

  CCopasiVector< CReportDefinition > * pReportList = mpDataModel->getReportDefinitionList();

  if (pReportList == NULL)
    return false;

  QList< CReportDefinition * > Reports;

  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && &pReportList->operator[](i->row()))
        Reports.append(&pReportList->operator[](i->row()));
    }

  QList< CReportDefinition * >::const_iterator j;

  for (j = Reports.begin(); j != Reports.end(); ++j)
    {
      CReportDefinition * pReport = *j;

      size_t delRow = pReportList->getIndex(pReport);

      if (delRow != C_INVALID_INDEX)
        {
          std::set< const CCopasiObject * > DeletedObjects;
          DeletedObjects.insert(pReport);

          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(NULL, "report",
                                        FROM_UTF8(pReport->getObjectName()),
                                        DeletedObjects);

          if (choice == QMessageBox::Ok)
            {
              removeRow((int) delRow);
            }
        }
    }

  return true;
}
