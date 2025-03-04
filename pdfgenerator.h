#ifndef PDFGENERATOR_H
#define PDFGENERATOR_H

#include <QObject>
#include <QFileInfo>
#include <QApplication>
#include <QWebEnginePage>
#include <QWebEngineSettings>

#include "interceptor.h"

class PDFGenerator : public QObject
{
    Q_OBJECT

public:
    explicit PDFGenerator(
        const QString &input,
        const QString &output,
        const QMarginsF &margins,
        QPageLayout::Unit page_unit,
        QPageSize::PageSizeId page_size,
        QPageLayout::Orientation page_orientation
    );
    int generate();

    static QPageLayout::Unit unitFromString(const QString &value);
    static QPageSize::PageSizeId sizeFromString(const QString &value);
    static QPageLayout::Orientation orientationFromString(
        const QString &value
    );

public slots:
    void onLoadFinished(bool ok);
    void onPdfPrintingFinished(const QString &filepath, bool success);

private:
    QString m_input;
    QString m_output;
    QMarginsF m_margins;
    QPageLayout::Unit m_page_unit;
    QPageSize::PageSizeId m_page_size;
    QPageLayout::Orientation m_page_orientation;
    QScopedPointer<QWebEnginePage> m_page;
    QScopedPointer<URLRequestInterceptor> m_interceptor;
};

#endif // PDFGENERATOR_H
