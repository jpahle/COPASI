/****************************************************************************
**  $ CopasiUI/MoietyWidget.h               
**  $ Author  : Mudita Singhal
**  
** This is the header file for the Moiety Widget, i.e the First level 
** of Moieties.
*****************************************************************************/

#ifndef MOIETY_WIDGET_H
#define MOIETY_WIDGET_H

#include <qtable.h>
#include <qpushbutton.h> 
#include "MyTable.h"
#include "copasi.h"
#include "model/model.h"
class CModel;
class MoietyWidget : public QWidget
{
	Q_OBJECT
protected:
	CModel *mModel;
	MyTable *table;	
	QPushButton *btnOK;
	QPushButton *btnCancel;
	

public:
	MoietyWidget(QWidget *parent, const char * name=0, WFlags f=0);
	void loadMoieties(CModel *model);
	void mousePressEvent( QMouseEvent * e );
	void resizeEvent( QResizeEvent * re);

protected slots:
    virtual void slotTableClicked( int row, int col, int button, const QPoint & mousePos );
	virtual void slotTableCurrentChanged( int row, int col );
	virtual void slotTableSelectionChanged();
	virtual void slotBtnOKClicked();
	virtual void slotBtnCancelClicked();
	


};

#endif
