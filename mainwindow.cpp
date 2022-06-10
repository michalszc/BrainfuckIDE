#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QDebug> // TO DELETE

#include<QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    codeEditor = new CodeEditor;
    QPushButton *call_button = new QPushButton(this);
    call_button->setText("Make a Call");
    call_button->setStyleSheet(
                "QPushButton{background-color:red;color:white}\
                 QPushButton::hover{color:black}");
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(codeEditor);
    mainLayout->addWidget(call_button);
    mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);
    mainWidget->setMinimumSize(120,100);
    setCentralWidget(mainWidget);
    setWindowTitle("Brainfuck IDE");
    connect( call_button, SIGNAL( clicked()),this,SLOT( checkChangeColor() ));\
    setupEditor();
}

void MainWindow::setupEditor()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(14);

    codeEditor->setFont(font);
    highlighter = new Highlighter(codeEditor->document());
}

void MainWindow::checkChangeColor(){
    codeEditor->setLineColor(Qt::gray);
    codeEditor->cursorPositionChanged();
    codeEditor->setLineNumberAreaColor(Qt::black);
    codeEditor->setBackgroundColor(Qt::blue);
    codeEditor->setLineNumberTextColor(Qt::yellow);
    codeEditor->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

