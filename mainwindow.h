#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "codeeditor.h"
#include "highlighter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupEditor();

private slots:
    void checkChangeColor(); // only for tests

private:
    Ui::MainWindow *ui;
    QWidget *mainWidget;
    CodeEditor *codeEditor;
    Highlighter *highlighter;
};
#endif // MAINWINDOW_H
