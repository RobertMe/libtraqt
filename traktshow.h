#ifndef TRAKTSHOW_H
#define TRAKTSHOW_H

#include <QObject>
#include <QDateTime>
#include <QTime>
#include <QStringList>

#include "traktitem.h"

class TraktShow : public TraktItem
{
    Q_OBJECT
    Q_PROPERTY(int year READ year WRITE setYear NOTIFY yearChanged)
    Q_PROPERTY(QString overview READ overview WRITE setOverview NOTIFY overviewChanged)
    Q_PROPERTY(QDateTime firstAired READ firstAired WRITE setFirstAired NOTIFY firstAiredChanged)
    Q_PROPERTY(QTime runtime READ runtime WRITE setRuntime NOTIFY runtimeChanged)
    Q_PROPERTY(QString certification READ certification WRITE setCertification NOTIFY certificationChanged)
    Q_PROPERTY(QString network READ network WRITE setNetwork NOTIFY networkChanged)
    Q_PROPERTY(QString country READ country WRITE setCountry NOTIFY countryChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)
    Q_PROPERTY(QString trailer READ trailer WRITE setTrailer NOTIFY trailerChanged)
    Q_PROPERTY(QString homepage READ homepage WRITE setHomepage NOTIFY homepageChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(double rating READ rating WRITE setRating NOTIFY ratingChanged)
    Q_PROPERTY(int votes READ votes WRITE setVotes NOTIFY votesChanged)
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(QStringList availableTranslations READ availableTranslations WRITE setAvailableTranslations NOTIFY availableTranslationsChanged)
    Q_PROPERTY(QStringList genres READ genres WRITE setGenres NOTIFY genresChanged)
    Q_PROPERTY(int airedEpisodes READ airedEpisodes WRITE setAiredEpisodes NOTIFY airedEpisodesChanged)
public:
    explicit TraktShow(QObject *parent = 0);
    explicit TraktShow(const QVariantMap &data, QObject *parent = 0);

    int year() const;
    void setYear(int year);

    QString overview() const;
    void setOverview(const QString &overview);

    QDateTime firstAired() const;
    void setFirstAired(const QDateTime &firstAired);

    QTime runtime() const;
    void setRuntime(const QTime &runtime);

    QString certification() const;
    void setCertification(const QString &certification);

    QString network() const;
    void setNetwork(const QString &network);

    QString country() const;
    void setCountry(const QString &country);

    QDateTime updatedAt() const;
    void setUpdatedAt(const QDateTime &updatedAt);

    QString trailer() const;
    void setTrailer(const QString &trailer);

    QString homepage() const;
    void setHomepage(const QString &homepage);

    QString status() const;
    void setStatus(const QString &status);

    double rating() const;
    void setRating(double rating);

    int votes() const;
    void setVotes(int votes);

    QString language() const;
    void setLanguage(const QString &language);

    QStringList availableTranslations() const;
    void setAvailableTranslations(const QStringList &availableTranslations);

    QStringList genres() const;
    void setGenres(const QStringList &genres);

    int airedEpisodes() const;
    void setAiredEpisodes(int airedEpisodes);

    void parse(const QVariantMap &data) Q_DECL_OVERRIDE;

signals:
    void yearChanged();
    void overviewChanged();
    void firstAiredChanged();
    void runtimeChanged();
    void certificationChanged();
    void networkChanged();
    void countryChanged();
    void updatedAtChanged();
    void trailerChanged();
    void homepageChanged();
    void statusChanged();
    void ratingChanged();
    void votesChanged();
    void languageChanged();
    void availableTranslationsChanged();
    void genresChanged();
    void airedEpisodesChanged();

protected:
    QString itemUrl() const Q_DECL_OVERRIDE;

private:
    int m_year;
    QString m_overview;
    QDateTime m_firstAired;
    QTime m_runtime;
    QString m_certification;
    QString m_network;
    QString m_country;
    QDateTime m_updatedAt;
    QString m_trailer;
    QString m_homepage;
    QString m_status;
    double m_rating;
    int m_votes;
    QString m_language;
    QStringList m_availableTranslations;
    QStringList m_genres;
    int m_airedEpisodes;
};

#endif // TRAKTSHOW_H
