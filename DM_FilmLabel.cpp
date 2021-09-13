#include "DM_FilmLabel.h"

#include <QDebug>
#include <QFileInfo>
#define qo qDebug()

QString DefaultSS("border: 2px solid; "\
				  "border-radius: 3px; "\
				  "border-color: rgb(141, 141, 141, 255);");

QString CheckedSS("border: 2px solid; "\
				  "border-radius: 3px; "\
				  "border-color: rgb(255, 219, 66, 255);");



DM_FilmLabel::DM_FilmLabel(const QString& filePath, const QSize& size, const QSize& maxThumbSize, int index, QWidget* parent)
{
	setParent(parent);
	setAlignment(Qt::AlignHCenter|Qt::AlignTop);
	FilePath = filePath;
	QFileInfo fi(FilePath);//项目文件路径
	if(fi.exists() && index != -1)//如果文件存在
	{
		setStyleSheet(DefaultSS);
		Index = index;
		Thumb = QPixmap(filePath).scaled(maxThumbSize, Qt::KeepAspectRatio);
		IsValid = true;
	}
	else
	{
		setStyleSheet("border: 2px solid; "\
					  "border-radius: 3px; "\
					  "border-color: rgb(90, 90, 90, 255);");
		Thumb = QPixmap(maxThumbSize);
		Thumb.fill(QColor(54, 54, 54));
		IsValid = false;
	}
	setSize(size);
}

DM_FilmLabel::~DM_FilmLabel()
{
	disconnect(this, &DM_Film::checked, 0, 0);
//	qo<<Index<<"dis :"<<disconnect(this, &DM_Film::checked, 0, 0);
}


void DM_FilmLabel::setSize(const QSize& size)
{
	setFixedSize(size);
	setPixmap(Thumb.scaled(size));
}



void DM_FilmLabel::setChecked(bool checked)
{
	IsChecked = checked;
//	qo<<Index<<IsChecked;
	if(IsChecked)
	{
		setStyleSheet(CheckedSS);
		IsChecked = true;
		emit this->checked(Index);
	}
	else
	{
		setStyleSheet(DefaultSS);
		IsChecked = false;
	}
}



bool DM_FilmLabel::isValid() const
{
	//以后可改为检查文件是否存在
	return IsValid;
}

QString DM_FilmLabel::getFilePath() const
{
	return FilePath;
}

int DM_FilmLabel::getIndex() const
{
	return Index;
}



void DM_FilmLabel::mouseReleaseEvent(QMouseEvent* ev)
{
	if(IsValid)
	{
		setChecked(true);
	}
	else
	{
		emit this->checked(-1);
	}
}
