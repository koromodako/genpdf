#include <QtDebug>
#include <QApplication>
#include <QWebEnginePage>
#include <QCommandLineParser>

#include "pdfgenerator.h"

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString message = qFormatLogMessage(type, context, msg);
    QTextStream(stderr) << message << "\n";
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("genpdf");
    QCoreApplication::setApplicationVersion("1.0.0");
    /* setup logging */
    qSetMessagePattern("%{time} [%{type}] %{message}");
    qInstallMessageHandler(messageHandler);
    qInfo().noquote() << QCoreApplication::applicationName() << QCoreApplication::applicationVersion();
    /* parse command line arguments */
    QCommandLineParser parser;
    parser.setApplicationDescription("Converts the web page INPUT into the PDF file OUTPUT");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("INPUT", "Path of the HTML file to process");
    parser.addPositionalArgument("OUTPUT", "Path of the PDF file to create");
    parser.parse(QCoreApplication::arguments());
    const QStringList positionalArgs = parser.positionalArguments();
    if(positionalArgs.size() != 2)
    {
        parser.showHelp(1);
    }
    /* generate PDF from HTML file */
    PDFGenerator generator(positionalArgs.at(0), positionalArgs.at(1));
    return generator.generate();
}
