/****************************************************************************
 ** Form interface generated from reading ui file '.\OptimizationWidget.ui'
 **
 ** Created: Fri Sep 19 15:37:58 2003
 **      by: The User Interface Compiler ($Id: OptimizationWidget.h,v 1.3 2003/09/30 04:10:40 lixu1 Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef OptimizationWidget_H
#define OptimizationWidget_H

#include <qvariant.h>
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QPushButton;
class QLabel;
//class QTable;
class QListBox;
class QLineEdit;
class QTextEdit;
class COptFunction;
class ScanScrollView;
class OptimizationItemWidget;
class QListBoxItem;

class OptimizationWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    OptimizationWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~OptimizationWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");
    //manually added
    QLineEdit* expressionText;
    ScanScrollView* itemsTable;

    QLineEdit* expressionName;
    QLabel* expressionEditlabel;
    QLabel* expressionNameLabel;
    QFrame* bodyField_2;
    QLabel* itemsLabel;
    QPushButton* downButton;
    QPushButton* deleteButton;
    QPushButton* addButton;
    QPushButton* upButton;
    QListBox* itemnamesTable;
    QFrame* bodyField;
    QPushButton* confirmButton;
    QPushButton* cancelButton;
    std::vector<QWidget*> selectedList;

  protected:
    QGridLayout* OptimizationWidgetLayout;
    QVBoxLayout* layout18;
    QGridLayout* layout17;
    QHBoxLayout* layout16;
    QVBoxLayout* layout15;
    QGridLayout* layout14;
    QHBoxLayout* layout14_2;

    bool loadFromExpression(COptFunction*);
    std::string objKey;
    bool bUpdated;

  protected slots:
    void addButtonClicked();
    void deleteButtonClicked();
    void upButtonClicked();
    void downButtonClicked();
    virtual void languageChange();
    virtual void slotBtnCancelClicked();
    virtual void slotBtnConfirmClicked();
    virtual void ListBoxClicked (QListBoxItem * item);
    virtual void ListBoxDoubleClicked (QListBoxItem* item);

  signals:
    void hide_me();
    void show_me();

  private:
    void mouseSelected(OptimizationItemWidget* pSelected);
    void viewMousePressEvent(QMouseEvent* e);
    int nSelectedObjects;
    int nTitleHeight;
    int activeObject;
    bool addNewOptItem(CCopasiObject* pObject);
  };

#endif // OptimizationWidget_H
