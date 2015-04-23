#include "traktcheckin.h"

#include "traktids.h"

TraktCheckin::TraktCheckin(QObject *parent) :
    QObject(parent),
    m_shareOnFacebook(false),
    m_shareOnTwitter(false),
    m_shareOnTumblr(false)
{
}

TraktIds *TraktCheckin::item() const
{
    return m_item;
}
void TraktCheckin::setItem(TraktIds *ids)
{
    m_item = ids;
    emit itemChanged();
}

bool TraktCheckin::shareOnFacebook() const
{
    return m_shareOnFacebook;
}

void TraktCheckin::setShareOnFacebook(bool share)
{
    m_shareOnFacebook = share;
    emit shareOnFacebookChanged();
}

bool TraktCheckin::shareOnTwitter() const
{
    return m_shareOnTwitter;
}

void TraktCheckin::setShareOnTwitter(bool share)
{
    m_shareOnTwitter = share;
    emit shareOnTwitterChanged();
}

bool TraktCheckin::shareOnTumblr() const
{
    return m_shareOnTumblr;
}

void TraktCheckin::setShareOnTumblr(bool share)
{
    m_shareOnTumblr = share;
    emit shareOnTumblrChanged();
}

QString TraktCheckin::message() const
{
    return m_message;
}

void TraktCheckin::setMessage(const QString &message)
{
    m_message = message;
    emit messageChanged();
}

QString TraktCheckin::appVersion() const
{
    return m_appVersion;
}

void TraktCheckin::setAppVersion(const QString &appVersion)
{
    m_appVersion = appVersion;
    emit appVersionChanged();
}

QString TraktCheckin::appDate() const
{
    return m_appDate;
}

void TraktCheckin::setAppDate(const QString &appDate)
{
    m_appDate = appDate;
    emit appDateChanged();
}

void TraktCheckin::checkIn()
{
    QVariantMap data;

    QString typeName;
    if (m_item->type() == "movies") {
        typeName = "movie";
    } else if (m_item->type() == "episodes") {
        typeName = "episode";
    } else {
        return;
    }

    QVariantMap ids;
    ids.insert("trakt", m_item->trakt());
    QVariantMap item;
    item.insert("ids", ids);
    data.insert(typeName, item);

    QVariantMap sharing;
    sharing.insert("facebook", m_shareOnFacebook);
    sharing.insert("twitter", m_shareOnTwitter);
    sharing.insert("tumblr", m_shareOnTumblr);
    data.insert("sharing", sharing);

    data.insert("message", m_message);
    data.insert("app_version", m_appVersion);
    data.insert("app_date", m_appDate);

    TraktRequest *request = new TraktRequest();
    request->setPath("/checkin");
    request->setOperation(TraktRequest::OperationPost);
    request->setData(data);

    request->fire();
}
