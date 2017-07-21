#include "colorpickerwidget.h"
#include "ui_colorpickerwidget.h"

ColorPickerWidget::ColorPickerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorPickerWidget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint |Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    //获取屏幕 大小
    desktop = new QDesktopWidget;
    //设置全屏
    this->setGeometry(0,0,desktop->width(),desktop->height());
    //默认在 左下角
    ui->groupBox->setGeometry(desktop->width()-ui->groupBox->width(),desktop->height()-ui->groupBox->height(),ui->groupBox->width(),ui->groupBox->height());
    this->hide();//隐藏窗口 截图
    this->pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    //显示出来
    this->show();
    //设置鼠标跟踪
    this->setMouseTracking(true);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::yellow);
    ui->locationLabel->setPalette(pa);

}

ColorPickerWidget::~ColorPickerWidget()
{
    delete ui;
}


void ColorPickerWidget::enterEvent(QEvent *){
    QCursor cursor ;
    QPixmap pixmap(":/cursor") ;
    cursor = QCursor(pixmap,0,20);
    setCursor(cursor);
}
//鼠标移动
void ColorPickerWidget::mouseMoveEvent(QMouseEvent *event){
    rgb = pixmap.toImage().pixel(this->mapFromGlobal(QCursor::pos()));
    r = qRed(rgb);
    g = qGreen(rgb);
    b = qBlue(rgb);
    ui->redLineEdit->setText(QString::number(r));
    ui->greenLineEdit->setText(QString::number(g));
    ui->blueLineEdit->setText(QString::number(b));

    ui->previewlabel->setPixmap(pixmap.copy(event->x()-15,event->y()-13.25,30,26.5).scaled(ui->previewlabel->width(),ui->previewlabel->height()));
    ui->colorLabel->setStyleSheet("QLabel{background:rgb("+QString::number(r)+","+QString::number(g)+","+QString::number(b)+");}");
    ui->locationLabel->setText("X="+QString::number(event->x())+" , Y="+QString::number(event->y()));

    int value = r << 16 | g << 8 | b;
    if(value == 0){
        ui->decLineEdit->setText( "0");
        ui->hexLineEdit->setText( "000000");
    }else{
        ui->decLineEdit->setText( QString::number(value) );
        ui->hexLineEdit->setText( QString::number(value,16).toUpper());
    }


    //移动位置
    if(event->x()>= this->desktop->width() - ui->groupBox->width() - 10 && event->y() >= this->desktop->height() - ui->groupBox->height() - 10){
        if( ui->groupBox->x() != 0 )
            ui->groupBox->setGeometry(0,0,ui->groupBox->width(),ui->groupBox->height());
    }else if(event->x() <= ui->groupBox->width() + 10 && event->y() <= ui->groupBox->height() + 10){
        if( ui->groupBox->x() != desktop->width()-ui->groupBox->width() )
            ui->groupBox->setGeometry(desktop->width()-ui->groupBox->width(),desktop->height()-ui->groupBox->height(),ui->groupBox->width(),ui->groupBox->height());
    }
}

void ColorPickerWidget::mousePressEvent(QMouseEvent *){
   this->showColor();
}
void ColorPickerWidget::paintEvent(QPaintEvent *event){
    //绘制用户看到的图片
    QPainter painter(this) ;
    painter.drawPixmap(0,0,desktop->width(),desktop->height(),pixmap);
}

//键盘按键松开
void ColorPickerWidget::keyReleaseEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Escape://退出
        this->close();
        break;
    case Qt::Key_Left://光标移动精确定位颜色
        QCursor::setPos(QPoint(QCursor::pos().x()-1,QCursor::pos().y()));
        break;
    case Qt::Key_Up:
       QCursor::setPos(QPoint(QCursor::pos().x(),QCursor::pos().y()-1));
        break;
    case Qt::Key_Right:
       QCursor::setPos(QPoint(QCursor::pos().x()+1,QCursor::pos().y()));
        break;
    case Qt::Key_Down:
         QCursor::setPos(QPoint(QCursor::pos().x(),QCursor::pos().y()+1));
        break;
    case Qt::Key_Return://回车键显示颜色
         this->showColor();
        break;
    }

}
void ColorPickerWidget::showColor(){
    //声音提醒
    qApp->beep();
    //显示对话框
    QColorDialog dialog(this);
    dialog.setWindowTitle("颜色");
    dialog.setCurrentColor( QColor(r,g,b));
    dialog.exec();
    //阻塞 后执行
    this->close();
}
