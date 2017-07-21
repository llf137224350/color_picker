#include "colorpickerwidget.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
        if (translator.load(QString(":/qt_zh_CN"))){
            a.installTranslator(&translator);
        }
    ColorPickerWidget w;

    w.show();

    return a.exec();
}
