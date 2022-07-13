#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QDebug> // TO DELETE

#include<QPushButton>
#include "qsettings_json.hpp"

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

    QFont font;
    font.setFamily("Cascadia Mono");
    font.setFixedPitch(true);
    font.setPointSize(12);

    inpbackgroundColor = QColor(43,43,43,255);
    inptextColor = QColor(130,128,135,255); // QColor(166,175,161,255)

    input = new QLineEdit;
    input->setPlaceholderText("Input");
    input->setFont(codeEditor->font());
    input->setStyleSheet("background:"+QString(inpbackgroundColor.name())+";color:"+QString(inptextColor.name()));

    output = new QTextEdit;
    output->setPlaceholderText("Output");
    output->setFont(codeEditor->font());
    output->setFixedHeight( output->fontMetrics().height() * 10);
    output->setReadOnly(true);
    output->setStyleSheet("background:"+QString(inpbackgroundColor.name())+";color:"+QString(inptextColor.name()));

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(codeEditor);
    mainLayout->addWidget(input);
    mainLayout->addWidget(output);

    connect(codeEditor, &QPlainTextEdit::textChanged,
            this, &MainWindow::documentWasModified);

    mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);
    mainWidget->setMinimumSize(120,100);
    setCentralWidget(mainWidget);
    setAutoFillBackground(true);
//    setPalette(QColor(43,43,43,255));
    readSettings();
    setUnifiedTitleAndToolBarOnMac(true);
    createActions();
    createMenus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getTheme(const QString name = "Custom"){
    QSettings setting(":/settings/themes.json", JsonFormat);
    setting.beginGroup(name);

    // Editor font
    QFont font = setting.value("editorFont").value<QFont>();
    codeEditor->setFont(font);
    input->setFont(font);
    output->setFont(font);

    // Editor Comment font
    font = setting.value("commentFont").value<QFont>();
    codeEditor->highlighter->setCommentFont(font);

    // IDE background color
    setPalette(setting.value("backgroundColor").value<QColor>());

    // Editor background color
    codeEditor->setBackgroundColor(setting.value("editorBackgroundColor").value<QColor>());

    // Editor sidebar color
    codeEditor->setLineNumberAreaColor(setting.value("editorSidebarColor").value<QColor>());

    // Editor line numbers color
    codeEditor->setLineNumberTextColor(setting.value("editorLineNumbersColor").value<QColor>());

    // Editor current line color
    codeEditor->setLineColor(setting.value("editorCurrentLineColor").value<QColor>());
    codeEditor->cursorPositionChanged();

    // Input & Output background color
    inpbackgroundColor = setting.value("input_outputBackgroundColor").value<QColor>();

    // Input & Output text color
    inptextColor = setting.value("input_outputTextColor").value<QColor>();

    input->setStyleSheet("background:"+QString(inpbackgroundColor.name())+";color:"+QString(inptextColor.name()));
    output->setStyleSheet("background:"+QString(inpbackgroundColor.name())+";color:"+QString(inptextColor.name()));

    // <>
    codeEditor->highlighter->setMovingPointerColor(setting.value("movingPointerColor").value<QColor>());

    // ,
    codeEditor->highlighter->setReadColor(setting.value("readColor").value<QColor>());

    // .
    codeEditor->highlighter->setInputColor(setting.value("inputColor").value<QColor>());

    // + -
    codeEditor->highlighter->setChangeValueColor(setting.value("changeValueColor").value<QColor>());

    // []
    codeEditor->highlighter->setLoopColor(setting.value("loopColor").value<QColor>());

    // comment
    codeEditor->highlighter->setCommentColor(setting.value("commentColor").value<QColor>());

    codeEditor->highlighter->rehighlight();

    setting.endGroup();
}

void MainWindow::saveTheme(const QString name = "Custom"){
    QSettings setting(":/settings/themes.json", JsonFormat);
    setting.beginGroup(name);

    // Editor font
    setting.setValue("editorFont", codeEditor->font());

    // Editor Comment font
    setting.setValue("commentFont", codeEditor->highlighter->getCommentFont());

    // IDE background color
    setting.setValue("backgroundColor", palette().color(QWidget::backgroundRole()));

    // Editor background color
    setting.setValue("editorBackgroundColor", codeEditor->getBackgroundColor());

    // Editor sidebar color
    setting.setValue("editorSidebarColor", codeEditor->getLineNumberAreaColor());

    // Editor line numbers color
    setting.setValue("editorLineNumbersColor", codeEditor->getLineNumberTextColor());

    // Editor current line color
    setting.setValue("editorCurrentLineColor", codeEditor->getLineColor());

    // Input & Output background color
    setting.setValue("input_outputBackgroundColor", inpbackgroundColor);

    // Input & Output text color
    setting.setValue("input_outputTextColor", inptextColor);

    // <>
    setting.setValue("movingPointerColor", codeEditor->highlighter->getMovingPointerColor());

    // ,
    setting.setValue("readColor", codeEditor->highlighter->getReadColor());

    // .
    setting.setValue("inputColor" , codeEditor->highlighter->getInputColor());

    // + -
    setting.setValue("changeValueColor",codeEditor->highlighter->getChangeValueColor());

    // []
    setting.setValue("loopColor", codeEditor->highlighter->getLoopColor());

    // comment
    setting.setValue("commentColor", codeEditor->highlighter->getCommentColor());

    setting.endGroup();
}

void MainWindow::readSettings(){
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
    QString fileName = settings.value("file").toString();
    if(fileName.isEmpty()){
        setCurrentFile(QString());
    }else{
        loadFile(fileName);
    }
    QString currentTheme = settings.value("theme").toString();
    if(currentTheme.length() > 0 && currentTheme.isEmpty()){
        getTheme(currentTheme);
    }else{
        getTheme("dark");
    }
}

