#ifndef URL_REQUEST_INTERCEPTOR_H
#define URL_REQUEST_INTERCEPTOR_H

#include <QtDebug>
#include <QWebEngineUrlRequestInterceptor>

class URLRequestInterceptor : public QWebEngineUrlRequestInterceptor
{
public:
    URLRequestInterceptor(QObject *parent = nullptr);

    void interceptRequest(QWebEngineUrlRequestInfo &info);

    static const QString resourceTypeString(QWebEngineUrlRequestInfo::ResourceType type);
};

#endif // URL_REQUEST_INTERCEPTOR_H
