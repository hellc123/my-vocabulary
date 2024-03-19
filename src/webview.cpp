#include "webview.h"
#include <QWebEngineSettings>
WebView::WebView(QWidget *parent)
    : QWebEngineView{parent}
{
    setAttribute( Qt::WA_NativeWindow, true );
    QWebEngineSettings * setting = settings();
    setting->setUnknownUrlSchemePolicy( QWebEngineSettings::UnknownUrlSchemePolicy::DisallowUnknownUrlSchemes );
    setting->setAttribute( QWebEngineSettings::LocalContentCanAccessRemoteUrls, true );
    setting->setAttribute( QWebEngineSettings::LocalContentCanAccessFileUrls, true );
    setting->setAttribute( QWebEngineSettings::ErrorPageEnabled, false );
    setting->setAttribute( QWebEngineSettings::PluginsEnabled, true );
    setting->setAttribute( QWebEngineSettings::PlaybackRequiresUserGesture, false );
    setting->setAttribute( QWebEngineSettings::JavascriptCanAccessClipboard, true );
    setting->setAttribute( QWebEngineSettings::PrintElementBackgrounds, false );
}
