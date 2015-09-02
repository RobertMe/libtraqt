#include "traktmovie.h"

#include <QVariantMap>

TraktMovie::TraktMovie(QObject *parent) :
    TraktItem(parent),
    m_year(0),
    m_rating(0),
    m_votes(0)
{
}

TraktMovie::TraktMovie(const QVariantMap &data, QObject *parent) :
    TraktItem(parent),
    m_year(0),
    m_rating(0),
    m_votes(0)
{
    m_ids = new TraktIds(data.value("ids").toMap(), "movies", this);
    m_title = data.value("title").toString();
    m_year = data.value("year").toInt();
    m_images = new TraktImageSet(data.value("images").toMap(), this);
}

int TraktMovie::year() const
{
    return m_year;
}

void TraktMovie::setYear(int year)
{
    m_year = year;
    emit yearChanged();
}

QString TraktMovie::tagline() const
{
    return m_tagline;
}

void TraktMovie::setTagline(QString tagline)
{
    m_tagline = tagline;
    emit taglineChanged();
}

QString TraktMovie::overview() const
{
    return m_overview;
}

void TraktMovie::setOverview(QString overview)
{
    m_overview = overview;
    emit overviewChanged();
}

QDate TraktMovie::released() const
{
    return m_released;
}

void TraktMovie::setReleased(QDate released)
{
    m_released = released;
    emit releasedChanged();
}

QTime TraktMovie::runtime() const
{
    return m_runtime;
}

void TraktMovie::setRuntime(QTime runtime)
{
    m_runtime = runtime;
    emit runtimeChanged();
}

QDateTime TraktMovie::updatedAt() const
{
    return m_updatedAt;
}

void TraktMovie::setUpdatedAt(QDateTime updatedAt)
{
    m_updatedAt = updatedAt;
    emit updatedAtChanged();
}

QString TraktMovie::trailer() const
{
    return m_trailer;
}

void TraktMovie::setTrailer(QString trailer)
{
    m_trailer = trailer;
    emit trailerChanged();
}

QString TraktMovie::homepage() const
{
    return m_homepage;
}

void TraktMovie::setHomepage(QString homepage)
{
    m_homepage = homepage;
    emit homepageChanged();
}

double TraktMovie::rating() const
{
    return m_rating;
}

void TraktMovie::setRating(double rating)
{
    m_rating = rating;
    emit ratingChanged();
}

int TraktMovie::votes() const
{
    return m_votes;
}

void TraktMovie::setVotes(int votes)
{
    m_votes = votes;
    emit votesChanged();
}

QString TraktMovie::language() const
{
    return m_language;
}

void TraktMovie::setLanguage(QString language)
{
    m_language = language;
    emit languageChanged();
}

QStringList TraktMovie::genres() const
{
    return m_genres;
}

void TraktMovie::setGenres(QStringList genres)
{
    m_genres = genres;
    emit genresChanged();
}

QString TraktMovie::certification() const
{
    return m_certification;
}

void TraktMovie::setCertification(QString certification)
{
    m_certification = certification;
    emit certificationChanged();
}

void TraktMovie::parse(const QVariantMap &data)
{
    setYear(data.value("year").toInt());
    setTagline(data.value("tagline").toString());
    setOverview(data.value("overview").toString());
    setReleased(data.value("released").toDate());
    setRuntime(QTime(0, 0).addSecs(data.value("runtime").toInt() * 60));
    setTrailer(data.value("trailer").toString());
    setHomepage(data.value("homepage").toString());
    setRating(data.value("rating").toDouble());
    setVotes(data.value("votes").toInt());
    setLanguage(data.value("language").toString());
    setGenres(data.value("genres").toStringList());
    setCertification(data.value("certification").toString());

    setLoaded(true);
}

QString TraktMovie::itemUrl() const
{
    return QString("/movies/%1").arg(ids()->trakt());
}
