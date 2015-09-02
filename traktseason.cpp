#include "traktseason.h"

#include <QVariantMap>

#include "traktshow.h"

TraktSeason::TraktSeason(TraktShow *show) :
    TraktItem(show),
    m_number(0),
    m_rating(0),
    m_votes(0),
    m_episodeCount(0),
    m_airedEpisodes(0),
    m_show(show)
{
}

TraktSeason::TraktSeason(const QVariantMap &data, TraktShow *show) :
    TraktItem(show),
    m_rating(0),
    m_votes(0),
    m_episodeCount(0),
    m_airedEpisodes(0),
    m_show(show)
{
    m_ids = new TraktIds(data.value("ids").toMap(), "seasons", this);
    m_number = data.value("number").toInt();
    m_images = new TraktImageSet(data.value("images").toMap(), this);
}

int TraktSeason::number() const
{
    return m_number;
}

void TraktSeason::setNumber(int number)
{
    m_number = number;
    emit numberChanged();
    emit titleChanged();
}

double TraktSeason::rating() const
{
    return m_rating;
}

void TraktSeason::setRating(double rating)
{
    m_rating = rating;
    emit ratingChanged();
}

int TraktSeason::votes() const
{
    return m_votes;
}

void TraktSeason::setVotes(int votes)
{
    m_votes = votes;
    emit votesChanged();
}

int TraktSeason::episodeCount() const
{
    return m_episodeCount;
}

void TraktSeason::setEpisodeCount(int episodeCount)
{
    m_episodeCount = episodeCount;
    emit episodeCountChanged();
}

int TraktSeason::airedEpisodes() const
{
    return m_airedEpisodes;
}

void TraktSeason::setAiredEpisodes(int airedEpisodes)
{
    m_airedEpisodes = airedEpisodes;
    emit airedEpisodesChanged();
}

QString TraktSeason::overview() const
{
    return m_overview;
}

void TraktSeason::setOverview(const QString &overview)
{
    m_overview = overview;
    emit overviewChanged();
}

TraktShow *TraktSeason::show() const
{
    return m_show;
}

void TraktSeason::setShow(TraktShow *show)
{
    m_show = show;
    setParent(show);
    emit showChanged();
}

QString TraktSeason::title() const
{
    return QString::number(m_number);
}

void TraktSeason::setTitle(const QString &title)
{
    Q_UNUSED(title)
}

void TraktSeason::parse(const QVariantMap &data)
{
    setNumber(data.value("number").toInt());
    setRating(data.value("rating").toDouble());
    setVotes(data.value("votes").toInt());
    setEpisodeCount(data.value("episode_count").toInt());
    setAiredEpisodes(data.value("aired_episodes").toInt());
    setOverview(data.value("overview").toString());

    setLoaded(true);
}

void TraktSeason::load()
{
}

QString TraktSeason::itemUrl() const
{
    return QString();
}
