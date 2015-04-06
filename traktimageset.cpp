#include "traktimageset.h"

#include <QVariantMap>

TraktImageSet::TraktImageSet(QObject *parent) :
    QObject(parent),
    m_poster(0),
    m_fanart(0),
    m_screenshot(0),
    m_headshot(0),
    m_banner(0),
    m_logo(0),
    m_clearart(0),
    m_thumb(0),
    m_avatar(0)
{
}

TraktImageSet::TraktImageSet(const QVariantMap &data, QObject *parent) :
    QObject(parent),
    m_poster(createImages(data.value("poster"))),
    m_fanart(0),
    m_screenshot(0),
    m_headshot(0),
    m_banner(0),
    m_logo(0),
    m_clearart(0),
    m_thumb(0),
    m_avatar(0)
{
}

TraktImages *TraktImageSet::poster() const
{
    return m_poster;
}

void TraktImageSet::setPoster(TraktImages *images)
{
    m_poster = images;
    emit posterChanged();
}

TraktImages *TraktImageSet::TraktImageSet::fanart() const
{
    return m_fanart;
}

void TraktImageSet::setFanart(TraktImages *images)
{
    m_fanart = images;
    emit fanartChanged();
}

TraktImages *TraktImageSet::screenshot() const
{
    return m_screenshot;
}

void TraktImageSet::setScreenshot(TraktImages *images)
{
    m_screenshot = images;
    emit screenshotChanged();
}

TraktImages *TraktImageSet::headshot() const
{
    return m_headshot;
}

void TraktImageSet::setHeadshot(TraktImages *images)
{
    m_headshot = images;
    emit headshotChanged();
}

TraktImages *TraktImageSet::banner() const
{
    return m_banner;
}

void TraktImageSet::setBanner(TraktImages *images)
{
    m_banner = images;
    emit bannerChanged();
}

TraktImages *TraktImageSet::logo() const
{
    return m_logo;
}

void TraktImageSet::setLogo(TraktImages *images)
{
    m_logo = images;
    emit logoChanged();
}

TraktImages *TraktImageSet::clearart() const
{
    return m_clearart;
}

void TraktImageSet::setClearart(TraktImages *images)
{
    m_clearart = images;
    emit clearartChanged();
}

TraktImages *TraktImageSet::thumb() const
{
    return m_thumb;
}

void TraktImageSet::setThumb(TraktImages *images)
{
    m_thumb = images;
    emit thumbChanged();
}

TraktImages *TraktImageSet::avatar() const
{
    return m_avatar;
}

void TraktImageSet::setAvatar(TraktImages *images)
{
    m_avatar = images;
    emit avatarChanged();
}

TraktImages *TraktImageSet::createImages(QVariant imageData)
{
    if (!imageData.isValid()) {
        return 0;
    } else {
        return new TraktImages(imageData.toMap(), this);
    }
}
