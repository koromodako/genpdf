#include "pdfgenerator.h"

PDFGenerator::PDFGenerator(
    const QString &input,
    const QString &output,
    const QMarginsF &margins,
    QPageLayout::Unit page_unit,
    QPageSize::PageSizeId page_size,
    QPageLayout::Orientation page_orientation
) :
    m_input(std::move(input)),
    m_output(std::move(output)),
    m_margins(std::move(margins)),
    m_page_unit(page_unit),
    m_page_size(page_size),
    m_page_orientation(page_orientation),
    m_page(new QWebEnginePage),
    m_interceptor(new URLRequestInterceptor)
{
    /* display underlying web engine components versions */
    qInfo() << "web engine version:" << qWebEngineVersion();
    qInfo() << "web engine chromium version:" << qWebEngineChromiumVersion();
    qInfo() << "web engine chromium security patch version:" << qWebEngineChromiumSecurityPatchVersion();
    /* setup request interceptor */
    m_page.data()->setUrlRequestInterceptor(m_interceptor.data());
    qInfo() << "url request interceptor setup";
    /* disable javascript engine */
    m_page.data()->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, false);
    qInfo() << "javascript engine is disabled";
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
        QPageLayout(m_page_size, m_page_orientation, m_margins, m_page_unit)
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


QPageLayout::Unit PDFGenerator::unitFromString(const QString &value)
{
    if(value == "point") { return QPageLayout::Point; }
    if(value == "inch") { return QPageLayout::Inch; }
    if(value == "pica") { return QPageLayout::Pica; }
    if(value == "didot") { return QPageLayout::Didot; }
    if(value == "cicero") { return QPageLayout::Cicero; }
    return QPageLayout::Millimeter;
}

QPageSize::PageSizeId PDFGenerator::sizeFromString(const QString &value)
{
    if(value == "A0") { return QPageSize::A0; }
    if(value == "A1") { return QPageSize::A1; }
    if(value == "A2") { return QPageSize::A2; }
    if(value == "A3") { return QPageSize::A3; }
    if(value == "A5") { return QPageSize::A5; }
    if(value == "A6") { return QPageSize::A6; }
    if(value == "A7") { return QPageSize::A7; }
    if(value == "A8") { return QPageSize::A8; }
    if(value == "A9") { return QPageSize::A9; }
    return QPageSize::A4;
}

QPageLayout::Orientation PDFGenerator::orientationFromString(const QString &value)
{
    if(value == "landscape") { return QPageLayout::Landscape; }
    return QPageLayout::Portrait;
}

