#include "myqlabel.h"
MyQLabel::MyQLabel(QWidget *parent):QLabel(parent)
{

}
void MyQLabel::paintEvent(QPaintEvent *event){
    QLabel::paintEvent(event);//先调用父类的paintEvent为了显示'背景'!!!
    QColor color(221,80,68);
    QPen pen(color);
    QPainter painter(this) ;
    painter.setPen(pen);
    QRect rect(this->width() / 2 ,this->height() / 2 +12,9,9);
    painter.drawRect(rect);
    painter.drawLine(this->width() / 2 - 9,this->height() / 2 +16.5,this->width() / 2 ,this->height() / 2 +16.5);

    painter.drawLine(this->width() / 2+9 ,this->height() / 2 +16.5,this->width() / 2+18,this->height() / 2 +16.5);

    painter.drawLine(this->width() / 2+4.5 ,this->height() / 2 + 3,this->width() / 2+4.5,this->height() / 2 +12);
    painter.drawLine(this->width() / 2+4.5 ,this->height() / 2 + 21,this->width() / 2+4.5,this->height() / 2 +30);
}
