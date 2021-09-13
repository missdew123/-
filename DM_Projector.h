#ifndef DM_PROJECTOR_H
#define DM_PROJECTOR_H

#include "flowlayout.h"
#include "DM_FilmLabel.h"

#include <QDir>
#include <QToolButton>
#include <QWidget>




class DM_Projector : public QWidget
{
		Q_OBJECT
	public:
		DM_Projector(QWidget *parent = 0);
		~DM_Projector();
		void setButtons(QToolButton *playFilmBtn, QToolButton *playFirstBtn, QToolButton *playPreviousBtn,
						QToolButton *playNextBtn, QToolButton *playFinalBtn);
		bool initProjector();

		bool setFolderPath(const QDir& folderPath);
		void clearFilms();
		void updateFilms();
		void updateFilms(int startIndex);

	public slots:
		void on_Films_checked(int index);

	private:
		//这些仅仅是用于显示的部分
		void addLabel(DM_Film* film);
		void clearLabels();
		void resizeEvent(QResizeEvent* ev);

	private slots:
		void on_Btn_PlayFinal_clicked();
		void on_Btn_PlayNext_clicked();
		void on_Btn_PlayPrevious_clicked();
		void on_Btn_PlayFirst_clicked();
		void on_Btn_PlayFilm_clicked();




	signals:
		void triggerOnce(const QString& filePath);

	private:
		QWidget* Wdt_Films;
		QVBoxLayout* LO_Films;
		QLabel* Lbl_FilmsInfo;
		QToolButton *Btn_PlayFilm, *Btn_PlayFirst, *Btn_PlayPrevious, *Btn_PlayNext, *Btn_PlayFinal;
		QDir FolderPath;
		QVector<DM_Film*> Films;
		QSpacerItem* SP_Films;

		int StartIndex;
		int CurrentFilmIndex;

		int CurrentTime;
		int CurrentCount;
};

#endif // DM_PROJECTOR_H
