#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationName("BrainfuckIDE");
    QCoreApplication::setApplicationVersion("0.1.0");

    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::translate("main",
    "Brainfuck IDE is a code editor that allows you to write and execute Brainfuck code. "
    "It's perfect for anybody who just wants to quickly write and run some code on their computer."));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("filename", QCoreApplication::translate("main", "File to open.(default is untiled.bf)"));

    QCommandLineOption codeOption(QStringList() << "c" << "code",  QCoreApplication::translate("main", "Set code."), QCoreApplication::translate("main", "code"), "+-[]<>,.");
    parser.addOption(codeOption);

    QCommandLineOption themeOption(QStringList() << "t" << "theme",  QCoreApplication::translate("main", "Change theme, possible options: light, dark and custom (default is dark)."), QCoreApplication::translate("main", "theme"), settings.value("theme").toString());
    parser.addOption(themeOption);

    parser.process(app);

    const QStringList args = parser.positionalArguments();

    QString fileName = (args.size() == 1) ? args.at(0) : "untitled.bf";

    qDebug() << "filename:  " << fileName;
    qDebug() << "code: " << parser.value(codeOption);
    qDebug() << "theme: " << parser.value(themeOption);

    QString theme = parser.value(themeOption);
    if(!theme.isEmpty()){
        if(theme == "light" || theme == "dark"){
            settings.setValue("theme", theme);
        }else{
            settings.setValue("theme", "custom");
        }
    }else{
        settings.setValue("theme", "custom");
    }

    MainWindow w;
    w.show();
    return app.exec();
}
