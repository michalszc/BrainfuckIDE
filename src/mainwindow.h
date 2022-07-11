#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSaveFile>
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
#include <QSettings>
#include "codeeditor.h"
#include "Interpreter.h"
#include "QtAwesome.h"
#include "settings.h"

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
    void closeEvent(QCloseEvent *event) override;
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private:
    void createActions();
    void createMenus();
    bool checkIfExample();
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void loadFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    void readSettings();
    void writeSettings();

private slots:
    void newFile();
    void open();
    void openSettings();
    bool save();
    bool saveAs();
    void print();
    void run();
    void openExample(QString fileName);
    void about();
    void documentWasModified();

private:
    Ui::MainWindow *ui;
    QWidget *mainWidget;

    CodeEditor *codeEditor;
    QString currentFile;

    QLineEdit *input;
    QTextEdit *output;
    QColor inpbackgroundColor;
    QColor inptextColor;

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
    QAction *settingsAct;
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
