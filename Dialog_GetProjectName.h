#ifndef DIALOG_GETPROJECTNAME_H
#define DIALOG_GETPROJECTNAME_H

#include <QDialog>


namespace Ui {
	class Dialog_GetProjectName;
}

class Dialog_GetProjectName : public QDialog
{
		Q_OBJECT
	public:
		explicit Dialog_GetProjectName(QWidget *parent = 0, const QString& title = "");
		~Dialog_GetProjectName();
		bool getText(QString& text);

	private slots:
		void on_Btn_Save_clicked();
		void on_Btn_Cancel_clicked();

	private:
		Ui::Dialog_GetProjectName *ui;
		bool isOK;
};





#endif // DIALOG_GETPROJECTNAME_H
