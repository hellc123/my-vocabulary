#include "webview.h"

WebView::WebView(QWidget *parent)
    : QWebEngineView{parent}
{
    setAttribute( Qt::WA_NativeWindow, true );
}
