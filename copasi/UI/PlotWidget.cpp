/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/PlotWidget.cpp,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/08/06 12:56:44 $
   End CVS Header */

#include "PlotWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>

#include "MyTable.h"
#include "model/CModel.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "report/CReportDefinition.h"
#include "report/CCopasiStaticString.h"
#include "qtUtilities.h"
#include "plot/CPlotSpec2Vector.h"
#include "DataModelGUI.h"

std::vector<const CCopasiObject*> PlotWidget::getObjects() const
  {
    CCopasiVector<CPlotSpecification>* tmp =
      dataModel->getPlotSpecVectorAddr();

    std::vector<const CCopasiObject*> ret;

    C_INT32 i, imax = tmp->size();
    for (i = 0; i < imax; ++i)
      ret.push_back((*tmp)[i]);

    return ret;
  }

void PlotWidget::init()
{
  mOT = ListViews::PLOT;
  numCols = 4;
  table->setNumCols(numCols);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Status");
  tableHeader->setLabel(1, "Name");
  tableHeader->setLabel(2, "Curves");
  tableHeader->setLabel(3, "active");

  //this restricts users from editing the number of curves
  table->setColumnReadOnly (2, true);
}

void PlotWidget::tableLineFromObject(const CCopasiObject* obj, unsigned C_INT32 row)
{
  if (!obj) return;
  //const CPlotSpecification* pPl = (const CPlotSpecification*)obj;
  const CPlotSpecification* pPl = dynamic_cast<const CPlotSpecification*>(obj);

  // 1: name
  table->setText(row, 1, FROM_UTF8(pPl->getObjectName()));

  // 2: NCurves
  table->setText(row, 2, QString::number(pPl->getItems().size()));

  // 3: active?
  QCheckTableItem * activeCB;
  activeCB = new QCheckTableItem(table, "");
  activeCB->setChecked(pPl->isActive());
  table->setItem(row, 3, activeCB);
}

void PlotWidget::tableLineToObject(unsigned C_INT32 row, CCopasiObject* obj)
{
  if (!obj) return;
  CPlotSpecification* pPl = (CPlotSpecification*)obj;

  // 3: active?
  bool active = ((QCheckTableItem*)(table->item(row, 3)))->isChecked();
  pPl->setActive(active);
}

void PlotWidget::defaultTableLineContent(unsigned C_INT32 row, unsigned C_INT32 exc)
{
  if (exc != 2)
    table->setText(row, 2, "");

  // 3: active?
  if (exc != 3)
    {
      QCheckTableItem * activeCB;
      activeCB = new QCheckTableItem(table, "");
      activeCB->setChecked(true);
      table->setItem(row, 3, activeCB);
    }
}

QString PlotWidget::defaultObjectName() const
  {
    return "plot";
  }

CCopasiObject* PlotWidget::createNewObject(const std::string & name)
{
  std::string nname = name;
  int i = 0;
  CPlotSpecification* pPl;
  while (!(pPl = dataModel->getPlotSpecVectorAddr()->createPlotSpec(nname, CPlotItem::plot2d)))
    {
      i++;
      nname = name;
      nname += (const char *)QString::number(i).utf8();
    }

  pPl->createDefaultPlot(dataModel->getModel()); //TODO have an extra button for that

  std::cout << " *** created PlotSpecification: " << nname << " : " << pPl->CCopasiParameter::getKey() << std::endl;
  return pPl;
}

void PlotWidget::deleteObjects(const std::vector<std::string> & keys)
{
  if (!dataModel->getModel())
    return;

  if (keys.size() == 0)
    return;

  unsigned C_INT32 i, imax = keys.size();
  for (i = 0; i < imax; i++)
    {
      dataModel->getPlotSpecVectorAddr()->removePlotSpec(keys[i]);
      ListViews::notify(ListViews::PLOT, ListViews::DELETE, keys[i]);
    }
}
