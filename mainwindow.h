#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QFont>
#include <QFontDialog>
#include <QDirIterator>
#include <QLineEdit>
#include "codeeditor.h"
#include "Interpreter.h"
#include "QtAwesome.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private:
    void createActions();
    void createMenus();

private slots:
    void newFile();
    void open();
    void save();
    void saveAs();
    void print();
    void run();
    void openExample(QString fileName);
    void about();

    // only for tests
    void checkChangeColor();

private:
    Ui::MainWindow *ui;
    QWidget *mainWidget;

    CodeEditor *codeEditor;
    QString currentFile;

    QLineEdit *input;
    QTextEdit *output;

    //FontAwesome
    QtAwesome* awesome;

    // Menu Bar
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *codeMenu;
    QMenu *examplesMenu;
    QMenu *helpMenu;

    // Actions
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *selectAllAct;
    QAction *runAct;
    QVector<QAction*> examplesAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};
#endif // MAINWINDOW_H
