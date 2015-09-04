#include "traktitem.h"

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
    if (m_images) {
        disconnect(m_images, 0, this, 0);
    }
    m_images = images;
    if (m_images) {
        connectImageChanged(m_images);
    }
    emit imagesChanged();
}

TraktImages *TraktItem::image() const
{
    if (m_images) {
        return m_images->poster();
    }

    return 0;
}

bool TraktItem::loaded() const
{
    return m_loaded;
}

void TraktItem::setLoaded(bool loaded)
{
    m_loaded = loaded;
    emit loadedChanged();
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

void TraktItem::connectImageChanged(TraktImageSet *images) const
{
    connect(images, &TraktImageSet::posterChanged, this, &TraktItem::imageChanged);
}
