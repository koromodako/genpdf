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
    QCoreApplication::setApplicationVersion("1.1.0");
    /* setup logging */
    qSetMessagePattern("%{time} [%{type}] %{message}");
    qInstallMessageHandler(messageHandler);
    qInfo().noquote() << QCoreApplication::applicationName() << QCoreApplication::applicationVersion();
    /* parse command line arguments */
    QCommandLineParser parser;
    parser.setApplicationDescription("Converts the input web page into the output PDF file");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption({"mt", "Top margin", "mt", "10.0"});
    parser.addOption({"ml", "Left margin", "ml", "10.0"});
    parser.addOption({"mr", "Right margin", "mr", "10.0"});
    parser.addOption({"mb", "Bottom margin", "mb", "10.0"});
    parser.addOption({"unit", "Page unit", "unit", "millimeter"});
    parser.addOption({"size", "Page size", "size", "A4"});
    parser.addOption({"orientation", "Page orientation", "orientation", "portrait"});
    parser.addPositionalArgument("input", "Path of the HTML file to process");
    parser.addPositionalArgument("output", "Path of the PDF file to create");
    parser.process(app);
    const QStringList positionalArgs = parser.positionalArguments();
    if(positionalArgs.size() != 2)
    {
        parser.showHelp(1);
    }
    /* generate PDF from HTML file */
    bool ok;
    double mt, mr, ml, mb;
    mt = parser.value("mt").toDouble(&ok);
    mt = qMax(ok ? mt : 10.0, 1.0);
    mr = parser.value("mr").toDouble(&ok);
    mr = qMax(ok ? mr : 10.0, 1.0);
    ml = parser.value("ml").toDouble(&ok);
    ml = qMax(ok ? ml : 10.0, 1.0);
    mb = parser.value("mb").toDouble(&ok);
    mb = qMax(ok ? mb : 10.0, 1.0);
    PDFGenerator generator(
        positionalArgs.at(0),
        positionalArgs.at(1),
        QMarginsF(ml, mt, mr, mb),
        PDFGenerator::unitFromString(parser.value("unit")),
        PDFGenerator::sizeFromString(parser.value("size")),
        PDFGenerator::orientationFromString(parser.value("orientation"))
    );
    return generator.generate();
}
