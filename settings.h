#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "QtAwesome.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QtAwesome* awesome_, QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;

    //FontAwesome
    QtAwesome* awesome;
};

#endif // SETTINGS_H
