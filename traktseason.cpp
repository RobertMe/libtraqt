#include "traktseason.h"

#include <QVariantMap>

#include "traktrequest.h"
#include "traktreply.h"
#include "traktshow.h"

TraktSeason::TraktSeason(TraktShow *show) :
    QObject(show),
    m_ids(0),
    m_number(0),
    m_rating(0),
    m_votes(0),
    m_episodeCount(0),
    m_airedEpisodes(0),
    m_images(0),
    m_loaded(false)
{
}

TraktSeason::TraktSeason(const QVariantMap &data, TraktShow *show) :
    QObject(show),
    m_rating(0),
    m_votes(0),
    m_episodeCount(0),
    m_airedEpisodes(0),
    m_loaded(false)
{
    m_ids = new TraktIds(data.value("ids").toMap(), "seasons", this);
    m_number = data.value("number").toInt();
    m_images = new TraktImageSet(data.value("images").toMap(), this);
}

TraktIds *TraktSeason::ids() const
{
    return m_ids;
}

void TraktSeason::setIds(TraktIds *ids)
{
    m_ids = ids;
    emit idsChanged();
}

int TraktSeason::number() const
{
    return m_number;
}

void TraktSeason::setNumber(int number)
{
    m_number = number;
    emit numberChanged();
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

TraktImageSet *TraktSeason::images() const
{
    return m_images;
}

void TraktSeason::setImages(TraktImageSet *images)
{
    m_images = images;
    emit imagesChanged();
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

void TraktSeason::parse(const QVariantMap &data)
{
    setNumber(data.value("number").toInt());
    setRating(data.value("rating").toDouble());
    setVotes(data.value("votes").toInt());
    setEpisodeCount(data.value("episode_count").toInt());
    setAiredEpisodes(data.value("aired_episodes").toInt());
    setOverview(data.value("overview").toString());

    m_loaded = true;
}

void TraktSeason::load()
{
    if (m_loaded) {
        return;
    }

    TraktRequest *request = new TraktRequest(this);
    request->setPath(QString("/shows/%1/seasons/%2").arg(m_show->ids()->trakt(), ids()->trakt()));
    request->addQueryItem("extended", "full");
    connect(request, &TraktRequest::replyReceived, this, &TraktSeason::onFullyLoaded);
    request->send();
}

void TraktSeason::onFullyLoaded(TraktReply *reply)
{
    reply->deleteLater();
    parse(reply->asMap());
}
