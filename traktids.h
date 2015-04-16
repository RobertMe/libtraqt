#ifndef TRAKTIDS_H
#define TRAKTIDS_H

#include <QObject>

class TraktIds : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int trakt READ trakt WRITE setTrakt NOTIFY traktChanged)
    Q_PROPERTY(QString slug READ slug WRITE setSlug NOTIFY slugChanged)
    Q_PROPERTY(int tvdb READ tvdb WRITE setTvdb NOTIFY tvdbChanged)
    Q_PROPERTY(QString imdb READ imdb WRITE setImdb NOTIFY imdbChanged)
    Q_PROPERTY(int tmdb READ tmdb WRITE setTmdb NOTIFY tmdbChanged)
    Q_PROPERTY(int tvrage READ tvrage WRITE setTvrage NOTIFY tvrageChanged)
public:
    explicit TraktIds(const QString &type, QObject *parent = 0);
    explicit TraktIds(const QVariantMap &data, const QString &type, QObject *parent = 0);

    QString type() const;

    int trakt() const;
    void setTrakt(int id);

    QString slug() const;
    void setSlug(const QString &slug);

    int tvdb() const;
    void setTvdb(int id);

    QString imdb() const;
    void setImdb(const QString &id);

    int tmdb() const;
    void setTmdb(int id);

    int tvrage();
    void setTvrage(int id);

signals:
    void traktChanged();
    void slugChanged();
    void tvdbChanged();
    void imdbChanged();
    void tmdbChanged();
    void tvrageChanged();

private:
    QString m_type;
    int m_trakt;
    QString m_slug;
    int m_tvdb;
    QString m_imdb;
    int m_tmdb;
    int m_tvrage;
};

Q_DECLARE_METATYPE(TraktIds*)

#endif // TRAKTIDS_H
