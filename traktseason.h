#ifndef TRAKTSEASON_H
#define TRAKTSEASON_H

#include <QObject>

#include "traktitem.h"

class TraktShow;

class TraktSeason : public TraktItem
{
    Q_OBJECT
    Q_PROPERTY(int number READ number WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(double rating READ rating WRITE setRating NOTIFY ratingChanged)
    Q_PROPERTY(int votes READ votes WRITE setVotes NOTIFY votesChanged)
    Q_PROPERTY(int episodeCount READ episodeCount WRITE setEpisodeCount NOTIFY episodeCountChanged)
    Q_PROPERTY(int airedEpisodes READ airedEpisodes WRITE setAiredEpisodes NOTIFY airedEpisodesChanged)
    Q_PROPERTY(QString overview READ overview WRITE setOverview NOTIFY overviewChanged)
    Q_PROPERTY(TraktShow *show READ show WRITE setShow NOTIFY showChanged)
public:
    explicit TraktSeason(TraktShow *show = 0);
    explicit TraktSeason(const QVariantMap &data, TraktShow *show);

    int number() const;
    void setNumber(int number);

    double rating() const;
    void setRating(double rating);

    int votes() const;
    void setVotes(int votes);

    int episodeCount() const;
    void setEpisodeCount(int episodeCount);

    int airedEpisodes() const;
    void setAiredEpisodes(int airedEpisodes);

    QString overview() const;
    void setOverview(const QString &overview);

    TraktShow *show() const;
    void setShow(TraktShow *show);

    QString title() const Q_DECL_OVERRIDE;
    void setTitle(const QString &title) Q_DECL_OVERRIDE;

    void parse(const QVariantMap &data) Q_DECL_OVERRIDE;
    void load() Q_DECL_OVERRIDE;

signals:
    void idsChanged();
    void numberChanged();
    void ratingChanged();
    void votesChanged();
    void episodeCountChanged();
    void airedEpisodesChanged();
    void overviewChanged();
    void imagesChanged();
    void showChanged();

protected:
    QString itemUrl() const Q_DECL_OVERRIDE;

private:
    int m_number;
    double m_rating;
    int m_votes;
    int m_episodeCount;
    int m_airedEpisodes;
    QString m_overview;
    TraktShow *m_show;
};

#endif // TRAKTSEASON_H
