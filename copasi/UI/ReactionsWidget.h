/****************************************************************************
 **  $ CopasiUI/ReactionsWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Reactions Widget, i.e the First level 
 ** of Reactions.
 **
 *****************************************************************************/

#ifndef REACTIONS_WIDGET_H
#define REACTIONS_WIDGET_H

#include <qtable.h>
#include "copasi.h"
#include "copasiWidget.h"

class CModel;
class QPushButton;
class QGridLayout;
class QTable;
class MyTable;

class ReactionsWidget : public CopasiWidget
  {
    Q_OBJECT

  protected:
    MyTable *table;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    bool binitialized;
    std::vector<std::string> mKeys;

  public:
    ReactionsWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    void resizeEvent(QResizeEvent * re);

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void slotTableCurrentChanged(int, int, int, const QPoint &);

    virtual void slotTableSelectionChanged();
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void tableValueChanged(int, int);

  private:
    void fillTable();
    void createNewObject();
  };

#endif
