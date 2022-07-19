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

    QCommandLineOption fileOption(QStringList() << "f" << "file",  QCoreApplication::translate("main", "File to open."), QCoreApplication::translate("main", "filename"));
    parser.addOption(fileOption);

    QCommandLineOption themeOption(QStringList() << "t" << "theme",  QCoreApplication::translate("main", "Change theme, possible options: light, dark and custom (default is dark)."), QCoreApplication::translate("main", "theme"), settings.value("theme").toString());
    parser.addOption(themeOption);

    QCommandLineOption codeOption(QStringList() << "c" << "code",  QCoreApplication::translate("main", "Set code."), QCoreApplication::translate("main", "code"), "+-[]<>,.");
    parser.addOption(codeOption);

    parser.process(app);

    QString file = parser.value(fileOption);
    if(!file.isEmpty() && QFile::exists(file) && file.endsWith(".bf")){
        settings.setValue("file", QFileInfo(file).absoluteFilePath());
    }

    QString theme = parser.value(themeOption);
    if(!theme.isEmpty()){
        if(theme == "light" || theme == "dark"){
            settings.setValue("theme", theme);
        }else{
            settings.setValue("theme", "custom");
        }
    }else{
        settings.setValue("theme", "dark");
    }

    MainWindow w;
    w.show();
    return app.exec();
}
