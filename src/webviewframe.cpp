/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "openurlrequest.h"
#include "webviewframe.h"
#include "webviewer.h"
#include <QVBoxLayout>
#include <QAction>

using namespace Akregator;

WebViewFrame::WebViewFrame(KActionCollection *ac, QWidget *parent)
    : Frame(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    setRemovable(true);
    Akregator::WebViewer *viewer = new Akregator::WebViewer(ac, this);
    mArticleViewerWidgetNg = new Akregator::ArticleViewerWidgetNg(viewer, ac, this);

    //setZoomFactor(100);

    connect(mArticleViewerWidgetNg->articleViewerNg(), &ArticleViewerNg::titleChanged, this, &WebViewFrame::slotTitleChanged);
    connect(mArticleViewerWidgetNg->articleViewerNg(), &ArticleViewerNg::loadProgress, this, &WebViewFrame::slotProgressChanged);
    connect(mArticleViewerWidgetNg->articleViewerNg(), &ArticleViewerNg::signalOpenUrlRequest, this, &WebViewFrame::signalOpenUrlRequest);
    connect(mArticleViewerWidgetNg->articleViewerNg(), &ArticleViewerNg::loadStarted, this, &WebViewFrame::slotLoadStarted);
    connect(mArticleViewerWidgetNg->articleViewerNg(), &ArticleViewerNg::loadFinished, this, &WebViewFrame::slotLoadFinished);
    layout->addWidget(mArticleViewerWidgetNg);
}

WebViewFrame::~WebViewFrame()
{
}

void WebViewFrame::slotLoadFinished()
{
    Q_EMIT signalCompleted(this);
}

void WebViewFrame::slotLoadStarted()
{
    Q_EMIT signalStarted(this);
}

void WebViewFrame::slotProgressChanged(int progress)
{
    Q_EMIT signalLoadingProgress(this, progress);
}

void WebViewFrame::slotTitleChanged(const QString &title)
{
    Q_EMIT signalTitleChanged(this, title);
}

KParts::ReadOnlyPart *WebViewFrame::part() const
{
    return Q_NULLPTR;
}

QUrl WebViewFrame::url() const
{
    return mArticleViewerWidgetNg->articleViewerNg()->url();
}

bool WebViewFrame::openUrl(const OpenUrlRequest &request)
{
    //TODO
    mArticleViewerWidgetNg->articleViewerNg()->load(request.url());
    return true;
}

void WebViewFrame::loadConfig(const KConfigGroup &config, const QString &prefix)
{
    const QString url = config.readEntry(QStringLiteral("url").prepend(prefix), QString());
    const qreal zf = config.readEntry(QStringLiteral("zoom").prepend(prefix), 100);
    OpenUrlRequest req(url);
    KParts::OpenUrlArguments args;
    req.setArgs(args);
    openUrl(req);
    mArticleViewerWidgetNg->articleViewerNg()->setZoomFactor(zf);
}

void WebViewFrame::saveConfig(KConfigGroup &config, const QString &prefix)
{
    config.writeEntry(QStringLiteral("url").prepend(prefix), url().url());
    config.writeEntry(QStringLiteral("zoom").prepend(prefix), mArticleViewerWidgetNg->articleViewerNg()->zoomFactor());
}

void WebViewFrame::setFavicon(const QIcon &icon)
{
    Q_EMIT signalIconChanged(this, icon);
}

void WebViewFrame::slotZoomIn()
{
    mArticleViewerWidgetNg->articleViewerNg()->setZoomIn();
}

void WebViewFrame::slotZoomOut()
{
    mArticleViewerWidgetNg->articleViewerNg()->setZoomOut();
}

void WebViewFrame::slotHistoryForward()
{
    mArticleViewerWidgetNg->articleViewerNg()->pageAction(QWebPage::Forward)->trigger();
}

void WebViewFrame::slotHistoryBack()
{
    mArticleViewerWidgetNg->articleViewerNg()->pageAction(QWebPage::Back)->trigger();
}

void WebViewFrame::slotReload()
{
    mArticleViewerWidgetNg->articleViewerNg()->reload();
}

void WebViewFrame::slotStop()
{
    mArticleViewerWidgetNg->articleViewerNg()->stop();
}

bool WebViewFrame::canGoForward() const
{
    return mArticleViewerWidgetNg->articleViewerNg()->canGoForward();
}

bool WebViewFrame::canGoBack() const
{
    return mArticleViewerWidgetNg->articleViewerNg()->canGoBack();
}
