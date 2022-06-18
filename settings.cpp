#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QtAwesome* awesome_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    awesome = awesome_;
    setWindowTitle("Brainfuck IDE - Settings");
    QVariantMap options;
    options.insert( "color" , QColor(187,187,187) );
    setWindowIcon(awesome->icon(fa::wrench, options).pixmap(256,256));
    setAutoFillBackground(true);
    setPalette(QColor(43,43,43,255));
}

Settings::~Settings()
{
    delete ui;
}
