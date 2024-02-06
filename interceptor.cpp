#include "interceptor.h"

URLRequestInterceptor::URLRequestInterceptor(QObject *parent) :
    QWebEngineUrlRequestInterceptor(parent)
{}

void URLRequestInterceptor::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    qInfo() << "outgoing request";
    qInfo().noquote() << "method:" << info.requestMethod();
    qInfo().noquote() << "   url:" << info.requestUrl().toString();
    qInfo().noquote() << "  type:" << resourceTypeString(info.resourceType());
    if(info.resourceType() == QWebEngineUrlRequestInfo::ResourceTypeMainFrame){
        qInfo() << "request allowed";
        info.block(false);
        return;
    }
    qWarning() << "request blocked";
    info.block(true);
}

const QString URLRequestInterceptor::resourceTypeString(QWebEngineUrlRequestInfo::ResourceType type)
{
    switch (type) {
    case QWebEngineUrlRequestInfo::ResourceTypeMainFrame:
        return "Main Frame";
    case QWebEngineUrlRequestInfo::ResourceTypeSubFrame:
        return "Sub Frame";
    case QWebEngineUrlRequestInfo::ResourceTypeStylesheet:
        return "Stylesheet";
    case QWebEngineUrlRequestInfo::ResourceTypeScript:
        return "Script";
    case QWebEngineUrlRequestInfo::ResourceTypeImage:
        return "Image";
    case QWebEngineUrlRequestInfo::ResourceTypeFontResource:
        return "Font Resource";
    case QWebEngineUrlRequestInfo::ResourceTypeSubResource:
        return "Sub Resource";
    case QWebEngineUrlRequestInfo::ResourceTypeObject:
        return "Object";
    case QWebEngineUrlRequestInfo::ResourceTypeMedia:
        return "Media";
    case QWebEngineUrlRequestInfo::ResourceTypeWorker:
        return "Worker";
    case QWebEngineUrlRequestInfo::ResourceTypeSharedWorker:
        return "Shared Worker";
    case QWebEngineUrlRequestInfo::ResourceTypePrefetch:
        return "Prefetch";
    case QWebEngineUrlRequestInfo::ResourceTypeFavicon:
        return "Favicon";
    case QWebEngineUrlRequestInfo::ResourceTypeXhr:
        return "XHR";
    case QWebEngineUrlRequestInfo::ResourceTypePing:
        return "Ping";
    case QWebEngineUrlRequestInfo::ResourceTypeServiceWorker:
        return "Service Worker";
    case QWebEngineUrlRequestInfo::ResourceTypeCspReport:
        return "CSP Report";
    case QWebEngineUrlRequestInfo::ResourceTypePluginResource:
        return "Plugin Resource";
    case QWebEngineUrlRequestInfo::ResourceTypeNavigationPreloadMainFrame:
        return "Navigation Preload Main Frame";
    case QWebEngineUrlRequestInfo::ResourceTypeNavigationPreloadSubFrame:
        return "Navigation Preload Sub Frame";
    case QWebEngineUrlRequestInfo::ResourceTypeWebSocket:
        return "Web Socket";
    case QWebEngineUrlRequestInfo::ResourceTypeUnknown:
        return "Unknown";
    }
    return "Unsupported";
}
