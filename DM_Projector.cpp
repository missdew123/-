#include "DM_Projector.h"
#include "DM_FilmLabel.h"

#include <QResizeEvent>
#include <QApplication>


#include <QButtonGroup>
#include <QDebug>
#include <QDir>
#define qo qDebug()


const int MinSizeTime = 1;
const int MaxSizeTime = 5;
const QSize FilmBaseSize(36, 27);
const QSize FilmMaxSize = FilmBaseSize * MaxSizeTime;

DM_Projector::DM_Projector(QWidget* parent)
{
	setParent(parent);
	Wdt_Films        = nullptr;
	Btn_PlayFilm     = nullptr;
	Btn_PlayFirst    = nullptr;
	Btn_PlayPrevious = nullptr;
	Btn_PlayNext     = nullptr;
	Btn_PlayFinal    = nullptr;
	LO_Films         = nullptr;
	Lbl_FilmsInfo    = nullptr;
	CurrentFilmIndex = -1;
	StartIndex = 0;
}

DM_Projector::~DM_Projector()
{
	while(false == Films.empty())
	{
		delete Films.back();
		Films.pop_back();
	}
}

void DM_Projector::setButtons(QToolButton* playFilmBtn, QToolButton* playFirstBtn, QToolButton* playPreviousBtn,
							  QToolButton* playNextBtn, QToolButton* playFinalBtn)
{
	delete Btn_PlayFilm;
	delete Btn_PlayFirst;
	delete Btn_PlayPrevious;
	delete Btn_PlayNext;
	delete Btn_PlayFinal;
	Btn_PlayFilm     = playFilmBtn;
	Btn_PlayFirst    = playFirstBtn;
	Btn_PlayPrevious = playPreviousBtn;
	Btn_PlayNext     = playNextBtn;
	Btn_PlayFinal    = playFinalBtn;
}

bool DM_Projector::initProjector()
{
	if(nullptr == Btn_PlayFilm||
	   nullptr == Btn_PlayFirst||
	   nullptr == Btn_PlayPrevious||
	   nullptr == Btn_PlayNext||
	   nullptr == Btn_PlayFinal)
	{
		return false;
	}

	FlowLayout* flowLayout = new FlowLayout;
//	flowLayout->setMargin(3);
//	flowLayout->setSpacing(3);
	flowLayout->addWidget(Btn_PlayFirst);
	flowLayout->addWidget(Btn_PlayPrevious);
	flowLayout->addWidget(Btn_PlayNext);
	flowLayout->addWidget(Btn_PlayFinal);
	flowLayout->addWidget(Btn_PlayFilm);//播放按钮放到最后
    flowLayout->setContentsMargins(0,0,0,0);
	Btn_PlayFilm->setVisible(false);//隐藏 不需要这个功能

	Wdt_Films = new QWidget(this);
	Lbl_FilmsInfo = new QLabel("", this);
	Lbl_FilmsInfo->setAlignment(Qt::AlignLeft);

	QVBoxLayout* vLayout = new QVBoxLayout();
	vLayout->addWidget(Lbl_FilmsInfo);
	vLayout->addWidget(Wdt_Films);
	vLayout->addLayout(flowLayout);
	vLayout->setStretch(0, 0);
	vLayout->setStretch(1, 1);
	vLayout->setStretch(2, 0);
//	vLayout->setSpacing(5);
    vLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(vLayout);


	connect(Btn_PlayFilm, &QToolButton::clicked, this, &DM_Projector::on_Btn_PlayFilm_clicked);
	connect(Btn_PlayFirst, &QToolButton::clicked, this, &DM_Projector::on_Btn_PlayFirst_clicked);
	connect(Btn_PlayPrevious, &QToolButton::clicked, this, &DM_Projector::on_Btn_PlayPrevious_clicked);
	connect(Btn_PlayNext, &QToolButton::clicked, this, &DM_Projector::on_Btn_PlayNext_clicked);
	connect(Btn_PlayFinal, &QToolButton::clicked, this, &DM_Projector::on_Btn_PlayFinal_clicked);

	LO_Films = new QVBoxLayout(Wdt_Films);
	LO_Films->setSpacing(0);
	LO_Films->setContentsMargins(0, 0, 0, 0);
	SP_Films = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

	StartIndex = 0;
	CurrentFilmIndex = -1;
	CurrentTime = -1;
	CurrentCount = -1;



	return true;
}

