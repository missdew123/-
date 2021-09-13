#include "Dialog_Activate.h"
#include "ui_Dialog_Activate.h"

#include "DM_Element.h"

#include <QSettings>
#include <QDateTime>
#pragma execution_character_set("utf-8") //加了这句话之后，就不用QStringLiteral了

Dialog_Activate::Dialog_Activate(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Dialog_Activate)
{
	ui->setupUi(this);
	QCoreApplication::setOrganizationName(QString("DMWK"));//公司名
	QCoreApplication::setApplicationName(QString("VMP"));//软件名
	QSettings settings(QSettings::NativeFormat, QSettings::UserScope,
					   QCoreApplication::organizationName(), QCoreApplication::applicationName());

	QString license = settings.value("License").toString();
	QDateTime endDT;
	int type;
	bool isOK = false;
	if(!license.isNull())
	{
		isOK = decodeLicense(license, endDT, type);
	}


	if(isOK)
	{
		int daysToEnd = QDateTime::currentDateTime().daysTo(endDT);
		this->Status = type;
		switch(type)
		{
			case 0:{
				if(daysToEnd>0)
				{
					ui->Lbl_ShowActivateInfo->setText("下载版："+QString::number(daysToEnd)+"天");
				}
				else
				{
					ui->Lbl_ShowActivateInfo->setText("下载版：已过期");
				}
			}break;
			case 1:{
				if(daysToEnd>0)
				{
					ui->Lbl_ShowActivateInfo->setText("限时版："+QString::number(daysToEnd)+"天");
				}
				else
				{
					ui->Lbl_ShowActivateInfo->setText("限时版：已过期");
				}

			}break;
			case 2:{
				ui->Lbl_ShowActivateInfo->setText("正式版");
			}break;
			default:
			break;
		}
		if(daysToEnd>0)
		{

		}
	}
	else
	{
		this->Status = -1;
		ui->Lbl_ShowActivateInfo->setText("未激活");
	}
}

Dialog_Activate::~Dialog_Activate()
{
	delete ui;
}

int Dialog_Activate::getStatus()
{
	return Status;
}

void Dialog_Activate::on_Btn_Activate_clicked()
{
	QString license = ui->Edit_License->text();
	QDateTime endDT;
	int type;
	bool isOK = false;
	if(!license.isNull())
	{
		isOK = decodeLicense(license, endDT, type);
	}


	if(isOK)
	{
		int daysToEnd = QDateTime::currentDateTime().daysTo(endDT);
		this->Status = type;
		switch(type)
		{
			case 0:{
				if(daysToEnd>0)
				{
					ui->Lbl_ShowActivateInfo->setText("下载版："+QString::number(daysToEnd)+"天");
				}
				else
				{
					ui->Lbl_ShowActivateInfo->setText("下载版：已过期");
				}
			}break;
			case 1:{
				if(daysToEnd>0)
				{
					ui->Lbl_ShowActivateInfo->setText("限时版："+QString::number(daysToEnd)+"天");
				}
				else
				{
					ui->Lbl_ShowActivateInfo->setText("限时版：已过期");
				}

			}break;
			case 2:{
				ui->Lbl_ShowActivateInfo->setText("正式版");
			}break;
			default:
			break;
		}
		if(daysToEnd<=0)
		{
			this->Status = -1;
			ui->Lbl_ShowActivateInfo->setText("激活码过期");
			return;
		}
		QCoreApplication::setOrganizationName(QString("DMWK"));//公司名
		QCoreApplication::setApplicationName(QString("VMP"));//软件名
		QSettings settings(QSettings::NativeFormat, QSettings::UserScope,
						   QCoreApplication::organizationName(), QCoreApplication::applicationName());
		settings.setValue("License", ui->Edit_License->text());
	}
	else
	{
		ui->Lbl_ShowActivateInfo->setText("激活码无效");
		this->Status = -1;
	}
}








