/***********************************************************************
 **  $ CopasiUI/FunctionWidget.cpp                 
 **  $ Author  : Mrinmayee Kulkarni
 **
 ** This file creates the GUI which displays information obtained 
 ** from the function database. The name and type of functions are  
 ** displayes in tablular form. This is the first level widget for functions
 ************************************************************************/
#include "FunctionWidget.h"

#include <qlayout.h>
#include <qwidget.h>

#include "MyTable.h"
#include "model/CModel.h"
#include "function/CFunction.h"
#include "function/CFunctionDB.h"
#include "function/CKinFunction.h"
#include "listviews.h"
#include "report/CKeyFactory.h"

/**
 *  Constructs a Widget for the Functions subsection of the tree for 
 *  displaying the functions.
 *  This widget is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'. 
 *  @param parent The widget which this widget is a child of.
 *  @param name The object name is a text that can be used to identify 
 *  this QObject. It's particularly useful in conjunction with the Qt Designer.
 *  You can find an object by name (and type) using child(), and more than one 
 *  using queryList(). 
 *  @param flags Flags for this widget. Refer Qt::WidgetFlags of Qt documentation 
 *  for more information about these flags.
 */

FunctionWidget::FunctionWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl)
{
  binitialized = true;

  table = new MyTable(0, 2, this, "tblFunctions");
  table->setNumRows(-1);
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Name");
  tableHeader->setLabel(1, "Type");
  setFocusPolicy(QWidget::WheelFocus);
  setFocusProxy (table);
  table->setFocusPolicy(QWidget::WheelFocus);

  // signals and slots connections

  connect(table, SIGNAL(doubleClicked(int, int, int, const QPoint &)),
          this, SLOT(slotTableCurrentChanged(int, int, int, const QPoint &)));
  connect(table, SIGNAL(selectionChanged ()),
          this, SLOT(slotTableSelectionChanged ()));
}

void FunctionWidget::fillTable()
{
  const CFunction *obj;
  const CCopasiVectorN < CFunction > & objects = Copasi->pFunctionDB->loadedFunctions();
  C_INT32 j, jmax = objects.size();
  table->setNumRows(jmax);
  mKeys.resize(jmax);

  for (j = 0; j < jmax; ++j)
    {
      obj = objects[j];
      table->setText(j, 0, obj->getName().c_str());

      QString ftype;
      switch (obj->getType())
        {
        case 1:
        case 2:
          ftype = QString("pre-defined");
          break;
        case 3:
          ftype = QString("user-defined");
          break;
        }
      table->setText(j, 1, ftype);

      mKeys[j] = obj->getKey();
    }
  table->setText(jmax, 1, "");
}

//**************************************************************************

void FunctionWidget::createNewObject()
{}

void FunctionWidget::slotTableCurrentChanged(int row,
    int C_UNUSED(col),
    int C_UNUSED(m) ,
    const QPoint & C_UNUSED(n))
{
  if (row >= table->numRows() || row < 0) return;

  if (row == table->numRows() - 1)
    {
      //TODO: create a new Object
    }

  pListView->switchToOtherWidget(mKeys[row]);
}

void FunctionWidget::slotTableSelectionChanged()
{
  if (!table->hasFocus()) table->setFocus();
}

void FunctionWidget::tableValueChanged(int C_UNUSED(row),
                                       int C_UNUSED(col))
{}

bool FunctionWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  switch (objectType)
    {
    case ListViews::FUNCTION:
    case ListViews::MODEL:
      fillTable();
      break;

    default:
      break;
    }
  return true;
}

bool FunctionWidget::leave()
{
  //does nothing.
  return true;
}

bool FunctionWidget::enter(const std::string & key)
{
  //does nothing.
  return true;
}

//*******************************************************************************************

void FunctionWidget::resizeEvent(QResizeEvent * re)
{
  if (isVisible())
    {
      //      repaint_table();
      if (binitialized)
        {
          int newWidth = re->size().width();
          newWidth -= 35; //Accounting for the left (vertical) header width.
          float weight0 = 4.0, weight1 = 3.0, weight2 = 3.0, weight3 = 3.0 , weight4 = 3.0;
          float weightSum = weight0 + weight1 + weight2 + weight3 + weight4;
          int w0, w1, w2, w3 , w4;
          w0 = newWidth * (weight0 / weightSum);
          w1 = newWidth * (weight1 / weightSum);
          w2 = newWidth * (weight2 / weightSum);
          w3 = newWidth * (weight3 / weightSum);
          w4 = newWidth - w0 - w1 - w2 - w3;
          table->setColumnWidth(0, w0);
          table->setColumnWidth(1, w1);
          table->setColumnWidth(2, w2);
          table->setColumnWidth(3, w3);
          table->setColumnWidth(4, w4);
          binitialized = false;
        }
      else
        {
          table->DisableColWidthUpdate();
          int newWidth = re->size().width();
          int i;

          int totalWidth = 0;
          for (i = 0; i < table->numCols(); i++)
            totalWidth += table->columnWidth(i);

          int minTotalWidth = 0;
          for (i = 0; i < table->numCols(); i++)
            minTotalWidth += table->minColWidth[i];

          //Zoom in
          if (newWidth > re->oldSize().width())
            {
              if (newWidth > totalWidth) // can do expansion
                {
                  if (totalWidth < re->oldSize().width())
                    for (i = 0; i < table->numCols(); i++) // Do expansion
                      table->setColumnWidth(i, newWidth*table->columnWidth(i) / re->oldSize().width());
                  else
                    for (i = 0; i < table->numCols(); i++) // Do expansion
                      table->setColumnWidth(i, float(newWidth)*float(table->columnWidth(i)) / float(totalWidth));
                }
              else
                for (i = 0; i < table->numCols(); i++) // Do not expand
                  table->setColumnWidth(i, table->columnWidth(i));

              table->EnableColWidthUpdate();
              return;
            }
          //Zoom out
          //calculate total Width
          if (newWidth >= totalWidth)    //will not decrease any column width
            {
              for (i = 0; i < table->numCols(); i++)
                table->setColumnWidth(i, table->columnWidth(i));
              table->EnableColWidthUpdate();
              return;
            }
          //will decrease only those larger than the minimum width
          //Less than the user specified total width
          if (newWidth <= minTotalWidth)
            {
              for (i = 0; i < table->numCols(); i++)
                table->setColumnWidth(i, table->minColWidth[i]);
              table->EnableColWidthUpdate();
              return;
            }
          //Bigger than the user specified total width
          for (i = 0; i < table->numCols(); i++) // Do Expansion
            table->setColumnWidth(i, (newWidth - minTotalWidth)*(table->columnWidth(i) - table->minColWidth[i]) / (totalWidth - minTotalWidth) + table->minColWidth[i]);
          table->EnableColWidthUpdate();
          return;
        }
    }
  CopasiWidget::resizeEvent(re);
}