bool DM_Projector::setFolderPath(const QDir& folderPath)
{
	FolderPath = folderPath;
	//打开文件夹下所有图像 把缩略图存到内存中
	QStringList filter;
	filter << "*.jpg" << "*.bmp" << "*.png" << "*.jpeg"<< "*.tiff"; //过滤图片文件拓展名
	QStringList fileNameList = FolderPath.entryList(filter);
	int count = fileNameList.size();
	if(count<=0)
	{
		return false;
	}

	StartIndex = 0;
	CurrentFilmIndex = -1;
	CurrentTime = -1;
	CurrentCount = -1;
	Lbl_FilmsInfo->setText("");

	//断开连接 删除对象
	while(false == Films.empty())
	{
		disconnect(Films.back());
		delete Films.back();
		Films.pop_back();
	}

	for(int i = 0; i<count; ++i)
	{
		QString tempFilePath = FolderPath.absolutePath()+"/"+ fileNameList.at(i);
		DM_Film* tempFilm = new DM_Film(tempFilePath, FilmBaseSize, FilmMaxSize, i);
		connect(tempFilm, &DM_Film::checked, this, &DM_Projector::on_Films_checked);
		Films.push_back(tempFilm);
	}

	updateFilms();
	return true;
}

void DM_Projector::clearFilms()
{
	StartIndex = 0;
	CurrentFilmIndex = -1;
	CurrentTime = -1;
	CurrentCount = -1;
	Lbl_FilmsInfo->setText("");

	//断开连接 删除对象
	while(false == Films.empty())
	{
		disconnect(Films.back());
		delete Films.back();
		Films.pop_back();
	}
	updateFilms();//刷新
}

void DM_Projector::updateFilms()
{
	if(nullptr == LO_Films) return;

	//根据Wdt大小计算可以放下的Film的大小和张数
	//通过宽度计算大小倍率
	int sizeTime = Wdt_Films->width()/FilmBaseSize.width();
	if(MinSizeTime > sizeTime) sizeTime = MinSizeTime;//让倍率只在1到5
	if(MaxSizeTime < sizeTime) sizeTime = MaxSizeTime;
	QSize size = FilmBaseSize*sizeTime;

	//通过高度计算能够放下的film的张数 实际能够显示可能不足，但是用空的film填满
	int newCount = Wdt_Films->height()/size.height();

	if(CurrentTime != sizeTime || CurrentCount != newCount)//需要更新
	{
		clearLabels();//清空原有显示的label
		int count = Films.size();
		for(int i = 0; i<newCount; ++i)
		{
			if(i<count)
			{
				Films[i]->setSize(size);
				addLabel(Films[i]);
			}
			else
			{
				DM_Film* tempFilm = new DM_Film(QString::number(i), size, FilmMaxSize);//临时占空的film 不需要连接槽函数
				addLabel(tempFilm);
			}
		}

		LO_Films->addSpacerItem(SP_Films);
		CurrentTime = sizeTime;
		CurrentCount = newCount;
	}
}


void DM_Projector::updateFilms(int startIndex)
{
	if(nullptr == LO_Films) return;

	int sizeTime = Wdt_Films->width()/FilmBaseSize.width();
	if(MinSizeTime > sizeTime) sizeTime = MinSizeTime;//让倍率只在1到5
	if(MaxSizeTime < sizeTime) sizeTime = MaxSizeTime;
	QSize size = FilmBaseSize*sizeTime;

	if(StartIndex != startIndex)//需要更新
	{
		clearLabels();//清空原有显示的label
		int count = Films.size();

		for(int i = startIndex; i<CurrentCount+startIndex; ++i)
		{
			if(i<count)
			{
				Films[i]->setSize(size);
				addLabel(Films[i]);
			}
			else
			{
				DM_Film* tempFilm = new DM_Film(QString::number(i), size, FilmMaxSize);//临时占空的film 不需要连接槽函数
				addLabel(tempFilm);
			}
		}

		LO_Films->addSpacerItem(SP_Films);
		StartIndex = startIndex;
	}
}



