#ifndef DIALOG_GETOPENPROJECTNAME_H
#define DIALOG_GETOPENPROJECTNAME_H

#include <QDialog>
#include <QDir>

namespace Ui {
	class Dialog_GetOpenProjectName;
}

class Dialog_GetOpenProjectName : public QDialog
{
		Q_OBJECT
	public:
		explicit Dialog_GetOpenProjectName(QWidget *parent = 0, const QString& title = "",
                                           const QString &path = QString(), QDir::Filters = QDir::NoFilter);
		~Dialog_GetOpenProjectName();
		bool getOpenName(QString& name);
        void setLoadMode();//设置加载模式
        void setNewMode();//设置新建模式
        void setDeleteMode();//设置删除模式
	private slots:
        void on_Btn_Load_clicked();
		void on_Btn_Cancel_clicked();
		void on_Btn_Delete_clicked();
        void on_Btn_New_clicked();
private:
		Ui::Dialog_GetOpenProjectName *ui;
        QString path;
		bool isOK;
};

#endif // DIALOG_GETOPENPROJECTNAME_H
