#include "pdfgenerator.h"

PDFGenerator::PDFGenerator(const QString &input, const QString &output) :
    m_input(std::move(input)),
    m_output(std::move(output)),
    m_page(new QWebEnginePage),
    m_interceptor(new URLRequestInterceptor)
{
    /* display underlying web engine components versions */
    qInfo() << "web engine version:" << qWebEngineVersion();
    qInfo() << "web engine chromium version:" << qWebEngineChromiumVersion();
    qInfo() << "web engine chromium security patch version:" << qWebEngineChromiumSecurityPatchVersion();
    /* setup interceptor */
    m_page.data()->setUrlRequestInterceptor(m_interceptor.data());
    m_page.data()->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, false);
    /* connect signals and slots */
    connect(m_page.data(), &QWebEnginePage::loadFinished, this, &PDFGenerator::onLoadFinished);
    connect(m_page.data(), &QWebEnginePage::pdfPrintingFinished, this, &PDFGenerator::onPdfPrintingFinished);
}

int PDFGenerator::generate()
{
    QFileInfo finfo(m_input);
    if(finfo.canonicalFilePath().isEmpty()){
        qCritical().noquote() << "failed to resolve canonical file path for" << m_input;
        QCoreApplication::exit(2);
    } else {
        qInfo().noquote() << "loading HTML from" << finfo.canonicalFilePath();
        m_page.data()->load(QUrl::fromUserInput(finfo.canonicalFilePath()));
    }
    return QApplication::exec();
}

void PDFGenerator::onLoadFinished(bool ok)
{
    if(!ok){
        qCritical().noquote() << "failed to load HTML from" << m_input;
        QCoreApplication::exit(3);
        return;
    }
    qInfo().noquote() << "HTML content loaded from" << m_input;
    m_page.data()->printToPdf(
        m_output,
        QPageLayout(
            QPageSize::A4,
            QPageLayout::Portrait,
            QMarginsF(10.0, 10.0, 10.0, 10.0),
            QPageLayout::Millimeter
        )
    );
}

void PDFGenerator::onPdfPrintingFinished(const QString &filepath, bool success)
{
    if(!success){
        qCritical().noquote() << "failed to generate" << filepath;
        QCoreApplication::exit(4);
        return;
    }
    qInfo().noquote() << "generated" << filepath;
    QCoreApplication::quit();
}
