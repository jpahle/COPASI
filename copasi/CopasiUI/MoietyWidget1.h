/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/MoietyWidget1.h,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:12:55 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/MoietyWidget1.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Moiety Widget, i.e the second level 
 ** of Moieties.
 *****************************************************************************/ 
/*
 reimplement UI to automatically change internal components size
 Author: Liang Xu
 */

#ifndef MOIETYWIDGET1_H
#define MOIETYWIDGET1_H

#include <qvariant.h>
#include <qwidget.h>
#include "copasiWidget.h"
#include <qtextbrowser.h>
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class CModel;
class MoietyWidget1 : public CopasiWidget
  {
    Q_OBJECT

  public:
    MoietyWidget1(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~MoietyWidget1();
    CModel *mModel;
    void loadMoieties(CModel *model);
    void loadName(QString setValue);
    int isName(QString setValue);
    QString *Moiety1_Name;

    QLabel* TextLabel1;
    QLineEdit* LineEdit2;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLineEdit* LineEdit3;
    QTextBrowser* textBrowser;

    //By G
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void slotBtnCancelClicked();
    virtual void slotBtnOKClicked();

  signals:
    void signal_emitted(const QString &);
    void leaf(CModel*);
    void updated();

  protected:
    QGridLayout* MoietyWidget1Layout;

    bool loadFromMoiety(const CMoiety *); //By
    std::string objKey; //By G
  };

#endif // MOIETYWIDGET1_H
