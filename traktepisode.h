#ifndef TRAKTEPISODE_H
#define TRAKTEPISODE_H

#include <QObject>
#include <QDateTime>
#include <QStringList>

#include "traktitem.h"

class TraktSeason;

class TraktEpisode : public TraktItem
{
    Q_OBJECT
    Q_PROPERTY(int number READ number WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(QString overview READ overview WRITE setOverview NOTIFY overviewChanged)
    Q_PROPERTY(QDateTime firstAired READ firstAired WRITE setFirstAired NOTIFY firstAiredChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)
    Q_PROPERTY(double rating READ rating WRITE setRating NOTIFY ratingChanged)
    Q_PROPERTY(int votes READ votes WRITE setVotes NOTIFY votesChanged)
    Q_PROPERTY(QStringList availableTranslations READ availableTranslations WRITE setAvailableTranslations NOTIFY availableTranslationsChanged)
    Q_PROPERTY(TraktSeason *season READ season WRITE setSeason NOTIFY seasonChanged)
public:
    explicit TraktEpisode(TraktSeason *season = 0);
    explicit TraktEpisode(const QVariantMap &data, TraktSeason *season = 0);

    int number() const;
    void setNumber(int number);

    QString overview() const;
    void setOverview(const QString &overview);

    QDateTime firstAired() const;
    void setFirstAired(const QDateTime &firstAired);

    QDateTime updatedAt() const;
    void setUpdatedAt(const QDateTime &updatedAt);

    double rating() const;
    void setRating(double rating);

    int votes() const;
    void setVotes(int votes);

    QStringList availableTranslations() const;
    void setAvailableTranslations(const QStringList &availableTranslations);

    TraktSeason *season() const;
    void setSeason(TraktSeason *season);

    virtual TraktImages *image() const Q_DECL_OVERRIDE;

    void parse(const QVariantMap &data) Q_DECL_OVERRIDE;

signals:
    void numberChanged();
    void overviewChanged();
    void firstAiredChanged();
    void updatedAtChanged();
    void ratingChanged();
    void votesChanged();
    void availableTranslationsChanged();
    void seasonChanged();

protected:
    QString itemUrl() const Q_DECL_OVERRIDE;
    virtual void connectImageChanged(TraktImageSet *images) const Q_DECL_OVERRIDE;

private:
    int m_number;
    QString m_overview;
    QDateTime m_firstAired;
    QDateTime m_updatedAt;
    double m_rating;
    int m_votes;
    QStringList m_availableTranslations;
    TraktSeason *m_season;
};

#endif // TRAKTEPISODE_H
