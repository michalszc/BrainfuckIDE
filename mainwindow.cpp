#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QDebug> // TO DELETE

#include<QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    awesome = new QtAwesome( qApp );
    awesome->initFontAwesome();

    QVariantMap options;
    options.insert( "color" , QColor(187,187,187) );
    setWindowIcon(awesome->icon(fa::code, options).pixmap(256,256));

    currentFile = "";
    codeEditor = new CodeEditor;

    QPushButton *call_button = new QPushButton(this);
    call_button->setText("Make a Call");
    call_button->setStyleSheet(
                "QPushButton{background-color:red;color:white}\
                 QPushButton::hover{color:black}");

    QFont font;
    font.setFamily("Cascadia Mono");
    font.setFixedPitch(true);
    font.setPointSize(12);

    input = new QLineEdit;
    input->setPlaceholderText("Input");
    input->setFont(font);

    output = new QTextEdit;
    output->setPlaceholderText("Output");
    output->setFont(font);
    output->setTextColor(QColor(166,175,161,255));
    output->setFixedHeight( output->fontMetrics().height() * 10);
    output->setReadOnly(true);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(codeEditor);
    mainLayout->addWidget(input);
    mainLayout->addWidget(output);
    mainLayout->addWidget(call_button);

    mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);
    mainWidget->setMinimumSize(120,100);
    setCentralWidget(mainWidget);
    setWindowTitle("Brainfuck IDE");
    connect( call_button, SIGNAL( clicked()),this,SLOT( checkChangeColor() ));
    setAutoFillBackground(true);
    setPalette(QColor(43,43,43,255));
    createActions();
    createMenus();
}

void MainWindow::checkChangeColor(){
    codeEditor->setLineColor(Qt::gray);
    codeEditor->cursorPositionChanged();
    codeEditor->setLineNumberAreaColor(Qt::black);
    codeEditor->setBackgroundColor(Qt::yellow);
    codeEditor->setLineNumberTextColor(Qt::yellow);
    codeEditor->setFocus();
    output->setText("asdasd");
}