void DM_Projector::addLabel(DM_Film* film)
{
	LO_Films->addWidget(film);
}

void DM_Projector::clearLabels()
{
	//清空Layout布局内的所有元素
	QLayoutItem *child;
	if((child = LO_Films->takeAt(LO_Films->children().size() - 1)) != 0)//这个应该是spacerItem
	{
		if(child->widget())//setParent为nullptr，防止删除之后界面不消失
		{
			child->widget()->setParent(nullptr);
		}
	}
	while((child = LO_Films->takeAt(0)) != 0)//去除胶片
	{
		if(child->widget())//setParent为nullptr，防止删除之后界面不消失
		{
			DM_Film* tempFilm = dynamic_cast<DM_Film*>(child->widget());
			tempFilm->setParent(nullptr);
			if(false == tempFilm->isValid())//只有占空的film需要删除, 空的film isValid是false
			{
				delete tempFilm;//必须要转成对应类型的指针才能delete
			}
		}
	}
}

void DM_Projector::resizeEvent(QResizeEvent* ev)
{
	//根据比例计算需要显示的FilmLabel的个数
	updateFilms();
}

void DM_Projector::on_Btn_PlayFinal_clicked()
{
//	qo<<"btn final";
	if(0 == Films.size()) return;
	Films[Films.size()-1]->setChecked(true);
}

void DM_Projector::on_Btn_PlayNext_clicked()
{
//	qo<<"btn next";
	if(0 == Films.size()) return;
	int nextIndex = CurrentFilmIndex+1;
	if(nextIndex>Films.size()-1) nextIndex = 0;//大于最后一张，跳转到第一张
	Films[nextIndex]->setChecked(true);
}

void DM_Projector::on_Btn_PlayPrevious_clicked()
{
//	qo<<"btn prev";
	if(0 == Films.size()) return;
	int prevIndex = CurrentFilmIndex-1;
	if(prevIndex<0) prevIndex = Films.size()-1;//小于第一张，跳转到最后一张
	Films[prevIndex]->setChecked(true);
}

void DM_Projector::on_Btn_PlayFirst_clicked()
{
//	qo<<"btn first";
	if(0 == Films.size()) return;
	Films[0]->setChecked(true);
}

void DM_Projector::on_Btn_PlayFilm_clicked()
{
//	qo<<"btn film";
}

void DM_Projector::on_Films_checked(int index)
{
	if(CurrentFilmIndex == index)
	{
		return;
	}
	//先将当前选中的film设置为未选中
	if(-1<CurrentFilmIndex && CurrentFilmIndex<Films.size())
	{
		Films[CurrentFilmIndex]->setChecked(false);
	}

	CurrentFilmIndex = index;

	//根据CurrentFilmIndex和图片显示张数还有StartIndex 计算当前StartIndex
	//当CurrentFilmIndex在当前显示的所有film中时，不需要更新现有显示
	//CurrentFilmIndex小于newCount时，从CurrentFilmIndex开始，即让currentIndex显示在第一张
	//CurrentFilmIndex大于newCount时，从count - newCount开始，即让currentIndex显示在最后一张

	if(-1 == CurrentFilmIndex)
	{
		Lbl_FilmsInfo->setText("");
	}
	else
	{
		if(CurrentFilmIndex<StartIndex)
		{
			updateFilms(CurrentFilmIndex);
		}
		else if(CurrentFilmIndex > StartIndex+CurrentCount-1)
		{
			updateFilms(CurrentFilmIndex-CurrentCount+1);
		}


		Lbl_FilmsInfo->setText(QString("(%1/%2)").arg(QString::number(CurrentFilmIndex+1), QString::number(Films.size())));
		emit triggerOnce(Films[CurrentFilmIndex]->getFilePath());//触发一次测量
	}
}
