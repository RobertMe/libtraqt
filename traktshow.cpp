#include "traktshow.h"

#include <QVariantMap>

#include "traktrequest.h"
#include "traktreply.h"
#include "traktpeoplemodel.h"

TraktShow::TraktShow(QObject *parent) :
    QObject(parent),
    m_ids(0),
    m_year(0),
    m_rating(0),
    m_votes(0),
    m_airedEpisodes(0),
    m_loaded(false)
{
}

TraktShow::TraktShow(const QVariantMap &data, QObject *parent) :
    QObject(parent),
    m_year(0),
    m_rating(0),
    m_votes(0),
    m_airedEpisodes(0),
    m_loaded(false)
{
    m_ids = new TraktIds(data.value("ids").toMap(), "shows", this);
    m_title = data.value("title").toString();
    m_year = data.value("year").toInt();
    m_images = new TraktImageSet(data.value("images").toMap(), this);
}

TraktIds *TraktShow::ids() const
{
    return m_ids;
}

void TraktShow::setIds(TraktIds *ids)
{
    m_ids = ids;
    emit idsChanged();
}

QString TraktShow::title() const
{
    return m_title;
}

void TraktShow::setTitle(const QString &title)
{
    m_title = title;
    emit titleChanged();
}

int TraktShow::year() const
{
    return m_year;
}

void TraktShow::setYear(int year)
{
    m_year = year;
    emit yearChanged();
}

QString TraktShow::overview() const
{
    return m_overview;
}

void TraktShow::setOverview(const QString &overview)
{
    m_overview = overview;
    emit overviewChanged();
}

QDateTime TraktShow::firstAired() const
{
    return m_firstAired;
}

void TraktShow::setFirstAired(const QDateTime &firstAired)
{
    m_firstAired = firstAired;
    emit firstAiredChanged();
}

QTime TraktShow::runtime() const
{
    return m_runtime;
}

void TraktShow::setRuntime(const QTime &runtime)
{
    m_runtime = runtime;
    emit runtimeChanged();
}

QString TraktShow::certification() const
{
    return m_certification;
}

void TraktShow::setCertification(const QString &certification)
{
    m_certification = certification;
    emit certificationChanged();
}

QString TraktShow::network() const
{
    return m_network;
}

void TraktShow::setNetwork(const QString &network)
{
    m_network = network;
    emit networkChanged();
}

QString TraktShow::country() const
{
    return m_country;
}

void TraktShow::setCountry(const QString &country)
{
    m_country = country;
    emit countryChanged();
}

QDateTime TraktShow::updatedAt() const
{
    return m_updatedAt;
}

void TraktShow::setUpdatedAt(const QDateTime &updatedAt)
{
    m_updatedAt = updatedAt;
    emit updatedAtChanged();
}

QString TraktShow::trailer() const
{
    return m_trailer;
}

void TraktShow::setTrailer(const QString &trailer)
{
    m_trailer = trailer;
    emit trailerChanged();
}

QString TraktShow::homepage() const
{
    return m_homepage;
}

void TraktShow::setHomepage(const QString &homepage)
{
    m_homepage = homepage;
    emit homepageChanged();
}

QString TraktShow::status() const
{
    return m_status;
}

void TraktShow::setStatus(const QString &status)
{
    m_status = status;
    emit statusChanged();
}

double TraktShow::rating() const
{
    return m_rating;
}

void TraktShow::setRating(double rating)
{
    m_rating = rating;
    emit ratingChanged();
}

int TraktShow::votes() const
{
    return m_votes;
}

void TraktShow::setVotes(int votes)
{
    m_votes = votes;
    emit votesChanged();
}

QString TraktShow::language() const
{
    return m_language;
}

void TraktShow::setLanguage(const QString &language)
{
    m_language = language;
    emit languageChanged();
}

QStringList TraktShow::availableTranslations() const
{
    return m_availableTranslations;
}

void TraktShow::setAvailableTranslations(const QStringList &availableTranslations)
{
    m_availableTranslations = availableTranslations;
    emit availableTranslationsChanged();
}

QStringList TraktShow::genres() const
{
    return m_genres;
}

void TraktShow::setGenres(const QStringList &genres)
{
    m_genres = genres;
    emit genresChanged();
}

int TraktShow::airedEpisodes() const
{
    return m_airedEpisodes;
}

void TraktShow::setAiredEpisodes(int airedEpisodes)
{
    m_airedEpisodes = airedEpisodes;
    emit airedEpisodesChanged();
}

TraktImageSet *TraktShow::images() const
{
    return m_images;
}

void TraktShow::setImages(TraktImageSet *images)
{
    m_images = images;
    emit imagesChanged();
}

void TraktShow::parse(const QVariantMap &data)
{
    setYear(data.value("year").toInt());
    setOverview(data.value("overview").toString());
    setFirstAired(data.value("first_aired").toDateTime());
    setRuntime(QTime(0, 0).addSecs(data.value("runtime").toInt() * 60));
    setCertification(data.value("certification").toString());
    setNetwork(data.value("network").toString());
    setCountry(data.value("country").toString());
    setUpdatedAt(data.value("updated_at").toDateTime());
    setTrailer(data.value("trailer").toString());
    setHomepage(data.value("homepage").toString());
    setStatus(data.value("status").toString());
    setRating(data.value("rating").toDouble());
    setVotes(data.value("votes").toInt());
    setLanguage(data.value("language").toString());
    setAvailableTranslations(data.value("available_translations").toStringList());
    setGenres(data.value("genres").toStringList());
    setAiredEpisodes(data.value("aired_episodes").toInt());

    m_loaded = true;
}

void TraktShow::load()
{
    if (m_loaded) {
        return;
    }

    TraktRequest *request = new TraktRequest(this);
    request->setPath(QString("/shows/%1").arg(ids()->trakt()));
    request->addQueryItem("extended", "full");
    connect(request, &TraktRequest::replyReceived, this, &TraktShow::onFullyLoaded);
    request->send();
}

void TraktShow::onFullyLoaded(TraktReply *reply)
{
    reply->deleteLater();
    parse(reply->asMap());
}
