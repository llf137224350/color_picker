#ifndef COLORPICKERWIDGET_H
#define COLORPICKERWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDesktopWidget>
#include <QRgb>
#include <QPixmap>
#include <QColorDialog>


namespace Ui {
class ColorPickerWidget;
}

class ColorPickerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorPickerWidget(QWidget *parent = 0);
    ~ColorPickerWidget();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void enterEvent(QEvent *);
    void paintEvent(QPaintEvent *event);

    void keyReleaseEvent(QKeyEvent *event);
private:
    Ui::ColorPickerWidget *ui;
    QDesktopWidget *desktop;
    QPixmap pixmap;
    QRgb rgb;
    int r,g,b;

    void showColor();
};

#endif // COLORPICKERWIDGET_H
