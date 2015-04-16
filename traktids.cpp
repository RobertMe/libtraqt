#include "traktids.h"

#include <QVariantMap>

TraktIds::TraktIds(const QString &type, QObject *parent) :
    QObject(parent),
    m_type(type)
{
}

TraktIds::TraktIds(const QVariantMap &data, const QString &type, QObject *parent) :
    QObject(parent),
    m_type(type)
{
    m_trakt = data.value("trakt").toInt();
    m_slug = data.value("slug").toString();
    m_tvdb = data.value("tvdb").toInt();
    m_imdb = data.value("imdb").toString();
    m_tmdb = data.value("tmdb").toInt();
    m_tvrage = data.value("tvrage").toInt();
}

QString TraktIds::type() const
{
    return m_type;
}

int TraktIds::trakt() const
{
    return m_trakt;
}

void TraktIds::setTrakt(int id)
{
    m_trakt = id;
    emit traktChanged();
}

QString TraktIds::slug() const
{
    return m_slug;
}

void TraktIds::setSlug(const QString &slug)
{
    m_slug = slug;
    emit slugChanged();
}

int TraktIds::tvdb() const
{
    return m_tvdb;
}

void TraktIds::setTvdb(int id)
{
    m_tvdb = id;
    emit tvdbChanged();
}

QString TraktIds::imdb() const
{
    return m_imdb;
}

void TraktIds::setImdb(const QString &id)
{
    m_imdb = id;
    emit imdbChanged();
}

int TraktIds::tmdb() const
{
    return m_tmdb;
}

void TraktIds::setTmdb(int id)
{
    m_tmdb = id;
    emit tmdbChanged();
}

int TraktIds::tvrage()
{
    return m_tvrage;
}

void TraktIds::setTvrage(int id)
{
    m_tvrage = id;
    emit tvrageChanged();
}
