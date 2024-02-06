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
    explicit PDFGenerator(const QString &input, const QString &output);
    int generate();

public slots:
    void onLoadFinished(bool ok);
    void onPdfPrintingFinished(const QString &filepath, bool success);

private:
    QString m_input;
    QString m_output;
    QScopedPointer<QWebEnginePage> m_page;
    QScopedPointer<URLRequestInterceptor> m_interceptor;
};

#endif // PDFGENERATOR_H