void MainWindow::writeSettings(){
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
    settings.setValue("file", currentFile);
}

void MainWindow::documentWasModified(){
    setWindowModified(codeEditor->document()->isModified());
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

    settingsAct = new QAction("Settings", this);
    settingsAct->setStatusTip("Open settings");
    settingsAct->setIcon(awesome->icon(fa::wrench, options).pixmap(32,32));
    settingsAct->setIconVisibleInMenu(true);
    connect(settingsAct, &QAction::triggered, this, &MainWindow::openSettings);

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

    selectAllAct = new QAction("Select all", this);
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
    fileMenu->addSeparator();
    fileMenu->addAction(settingsAct);
    fileMenu->addSeparator();
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

void MainWindow::closeEvent(QCloseEvent *event){
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

bool MainWindow::maybeSave(){
    if (!codeEditor->document()->isModified())
        return true;
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("BrainfuckIDE"),
                               tr("The file has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

void MainWindow::newFile(){
    if(maybeSave()){
        currentFile.clear();
        codeEditor->setPlainText(QString());
        setCurrentFile(QString());
    }
}

void MainWindow::loadFile(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Open file error"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    codeEditor->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif
    file.close();
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::open(){
    if(maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(this, "Open the file", "", "Brainfuck files (*.bf)");
        if (fileName.isEmpty())
            return;
        loadFile(fileName);
    }
}

void MainWindow::openSettings(){
    const QColor colors[] = {
        palette().color(QWidget::backgroundRole()), // IDE background color
        codeEditor->getBackgroundColor(), // Editor background color
        codeEditor->getLineNumberAreaColor(), // Editor sidebar color
        codeEditor->getLineNumberTextColor(), // Editor line numbers color
        codeEditor->getLineColor(), // Editor current line color
        inpbackgroundColor, // Input & Output background color
        inptextColor, // Input & Output text color
        codeEditor->highlighter->getMovingPointerColor(), // <>
        codeEditor->highlighter->getReadColor(), // ,
        codeEditor->highlighter->getInputColor(),// .
        codeEditor->highlighter->getChangeValueColor(),// + -
        codeEditor->highlighter->getLoopColor(), // []
        codeEditor->highlighter->getCommentColor()// comment
    };
    Settings s(awesome,colors, codeEditor->font(), codeEditor->highlighter->getCommentFont(), this);
    s.setModal(true);
    if ( s.exec() == QDialog::Accepted ){
        QFont font = s.getFont();
        codeEditor->setFont(font);
        input->setFont(font);
        output->setFont(font);
        font = s.getCommentFont();
        codeEditor->highlighter->setCommentFont(font);
        std::vector<QColor> colors = s.getColors();

        setPalette(colors[0]);

        codeEditor->setBackgroundColor(colors[1]);

        codeEditor->setLineNumberAreaColor(colors[2]);

        codeEditor->setLineNumberTextColor(colors[3]);

        codeEditor->setLineColor(colors[4]);
        codeEditor->cursorPositionChanged();

        inpbackgroundColor = colors[5];
        inptextColor = colors[6];
        input->setStyleSheet("background:"+QString(colors[5].name())+";color:"+QString(colors[6].name()));
        output->setStyleSheet("background:"+QString(colors[5].name())+";color:"+QString(colors[6].name()));

        codeEditor->highlighter->setMovingPointerColor(colors[7]);
        codeEditor->highlighter->setReadColor(colors[8]);
        codeEditor->highlighter->setInputColor(colors[9]);
        codeEditor->highlighter->setChangeValueColor(colors[10]);
        codeEditor->highlighter->setLoopColor(colors[11]);
        codeEditor->highlighter->setCommentColor(colors[12]);
        codeEditor->highlighter->rehighlight();
//        saveTheme("Custom");
//        QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
//        settings.setValue("theme", "Custom");
    }
}

bool MainWindow::checkIfExample(){
    if( currentFile.startsWith(":/examples/")){
        QMessageBox::warning(this, "Save example file error", "Cannot save example file: " + QFileInfo(currentFile).fileName()
                             + "<br> you can save it in different name.");
        return true;
    }
    return false;
}

void MainWindow::setCurrentFile(const QString &fileName){
    currentFile = fileName;
    codeEditor->document()->setModified(false);
    setWindowModified(false);

    QString shownName = currentFile;
    if (currentFile.isEmpty())
        shownName = "untitled.bf";
    setWindowFilePath(shownName);
    setWindowTitle("BrainfuckIDE - "+QFileInfo(shownName).fileName()+"[*]");
}

bool MainWindow::save(){
    if ( currentFile.isEmpty() || checkIfExample() ) {
        return saveAs();
    } else {
        return saveFile(currentFile);
    }
}

bool MainWindow::saveAs(){
    QString fileName = QFileDialog::getSaveFileName(this, "Save as", "newFile.bf", "Brainfuck files (*.bf)");
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName){
    QString errorMessage;
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << codeEditor->toPlainText();
        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.")
                           .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    }else{
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                       .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }
    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("Save file error"), errorMessage);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
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
    if(maybeSave()){
        loadFile(fileName);
    }
}

void MainWindow::about(){
    QMessageBox::about(this, "About Brainfuck IDE",
    "<b>Brainfuck IDE</b> is a code editor that allows you to write and execute <b>Brainfuck</b> code."
    " It's perfect for anybody who just wants to quickly write and run some code on their computer. ");
}
