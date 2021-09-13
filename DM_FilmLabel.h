#ifndef DM_FILMLABEL_H
#define DM_FILMLABEL_H

#include <QObject>
#include <QLabel>

typedef class DM_FilmLabel : public QLabel
{
		Q_OBJECT
	public:
		DM_FilmLabel(const QString& filePath, const QSize& size, const QSize& maxThumbSize, int index = -1, QWidget *parent = 0);
		~DM_FilmLabel();

		void setSize(const QSize& size);
		void setChecked(bool checked);
		bool isValid() const;

		QString getFilePath() const;
		int getIndex() const;


	private:
		void mouseReleaseEvent(QMouseEvent* ev);

	signals:
		void checked(int index);//只当isChecked == true时发射;

	private:
		QPixmap Thumb;
		QString FilePath;
		bool IsChecked;
		bool IsValid;
		int Index = -1;
}DM_Film;

#endif // DM_FILMLABEL_H
