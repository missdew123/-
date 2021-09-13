#include "Dialog_GetOpenProjectName.h"
#include "ui_Dialog_GetOpenProjectName.h"

#include <QSettings>
#include <QDebug>
#include <QMessageBox>
#define qo qDebug()
#pragma execution_character_set("utf-8") //加了这句话之后，就不用QStringLiteral了

Dialog_GetOpenProjectName::Dialog_GetOpenProjectName(QWidget *parent, const QString& title,
                                                     const QString &path, QDir::Filters filter) :
	QDialog(parent),
	ui(new Ui::Dialog_GetOpenProjectName)
{
	ui->setupUi(this);
	this->setWindowTitle(title);
    this->path = path;
    this->isOK = false;
    QDir dir(this->path);
    if(!dir.exists())
    {
        return;
    }
    dir.setFilter(filter);
    dir.setSorting(QDir::DirsFirst);//文件夹排在前面
    QFileInfoList list = dir.entryInfoList();
    foreach(QFileInfo fileInfo, list)
    {
        if(fileInfo.fileName() == "." | fileInfo.fileName() == "..")
        {
            continue;
        }
        else
        {
            QListWidgetItem *imageItem = new QListWidgetItem;
            //为单元项设置属性
            imageItem->setIcon(QIcon(this->path+"/Folder.png"));
            imageItem->setText(fileInfo.fileName());
            //重新设置单元项图片的宽度和高度
            imageItem->setSizeHint(QSize(140, 120));
            imageItem->setData(Qt::UserRole, fileInfo.absoluteFilePath());

            //将单元项添加到QListWidget中
            ui->ListWdt_Projects->addItem(imageItem);
        }
    }
}

Dialog_GetOpenProjectName::~Dialog_GetOpenProjectName()
{
	delete ui;
}


bool Dialog_GetOpenProjectName::getOpenName(QString& name)
{
    if(this->isOK)
    {
        if(0<ui->ListWdt_Projects->count())
        {
//            name = ui->ListWdt_Projects->currentItem()->data(Qt::UserRole).toString();
            name = ui->ListWdt_Projects->currentItem()->text();

        }
        else
        {
            this->isOK = false;
            name.clear();
        }
    }
    return this->isOK;
}

void Dialog_GetOpenProjectName::setLoadMode()
{
    //隐藏新建相关的按钮
    ui->Btn_New->hide();
    ui->label_ProName->hide();
    ui->QLEdit_ProName->hide();
    //隐藏删除相关的按钮
    ui->Btn_Delete->hide();
}

void Dialog_GetOpenProjectName::setNewMode()
{
    //隐藏加载相关的按钮
    ui->Btn_Load->hide();
}

void Dialog_GetOpenProjectName::setDeleteMode()
{
    //隐藏新建相关的按钮
    ui->Btn_New->hide();
    ui->label_ProName->hide();
    ui->QLEdit_ProName->hide();

    //隐藏加载相关的按钮
    ui->Btn_Load->hide();
}

void Dialog_GetOpenProjectName::on_Btn_Load_clicked()
{
    this->isOK = true;
	this->close();
}

void Dialog_GetOpenProjectName::on_Btn_Cancel_clicked()
{
    //this->isOK = false;
	this->close();
}

void Dialog_GetOpenProjectName::on_Btn_Delete_clicked()
{
	if(0<ui->ListWdt_Projects->count())
	{
		QString proPath = ui->ListWdt_Projects->currentItem()->data(Qt::UserRole).toString();
		QString proName = ui->ListWdt_Projects->currentItem()->text();
		switch(QMessageBox::information(this, "删除确定", "是否删除 "+proName+" ？",
										"是", "否", nullptr, 1))
		{
            case 0:
            {
                QDir dir;
                dir.setPath(proPath);
                dir.removeRecursively();
				ui->ListWdt_Projects->takeItem(ui->ListWdt_Projects->currentRow());
            }
            break;
			case 1:
			default:break;
		}
	}
    this->isOK = false;
}

void Dialog_GetOpenProjectName::on_Btn_New_clicked()
{

    QString name = ui->QLEdit_ProName->text();
    if(name == "")
    {
        QMessageBox::warning(this, "新建工程", "请输入工程名!","确定");
        this->isOK = false;
    }
    else
    {
        //新建文件夹
        QDir dir(this->path);
        if (!dir.exists(name))//判断需要创建的文件夹是否存在
        {
            dir.mkdir(name); //创建文件夹
            //更新显示
            QListWidgetItem *imageItem = new QListWidgetItem;
            //为单元项设置属性
            imageItem->setIcon(QIcon(this->path+"/Folder.png"));
            imageItem->setText(name);
            //重新设置单元项图片的宽度和高度
            imageItem->setSizeHint(QSize(140, 120));
            imageItem->setData(Qt::UserRole,dir.absolutePath()+"/"+ name);

            //将单元项添加到QListWidget中
            ui->ListWdt_Projects->addItem(imageItem);
            ui->ListWdt_Projects->setCurrentItem(imageItem);//将新建的文件设置为当前目录
        }
        else//如果已经存在，直接删除所有文件，新建工程
        {
			//采用精准匹配，按照整个系统的设计，代码进入到这里有且仅有一个同名文件
            QList<QListWidgetItem*> sameNameWidget = ui->ListWdt_Projects->findItems(name,Qt::MatchExactly);
			if (sameNameWidget.size() > 0)
			{
				QListWidgetItem *Pwidget = sameNameWidget[0];
				ui->ListWdt_Projects->setCurrentItem(Pwidget);//将新建的文件设置为当前目录

				switch (QMessageBox::information(this, "替换确定", "是否替换 " + name + " ？",
					"是", "否", nullptr, 1))
				{
				case 0:
				{
					dir.setPath(this->path + "/" + name);
					dir.removeRecursively();//先删除

					dir.setPath(this->path);
					dir.mkdir(name); //创建文件夹
				}
				break;
				case 1:
				default:break;
				}
			}
        }
        this->isOK = true;
    }
}
