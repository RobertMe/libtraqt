#include "traktimages.h"

#include <QVariantMap>

TraktImages::TraktImages(QObject *parent) :
    QObject(parent)
{
}

TraktImages::TraktImages(const QVariantMap &data, QObject *parent) :
    QObject(parent)
{
    m_full = data.value("full").toString();
    m_medium = data.value("medium").toString();
    m_thumb = data.value("thumb").toString();
}

QString TraktImages::full() const
{
    return m_full;
}

void TraktImages::setFull(const QString &url)
{
    m_full = url;
    emit fullChanged();
}

QString TraktImages::medium() const
{
    return m_medium;
}

void TraktImages::setMedium(const QString &url)
{
    m_medium = url;
    emit mediumChanged();
}

QString TraktImages::thumb() const
{
    return m_thumb;
}

void TraktImages::setThumb(const QString &url)
{
    m_thumb = url;
    emit thumbChanged();
}
