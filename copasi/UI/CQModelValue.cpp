// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQModelValue.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/09/14 15:29:50 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQModelValue.ui'
 **
 ** Created: Wed Sep 12 16:08:25 2007
 **      by: The User Interface Compiler ($Id: CQModelValue.cpp,v 1.4 2007/09/14 15:29:50 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQModelValue.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qtoolbutton.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "CQExpressionWidget.h"
#include "CQModelValue.ui.h"
static const unsigned char image0_data[] =
  {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x02,
    0x5c, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xa5, 0x93, 0x4d, 0x4f, 0x13,
    0x71, 0x10, 0x87, 0x9f, 0xff, 0xee, 0xd6, 0xd6, 0xb6, 0xdb, 0x52, 0x5a,
    0x40, 0x81, 0x16, 0x85, 0x5a, 0x5e, 0x04, 0xa2, 0xa9, 0x26, 0x26, 0x98,
    0x88, 0x89, 0x07, 0xaf, 0xc6, 0x0f, 0xe8, 0x47, 0xc0, 0x98, 0x78, 0x30,
    0x6a, 0x0c, 0x97, 0x62, 0xc4, 0x82, 0xc8, 0x6b, 0x63, 0x43, 0xaa, 0xa0,
    0xad, 0x5d, 0xe8, 0xf2, 0x62, 0x29, 0xdd, 0x6d, 0x3b, 0x1e, 0x10, 0x22,
    0x41, 0xf4, 0xe0, 0x9c, 0x26, 0x33, 0xf3, 0xfc, 0x0e, 0xbf, 0x99, 0x51,
    0x99, 0x4c, 0x86, 0xff, 0x09, 0xe3, 0x6f, 0x4d, 0x9f, 0xaf, 0x2c, 0xae,
    0xab, 0x61, 0xdb, 0x65, 0xb6, 0xb6, 0x2a, 0x78, 0xbd, 0x06, 0x3d, 0x3d,
    0x77, 0xd4, 0x3f, 0x05, 0x4c, 0xd3, 0x96, 0x4a, 0xe5, 0x80, 0x6c, 0xb6,
    0x40, 0xa1, 0x50, 0xc7, 0xeb, 0x15, 0x62, 0x31, 0x61, 0x60, 0x20, 0x4a,
    0x38, 0x5c, 0x91, 0xdd, 0xdd, 0x76, 0x75, 0xae, 0x80, 0xcf, 0x57, 0x97,
    0xf9, 0xf9, 0x0d, 0xe6, 0xe6, 0x2c, 0x82, 0x41, 0xc5, 0xc4, 0x44, 0x37,
    0x89, 0x44, 0x02, 0x91, 0x1f, 0x18, 0x86, 0xf0, 0x3b, 0x7c, 0x46, 0xc0,
    0xb6, 0xbf, 0xca, 0xcc, 0xcc, 0x67, 0x2c, 0xeb, 0x80, 0x64, 0xd2, 0xc3,
    0xe8, 0x68, 0x2f, 0xe1, 0xf0, 0x80, 0x72, 0x1c, 0x00, 0x3f, 0xae, 0xfb,
    0x17, 0x0f, 0xf2, 0xf9, 0x9c, 0x64, 0xe7, 0x4a, 0x04, 0xfc, 0x1a, 0x93,
    0x93, 0x7d, 0xf4, 0xf5, 0x5d, 0x53, 0x67, 0xc7, 0xcf, 0x11, 0xc8, 0xe7,
    0xd7, 0x64, 0x61, 0xe1, 0x3b, 0x83, 0xa9, 0x20, 0xe9, 0xf4, 0x75, 0x9a,
    0x4d, 0xdf, 0x29, 0x38, 0xac, 0xd6, 0x44, 0x73, 0x04, 0x6b, 0x7d, 0x95,
    0xda, 0x4e, 0x85, 0x50, 0x7b, 0x94, 0xee, 0xe1, 0x34, 0x5f, 0x1b, 0x09,
    0x65, 0x94, 0x4a, 0x39, 0xc9, 0x66, 0xbf, 0x91, 0x4c, 0x06, 0x19, 0x1b,
    0xeb, 0x3a, 0x05, 0x07, 0xdc, 0x05, 0xd9, 0x2f, 0x16, 0x59, 0x5a, 0x5a,
    0xa2, 0xb4, 0xd1, 0xc4, 0xda, 0x0f, 0x50, 0x6f, 0x18, 0xb4, 0x7b, 0x3e,
    0x71, 0x75, 0x3e, 0xc7, 0xed, 0xc7, 0x0f, 0xc4, 0x98, 0x9d, 0x9d, 0xc7,
    0x34, 0x03, 0xa4, 0x52, 0x09, 0x74, 0xbd, 0xf7, 0x04, 0xbe, 0xb0, 0xf1,
    0x42, 0x16, 0x3f, 0xac, 0x91, 0x2b, 0x18, 0x78, 0xc2, 0x31, 0xe2, 0x63,
    0x6d, 0xdc, 0x1c, 0xe9, 0xc7, 0x17, 0x08, 0x52, 0xdb, 0xb6, 0xc9, 0x3e,
    0x7f, 0x49, 0x7e, 0xe6, 0x15, 0x86, 0x65, 0xd9, 0x8c, 0x8f, 0xb7, 0x61,
    0x9a, 0xc9, 0x13, 0x58, 0xcf, 0x3f, 0x93, 0x77, 0xaf, 0x57, 0xd8, 0xb9,
    0x18, 0x65, 0xf0, 0x5e, 0x92, 0xc1, 0xf1, 0x1b, 0xb8, 0x44, 0x14, 0x40,
    0x03, 0xd0, 0xcd, 0x4d, 0xb1, 0x1b, 0x21, 0x76, 0xec, 0x6f, 0x67, 0xd7,
    0x98, 0x08, 0x94, 0xe5, 0xcd, 0xdb, 0x45, 0x0e, 0x82, 0x31, 0x26, 0x1f,
    0x3d, 0x04, 0x7f, 0x5c, 0xfd, 0x6e, 0xbe, 0x6e, 0xbd, 0x97, 0xcc, 0xf4,
    0x3a, 0x5e, 0xd1, 0xb8, 0x9c, 0x7e, 0x88, 0xd1, 0xd1, 0x11, 0xa1, 0x54,
    0x72, 0xb0, 0xac, 0x15, 0xe9, 0xe8, 0x18, 0x51, 0xf5, 0xba, 0xcd, 0x8f,
    0xea, 0x01, 0xa1, 0x78, 0x83, 0x20, 0x45, 0xcc, 0xe6, 0xb6, 0xb4, 0x9a,
    0x0d, 0xaa, 0xd5, 0x2a, 0x85, 0x8f, 0xab, 0x7c, 0x59, 0x2c, 0x72, 0xa8,
    0x5d, 0x62, 0xfc, 0xfe, 0x18, 0x46, 0xf7, 0x5d, 0xa5, 0xa6, 0xa6, 0x9e,
    0xc8, 0xf4, 0xf4, 0x17, 0xa2, 0x51, 0x97, 0x91, 0xe1, 0x5e, 0xa2, 0xa1,
    0x06, 0x9b, 0xb3, 0x4f, 0x29, 0xe7, 0xca, 0x38, 0xc5, 0x0b, 0x38, 0x7b,
    0xa0, 0xeb, 0x1a, 0x8e, 0x3f, 0x42, 0x35, 0x10, 0xa3, 0x2b, 0xd5, 0xc6,
    0xc8, 0xad, 0x21, 0x22, 0xf1, 0xb4, 0x02, 0x50, 0x99, 0x4c, 0x86, 0x5a,
    0xad, 0x20, 0xcb, 0xcb, 0x6b, 0x2c, 0x2f, 0x7b, 0xa8, 0x1f, 0x2a, 0xdc,
    0x9a, 0x8d, 0xb3, 0x5f, 0xa7, 0xbe, 0x27, 0xe8, 0x2d, 0xa1, 0x27, 0x2e,
    0xa4, 0x46, 0x4d, 0xae, 0x0c, 0xc5, 0x69, 0xef, 0x8a, 0xa0, 0x79, 0xfa,
    0x4f, 0xfc, 0x52, 0xc7, 0xdf, 0xe8, 0xf1, 0x6c, 0x8a, 0xeb, 0x7a, 0x68,
    0xb5, 0xe4, 0xa8, 0xd3, 0x82, 0x96, 0x80, 0xae, 0x0c, 0xfc, 0xc1, 0x10,
    0xd2, 0xda, 0xe1, 0xd0, 0xe9, 0x3c, 0x73, 0x5c, 0x27, 0x26, 0xba, 0xee,
    0xd1, 0x0a, 0x35, 0xed, 0x57, 0x41, 0x83, 0xe3, 0xb4, 0x76, 0x08, 0xd0,
    0xf9, 0xc7, 0x4b, 0xfc, 0x09, 0x52, 0xcb, 0x07, 0x62, 0x36, 0x43, 0x92,
    0xc6, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60,
    0x82
  };

/*
 *  Constructs a CQModelValue which is a child of 'parent', with the
 *  name 'name'.'
 */
CQModelValue::CQModelValue(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  QImage img;
  img.loadFromData(image0_data, sizeof(image0_data), "PNG");
  image0 = img;
  if (!name)
    setName("CQModelValue");
  CQModelValueLayout = new QVBoxLayout(this, 11, 6, "CQModelValueLayout");

  layout7 = new QGridLayout(0, 1, 1, 0, 6, "layout7");

  mpEditRate = new QLineEdit(this, "mpEditRate");
  mpEditRate->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, mpEditRate->sizePolicy().hasHeightForWidth()));
  mpEditRate->setFrameShape(QLineEdit::LineEditPanel);
  mpEditRate->setFrameShadow(QLineEdit::Sunken);
  mpEditRate->setReadOnly(TRUE);

  layout7->addWidget(mpEditRate, 5, 2);

  mpLblRate = new QLabel(this, "mpLblRate");
  mpLblRate->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)5, 0, 0, mpLblRate->sizePolicy().hasHeightForWidth()));
  mpLblRate->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout7->addWidget(mpLblRate, 5, 0);

  mpLblCurrentValue = new QLabel(this, "mpLblCurrentValue");
  mpLblCurrentValue->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignLeft));

  layout7->addWidget(mpLblCurrentValue, 3, 2);

  mpLblExpression = new QLabel(this, "mpLblExpression");
  mpLblExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)5, 0, 0, mpLblExpression->sizePolicy().hasHeightForWidth()));
  mpLblExpression->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  layout7->addWidget(mpLblExpression, 6, 0);

  mpLblType = new QLabel(this, "mpLblType");
  mpLblType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)5, 0, 0, mpLblType->sizePolicy().hasHeightForWidth()));
  mpLblType->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout7->addWidget(mpLblType, 1, 0);

  mpEditName = new QLineEdit(this, "mpEditName");
  mpEditName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, mpEditName->sizePolicy().hasHeightForWidth()));
  mpEditName->setFrameShape(QLineEdit::LineEditPanel);
  mpEditName->setFrameShadow(QLineEdit::Sunken);

  layout7->addMultiCellWidget(mpEditName, 0, 0, 1, 2);

  mpEditInitialValue = new QLineEdit(this, "mpEditInitialValue");
  mpEditInitialValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, mpEditInitialValue->sizePolicy().hasHeightForWidth()));
  mpEditInitialValue->setFrameShape(QLineEdit::LineEditPanel);
  mpEditInitialValue->setFrameShadow(QLineEdit::Sunken);

  layout7->addWidget(mpEditInitialValue, 4, 1);

  mpLblName = new QLabel(this, "mpLblName");
  mpLblName->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)5, 0, 0, mpLblName->sizePolicy().hasHeightForWidth()));
  mpLblName->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout7->addWidget(mpLblName, 0, 0);

  mpLblInitialValue = new QLabel(this, "mpLblInitialValue");
  mpLblInitialValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)5, 0, 0, mpLblInitialValue->sizePolicy().hasHeightForWidth()));
  mpLblInitialValue->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignLeft));

  layout7->addWidget(mpLblInitialValue, 3, 1);

  mpLblValue = new QLabel(this, "mpLblValue");
  mpLblValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)1, (QSizePolicy::SizeType)5, 0, 0, mpLblValue->sizePolicy().hasHeightForWidth()));
  mpLblValue->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout7->addWidget(mpLblValue, 4, 0);

  layout6 = new QHBoxLayout(0, 0, 6, "layout6");

  mpEditExpression = new CQExpressionWidget(this, "mpEditExpression");
  layout6->addWidget(mpEditExpression);

  mpVBoxLayout = new QVBoxLayout(0, 0, 6, "mpVBoxLayout");

  mpBtnObject = new QToolButton(this, "mpBtnObject");
  mpBtnObject->setMaximumSize(QSize(20, 20));
  mpBtnObject->setIconSet(QIconSet(image0));
  mpVBoxLayout->addWidget(mpBtnObject);
  mpSpacerObject = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
  mpVBoxLayout->addItem(mpSpacerObject);
  layout6->addLayout(mpVBoxLayout);

  layout7->addMultiCellLayout(layout6, 6, 6, 1, 2);

  mpEditCurrentValue = new QLineEdit(this, "mpEditCurrentValue");
  mpEditCurrentValue->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, mpEditCurrentValue->sizePolicy().hasHeightForWidth()));
  mpEditCurrentValue->setFrameShape(QLineEdit::LineEditPanel);
  mpEditCurrentValue->setFrameShadow(QLineEdit::Sunken);
  mpEditCurrentValue->setReadOnly(TRUE);

  layout7->addWidget(mpEditCurrentValue, 4, 2);

  mpComboBoxType = new QComboBox(FALSE, this, "mpComboBoxType");
  mpComboBoxType->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, mpComboBoxType->sizePolicy().hasHeightForWidth()));

  layout7->addWidget(mpComboBoxType, 1, 1);

  mpLine1 = new QFrame(this, "mpLine1");
  mpLine1->setFrameShape(QFrame::HLine);
  mpLine1->setFrameShadow(QFrame::Sunken);
  mpLine1->setFrameShape(QFrame::HLine);

  layout7->addMultiCellWidget(mpLine1, 2, 2, 0, 2);
  CQModelValueLayout->addLayout(layout7);
  mpSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQModelValueLayout->addItem(mpSpacer);

  mpLine2 = new QFrame(this, "mpLine2");
  mpLine2->setFrameShape(QFrame::HLine);
  mpLine2->setFrameShadow(QFrame::Sunken);
  mpLine2->setFrameShape(QFrame::HLine);
  CQModelValueLayout->addWidget(mpLine2);

  mpBtnLayout = new QHBoxLayout(0, 0, 6, "mpBtnLayout");

  mpBtnCommit = new QPushButton(this, "mpBtnCommit");
  mpBtnLayout->addWidget(mpBtnCommit);

  mpBtnRevert = new QPushButton(this, "mpBtnRevert");
  mpBtnLayout->addWidget(mpBtnRevert);

  mpBtnNew = new QPushButton(this, "mpBtnNew");
  mpBtnLayout->addWidget(mpBtnNew);

  mpBtnDelete = new QPushButton(this, "mpBtnDelete");
  mpBtnLayout->addWidget(mpBtnDelete);
  CQModelValueLayout->addLayout(mpBtnLayout);
  languageChange();
  resize(QSize(366, 251).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpComboBoxType, SIGNAL(activated(int)), this, SLOT(slotTypeChanged(int)));
  connect(mpBtnCommit, SIGNAL(clicked()), this, SLOT(slotBtnCommit()));
  connect(mpBtnRevert, SIGNAL(clicked()), this, SLOT(slotBtnRevert()));
  connect(mpBtnNew, SIGNAL(clicked()), this, SLOT(slotBtnNew()));
  connect(mpBtnDelete, SIGNAL(clicked()), this, SLOT(slotBtnDelete()));
  connect(mpBtnObject, SIGNAL(clicked()), mpEditExpression, SLOT(slotSelectObject()));
  connect(mpEditExpression, SIGNAL(valid(bool)), this, SLOT(slotExpressionValid(bool)));
  connect(mpEditName, SIGNAL(lostFocus()), this, SLOT(slotNameLostFocus()));

  // tab order
  setTabOrder(mpEditName, mpComboBoxType);
  setTabOrder(mpComboBoxType, mpEditInitialValue);
  setTabOrder(mpEditInitialValue, mpEditCurrentValue);
  setTabOrder(mpEditCurrentValue, mpEditRate);
  setTabOrder(mpEditRate, mpEditExpression);
  setTabOrder(mpEditExpression, mpBtnObject);
  setTabOrder(mpBtnObject, mpBtnCommit);
  setTabOrder(mpBtnCommit, mpBtnRevert);
  setTabOrder(mpBtnRevert, mpBtnNew);
  setTabOrder(mpBtnNew, mpBtnDelete);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQModelValue::~CQModelValue()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQModelValue::languageChange()
{
  setCaption(tr("Global Quantity"));
  mpLblRate->setText(tr("Rate"));
  mpLblCurrentValue->setText(tr("Transient Values"));
  mpLblExpression->setText(tr("Expression"));
  mpLblType->setText(tr("Type"));
  mpLblName->setText(tr("Global Quantity Name"));
  mpLblInitialValue->setText(tr("Initial Values"));
  mpLblValue->setText(tr("Value"));
  mpBtnObject->setText(QString::null);
  mpBtnObject->setTextLabel(tr("select"));
  mpBtnCommit->setText(tr("Commit"));
  mpBtnRevert->setText(tr("Revert"));
  mpBtnNew->setText(tr("New"));
  mpBtnDelete->setText(tr("Delete"));
}
