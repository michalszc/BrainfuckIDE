#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QPushButton>
#include <QListWidget>
#include <QFontDialog>
#include <QColorDialog>
#include <QSettings>
#include "codeeditor.h"
#include "QtAwesome.h"
namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QtAwesome* awesome_, const QColor colors[], const QFont font,const QFont commentFont, QString theme, QWidget *parent = nullptr);
    ~Settings();
    std::vector<QColor> getColors();
    QFont getFont() { return font_; }
    QFont getCommentFont() { return commentFont_; }

private:
    void setup();
    void addListItem(QString text, QColor color, int character=fa::square);

private slots:
    void change();
    void changeTheme();

private:
    Ui::Settings *ui;
    CodeEditor *codeEditor;
    QListWidget *list;

    //Theme
    QString currentTheme;
    QListWidget *themes;

    //FontAwesome
    QtAwesome* awesome;

    //Font
    QFont font_;
    QFont commentFont_;

    //Colors
    std::vector<std::pair<QString, QColor>> listItems;
};

#endif // SETTINGS_H
