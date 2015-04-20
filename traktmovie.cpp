#include "traktmovie.h"

#include <QVariantMap>

#include "traktrequest.h"
#include "traktreply.h"
#include "traktpeoplemodel.h"

TraktMovie::TraktMovie(QObject *parent) :
    QObject(parent),
    m_ids(0),
    m_year(0),
    m_rating(0),
    m_votes(0),
    m_people(0),
    m_loaded(false)
{
}

TraktMovie::TraktMovie(const QVariantMap &data, QObject *parent) :
    QObject(parent),
    m_year(0),
    m_rating(0),
    m_votes(0),
    m_people(0),
    m_loaded(false)
{
    m_ids = new TraktIds(data.value("ids").toMap(), "movies", this);
    m_title = data.value("title").toString();
    m_year = data.value("year").toInt();
    m_images = new TraktImageSet(data.value("images").toMap(), this);
}

TraktIds *TraktMovie::ids() const
{
    return m_ids;
}

void TraktMovie::setIds(TraktIds *ids)
{
    m_ids = ids;
    emit idsChanged();
}

QString TraktMovie::title() const
{
    return m_title;
}

void TraktMovie::setTitle(QString title)
{
    m_title = title;
    emit titleChanged();
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

TraktImageSet *TraktMovie::images() const
{
    return m_images;
}

void TraktMovie::setImages(TraktImageSet *images)
{
    m_images = images;
    emit imagesChanged();
}

TraktPeopleModel *TraktMovie::people()
{
    if (!m_people) {
        m_people = new TraktPeopleModel(m_ids, this);
    }
    return m_people;
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

    m_loaded = true;
}

void TraktMovie::load()
{
    if (m_loaded) {
        return;
    }

    TraktRequest *request = new TraktRequest(this);
    request->setPath(QString("/movies/%1").arg(ids()->trakt()));
    request->addQueryItem("extended", "full");
    connect(request, &TraktRequest::replyReceived, this, &TraktMovie::onFullyLoaded);
    request->send();
}

void TraktMovie::onFullyLoaded(TraktReply *reply)
{
    reply->deleteLater();
    parse(reply->asMap());
}
