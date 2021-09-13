#include "Dialog_GetProjectName.h"
#include "ui_Dialog_GetProjectName.h"

#include <QDebug>
#define qo qDebug()



Dialog_GetProjectName::Dialog_GetProjectName(QWidget *parent, const QString& title) :
	QDialog(parent),
	ui(new Ui::Dialog_GetProjectName)
{
	ui->setupUi(this);
	this->setWindowTitle(title);
	isOK = false;
}

Dialog_GetProjectName::~Dialog_GetProjectName()
{
	delete ui;
}

bool Dialog_GetProjectName::getText(QString& text)
{
	text = ui->lineEdit->text();
	return isOK;
}

void Dialog_GetProjectName::on_Btn_Save_clicked()
{
	isOK = true;
	this->close();
}

void Dialog_GetProjectName::on_Btn_Cancel_clicked()
{
	isOK = false;
	this->close();
}

