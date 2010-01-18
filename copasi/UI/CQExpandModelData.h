// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQExpandModelData.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2009/12/14 12:54:47 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEXPANDMODELDATA_H
#define CQEXPANDMODELDATA_H

#include <qvariant.h>
#include <string>
#include <vector>

//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3GridLayout>
#include <QPixmap>
#include <Q3VBoxLayout>

class QSignalMapper;

#include <QtGui/QDialog>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <Qt3Support/Q3VBoxLayout>
#include <QtGui/QWidget>
#include <QToolButton>

#include "model/CModel.h"

#include "ui_CQExpandModelData.h"

class CQExpandModelData : public QDialog, public Ui::CQExpandModelData
{
  Q_OBJECT

public:
  CQExpandModelData(QWidget* parent = 0, Qt::WindowFlags fl = 0);
  ~CQExpandModelData();

  std::vector< std::string > mCompartmentName;

protected:
  QSignalMapper * mpComboMap;
  CModel* pModel;

protected slots:
  void slotCompartmentChanged(/* int row */);

private:
  void load();
private slots:
  void slotOK();
  void slotCancel();
};

#endif // CQEXPANDMODELDATA_H