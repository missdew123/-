#ifndef DM_SLIDER_H
#define DM_SLIDER_H

#include <QSlider>
#include <QLabel>
#include <QMouseEvent>
class DM_Slider: public QSlider
{
public:
    DM_Slider(QWidget *parent=0);
    ~DM_Slider();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

private:
    QLabel* m_displayLabel;
};


#endif // DM_SLIDER_H