MainWindow::~MainWindow()
{
    delete ui;
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(undoAct);
    menu.addSeparator();
    menu.addAction(cutAct);
    menu.addAction(copyAct);
    menu.addAction(pasteAct);
    menu.addSeparator();
    menu.addAction(selectAllAct);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void MainWindow::createActions()
{
    QVariantMap options;
    options.insert( "color" , QColor(187,187,187) );

    newAct = new QAction("New", this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip("Create a new file");
    newAct->setIcon(awesome->icon(fa::file, options).pixmap(32,32));
    newAct->setIconVisibleInMenu(true);
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction("Open...", this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip("Open an existing file");
    openAct->setIcon(awesome->icon(fa::folderopen, options).pixmap(32,32));
    openAct->setIconVisibleInMenu(true);
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction("Save", this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip("Save the document to disk");
    saveAct->setIcon(awesome->icon(fa::save, options).pixmap(32,32));
    saveAct->setIconVisibleInMenu(true);
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    saveAsAct = new QAction("Save as...", this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip("Save the document as ... to disk");
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);

    printAct = new QAction("Print...", this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip("Print the document");
    printAct->setIcon(awesome->icon(fa::print, options).pixmap(32,32));
    printAct->setIconVisibleInMenu(true);
    connect(printAct, &QAction::triggered, this, &MainWindow::print);

    exitAct = new QAction("Exit", this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip("Exit the application");
    exitAct->setIcon(awesome->icon(fa::windowclose, options).pixmap(32,32));
    exitAct->setIconVisibleInMenu(true);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    undoAct = new QAction("Undo", this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip("Undo the last operation");
    undoAct->setIcon(awesome->icon(fa::undo, options).pixmap(32,32));
    undoAct->setIconVisibleInMenu(true);
    connect(undoAct, &QAction::triggered, codeEditor, &QPlainTextEdit::undo);

    redoAct = new QAction("Redo", this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip("Redo the last operation");
    redoAct->setIcon(awesome->icon(fa::undo, options).pixmap(32,32).transformed(QTransform().scale(-1, 1)));
    redoAct->setIconVisibleInMenu(true);
    connect(redoAct, &QAction::triggered, codeEditor, &QPlainTextEdit::redo);

    cutAct = new QAction("Cut", this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip("Cut the current selection's contents to the clipboard");
    cutAct->setIcon(awesome->icon(fa::cut, options).pixmap(32,32));
    cutAct->setIconVisibleInMenu(true);
    connect(cutAct, &QAction::triggered, codeEditor, &QPlainTextEdit::cut);

    copyAct = new QAction("Copy", this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip("Copy the current selection's contents to the clipboard");
    copyAct->setIcon(awesome->icon(fa::copy, options).pixmap(32,32));
    copyAct->setIconVisibleInMenu(true);
    connect(copyAct, &QAction::triggered, codeEditor, &QPlainTextEdit::copy);

    pasteAct = new QAction("Paste", this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip("Paste the clipboard's contents into the current selection");
    pasteAct->setIcon(awesome->icon(fa::paste, options).pixmap(32,32));
    pasteAct->setIconVisibleInMenu(true);
    connect(pasteAct, &QAction::triggered, codeEditor, &QPlainTextEdit::paste);

    selectAllAct = new QAction("Paste", this);
    selectAllAct->setShortcuts(QKeySequence::SelectAll);
    selectAllAct->setStatusTip("Select all from the current file");
    selectAllAct->setIconVisibleInMenu(true);
    connect(selectAllAct, &QAction::triggered, codeEditor, &QPlainTextEdit::selectAll);

    runAct = new QAction("Run", this);
    runAct->setShortcut(QKeySequence(Qt::SHIFT | Qt::Key_F10));
    runAct->setStatusTip(tr("Run the brainfuck file"));
    runAct->setIcon(awesome->icon(fa::play, options).pixmap(32,32));
    runAct->setIconVisibleInMenu(true);
    connect(runAct, &QAction::triggered, this, &MainWindow::run);

    QDirIterator it(":/examples", QDirIterator::Subdirectories);
    it.next();
    QAction *tmpAct;
    while (it.hasNext()) {
        QString path = it.next();
        QString fileName = path.mid(path.lastIndexOf("/")+1);
        fileName = fileName.mid(0, fileName.lastIndexOf("."));
        tmpAct = new QAction(fileName,this);
        tmpAct->setStatusTip("Open "+fileName+" example");
        connect(tmpAct, &QAction::triggered, this, [this, path]{ openExample(path); });
        examplesAct.push_back(tmpAct);
    }


    aboutAct = new QAction("About", this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    aboutQtAct = new QAction("About Qt", this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu("Edit");
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(selectAllAct);

    codeMenu = menuBar()->addMenu("Code");
    codeMenu->addAction(runAct);

    examplesMenu = codeMenu->addMenu("Examples");
    for(QAction *act: examplesAct){
        examplesMenu->addAction(act);
    }

    helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

}


void MainWindow::newFile(){
    currentFile.clear();
    codeEditor->setPlainText(QString());
    setWindowTitle("Brainfuck IDE - newfile.bf");
}

void MainWindow::open(){
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file", "", "Brainfuck files (*.bf)");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle("Brainfuck IDE - " + fileName.mid(fileName.lastIndexOf("/")+1));
    QTextStream in(&file);
    QString text = in.readAll();
    codeEditor->setPlainText(text);
    file.close();
}

void MainWindow::save(){
    QString fileName;
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save", "newFile.bf", "Brainfuck files (*.bf)");
        if (fileName.isEmpty())
            return;
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle("Brainfuck IDE - " + fileName.mid(fileName.lastIndexOf("/")+1));
    QTextStream out(&file);
    QString text = codeEditor->toPlainText();
    out << text;
}

void MainWindow::saveAs(){
    QString fileName = QFileDialog::getSaveFileName(this, "Save as", "newFile.bf", "Brainfuck files (*.bf)");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = codeEditor->toPlainText();
    out << text;
    file.close();
}

void MainWindow::print(){
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if( dialog.exec() == QDialog::Rejected)
        return;
    codeEditor->print(&printer);
}

void MainWindow::run(){
    output->setText("");
    Interpreter(codeEditor->toPlainText().toStdString(),input->text().toStdString(), output);
}

void MainWindow::openExample(QString fileName){
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle("Brainfuck IDE - " + fileName.mid(fileName.lastIndexOf("/")+1));
    QTextStream in(&file);
    QString text = in.readAll();
    codeEditor->setPlainText(text);
    file.close();
}

void MainWindow::about(){
    QMessageBox::about(this, "About Brainfuck IDE",
    "<b>Brainfuck IDE</b> is a code editor that allows you to write and execute <b>Brainfuck</b> code."
    " It's perfect for anybody who just wants to quickly write and run some code on their computer. ");
}
