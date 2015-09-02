#include "traktepisode.h"

#include <QVariantMap>

#include "traktseason.h"
#include "traktshow.h"

TraktEpisode::TraktEpisode(TraktSeason *season) :
    TraktItem(season),
    m_number(0),
    m_rating(0),
    m_votes(0),
    m_season(season)
{
}

TraktEpisode::TraktEpisode(const QVariantMap &data, TraktSeason *season) :
    TraktItem(season),
    m_rating(0),
    m_votes(0),
    m_season(season)
{
    m_ids = new TraktIds(data.value("ids").toMap(), "shows", this);
    m_title = data.value("title").toString();
    m_number = data.value("number").toInt();
    m_images = new TraktImageSet(data.value("images").toMap(), this);
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

    setLoaded(true);
}

QString TraktEpisode::itemUrl() const
{
    return QString("/shows/%1/seasons/%2/episodes/%3").arg(m_season->show()->ids()->trakt()).arg(m_season->number()).arg(number());
}
