#include "traktepisode.h"

#include <QVariantMap>

#include "traktseason.h"
#include "traktshow.h"
#include "traktrequest.h"
#include "traktreply.h"
#include "traktpeoplemodel.h"

TraktEpisode::TraktEpisode(TraktSeason *season) :
    QObject(season),
    m_ids(0),
    m_number(0),
    m_rating(0),
    m_votes(0),
    m_season(season),
    m_loaded(false)
{
}

TraktEpisode::TraktEpisode(const QVariantMap &data, TraktSeason *season) :
    QObject(season),
    m_rating(0),
    m_votes(0),
    m_season(season),
    m_loaded(false)
{
    m_ids = new TraktIds(data.value("ids").toMap(), "shows", this);
    m_title = data.value("title").toString();
    m_number = data.value("number").toInt();
    m_images = new TraktImageSet(data.value("images").toMap(), this);
}

TraktIds *TraktEpisode::ids() const
{
    return m_ids;
}

void TraktEpisode::setIds(TraktIds *ids)
{
    m_ids = ids;
    emit idsChanged();
}

QString TraktEpisode::title() const
{
    return m_title;
}

void TraktEpisode::setTitle(const QString &title)
{
    m_title = title;
    emit titleChanged();
}

int TraktEpisode::number() const
{
    return m_number;
}

void TraktEpisode::setNumber(int number)
{
    m_number = number;
    emit numberChanged();
}

QString TraktEpisode::overview() const
{
    return m_overview;
}

void TraktEpisode::setOverview(const QString &overview)
{
    m_overview = overview;
    emit overviewChanged();
}

QDateTime TraktEpisode::firstAired() const
{
    return m_firstAired;
}

void TraktEpisode::setFirstAired(const QDateTime &firstAired)
{
    m_firstAired = firstAired;
    emit firstAiredChanged();
}

QDateTime TraktEpisode::updatedAt() const
{
    return m_updatedAt;
}

void TraktEpisode::setUpdatedAt(const QDateTime &updatedAt)
{
    m_updatedAt = updatedAt;
    emit updatedAtChanged();
}

double TraktEpisode::rating() const
{
    return m_rating;
}

void TraktEpisode::setRating(double rating)
{
    m_rating = rating;
    emit ratingChanged();
}

int TraktEpisode::votes() const
{
    return m_votes;
}

void TraktEpisode::setVotes(int votes)
{
    m_votes = votes;
    emit votesChanged();
}

QStringList TraktEpisode::availableTranslations() const
{
    return m_availableTranslations;
}

void TraktEpisode::setAvailableTranslations(const QStringList &availableTranslations)
{
    m_availableTranslations = availableTranslations;
    emit availableTranslationsChanged();
}

TraktImageSet *TraktEpisode::images() const
{
    return m_images;
}

void TraktEpisode::setImages(TraktImageSet *images)
{
    m_images = images;
    emit imagesChanged();
}

TraktSeason *TraktEpisode::season() const
{
    return m_season;
}

void TraktEpisode::setSeason(TraktSeason *season)
{
    m_season = season;
    emit seasonChanged();
}

void TraktEpisode::parse(const QVariantMap &data)
{
    setTitle(data.value("title").toString());
    setNumber(data.value("number").toInt());
    setOverview(data.value("overview").toString());
    setFirstAired(data.value("first_aired").toDateTime());
    setUpdatedAt(data.value("updated_at").toDateTime());
    setRating(data.value("rating").toDouble());
    setVotes(data.value("votes").toInt());
    setAvailableTranslations(data.value("available_translations").toStringList());

    m_loaded = true;
}

void TraktEpisode::load()
{
    if (m_loaded) {
        return;
    }

    TraktRequest *request = new TraktRequest(this);
    request->setPath(QString("/shows/%1/seasons/%2/episodes/%3").arg(m_season->show()->ids()->trakt()).arg(m_season->number()).arg(number()));
    request->addQueryItem("extended", "full");
    connect(request, &TraktRequest::replyReceived, this, &TraktEpisode::onFullyLoaded);
    request->send();
}

void TraktEpisode::onFullyLoaded(TraktReply *reply)
{
    reply->deleteLater();
    parse(reply->asMap());
}
