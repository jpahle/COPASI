/****************************************************************************
 ** Form interface generated from reading ui file '.\ObjectBrowser.ui'
 **
 ** Created: Tue Apr 22 13:27:37 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#ifndef OBJECTBROWSER_H
#define OBJECTBROWSER_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QPushButton;
class QListView;
class ObjectBrowserItem;
class objectList;
class QListViewItem;
class CCopasiContainer;
class CCopasiObject;
class ObjectBrowser : public QWidget
  {
    Q_OBJECT

  public:
    objectList* objectItemList;
    objectList* refreshList;
    ObjectBrowser(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ObjectBrowser();

    QPushButton* cancelButton;
    QPushButton* nextButton;
    QPushButton* backButton;
    QListView* ObjectListView;

    /*
     isSibling describe the level we need to overlook sibling
     0: overlook sibling
     else: n>0 or n<0, includign sibling
    */
    void setCheck(ObjectBrowserItem* pCurrent, int isSibling);
    void setUncheck(ObjectBrowserItem* pCurrent, int isSibling);
    void clickToReverseCheck(ObjectBrowserItem* pCurrent);
    void setCheckMark(ObjectBrowserItem* pCurrent);

    void loadData();
    void loadChild(ObjectBrowserItem* parent, CCopasiContainer * copaParent, bool nField);
    void loadField(ObjectBrowserItem* parent, CCopasiContainer * copaParent);
    // void loadVectors(ObjectBrowserItem* parent, CCopasiContainer * copaParent);
    CCopasiObject* getFieldCopasiObject(CCopasiObject* pCurrent, const char* name);

    void updateUI();
    void loadUI();
  public slots:
    virtual void cancelClicked();
    virtual void listviewChecked(QListViewItem*);
    virtual void backClicked();
    virtual void nextClicked();

  protected:
    QGridLayout* ObjectBrowserLayout;
  };
#endif // OBJECTBROWSER_H
