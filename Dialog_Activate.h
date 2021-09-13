#ifndef DIALOG_ACTIVATE_H
#define DIALOG_ACTIVATE_H

#include <QDialog>

namespace Ui {
	class Dialog_Activate;
}

class Dialog_Activate : public QDialog
{
		Q_OBJECT
	public:
		explicit Dialog_Activate(QWidget *parent = 0);
		~Dialog_Activate();
		int getStatus();

	private slots:
		void on_Btn_Activate_clicked();

	private:
		Ui::Dialog_Activate *ui;
		int Status;
};







#endif // DIALOG_ACTIVATE_H
