#include "traktitem.h"

#include "traktids.h"
#include "traktimageset.h"
#include "traktrequest.h"
#include "traktreply.h"

TraktItem::TraktItem(QObject *parent) :
    QObject(parent),
    m_ids(0),
    m_images(0),
    m_loaded(false)
{
}

TraktIds *TraktItem::ids() const
{
    return m_ids;
}

void TraktItem::setIds(TraktIds *ids)
{
    m_ids = ids;
    emit idsChanged();
}

QString TraktItem::title() const
{
    return m_title;
}

void TraktItem::setTitle(const QString &title)
{
    m_title = title;
    emit titleChanged();
}

TraktImageSet *TraktItem::images() const
{
    return m_images;
}

void TraktItem::setImages(TraktImageSet *images)
{
    m_images = images;
    emit imagesChanged();
}

void TraktItem::setLoaded(bool loaded)
{
    m_loaded = loaded;
}

void TraktItem::load()
{
    if (m_loaded) {
        return;
    }

    TraktRequest *request = new TraktRequest(this);
    request->setPath(itemUrl());
    request->addQueryItem("extended", "full");
    connect(request, &TraktRequest::replyReceived, this, &TraktItem::onFullyLoaded);
    request->send();
}

void TraktItem::onFullyLoaded(TraktReply *reply)
{
    reply->deleteLater();
    parse(reply->asMap());
}
