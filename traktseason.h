#ifndef TRAKTSEASON_H
#define TRAKTSEASON_H

#include <QObject>

#include "traktids.h"
#include "traktimageset.h"

class TraktReply;
class TraktShow;

class TraktSeason : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TraktIds *ids READ ids WRITE setIds NOTIFY idsChanged)
    Q_PROPERTY(int number READ number WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(double rating READ rating WRITE setRating NOTIFY ratingChanged)
    Q_PROPERTY(int votes READ votes WRITE setVotes NOTIFY votesChanged)
    Q_PROPERTY(int episodeCount READ episodeCount WRITE setEpisodeCount NOTIFY episodeCountChanged)
    Q_PROPERTY(int airedEpisodes READ airedEpisodes WRITE setAiredEpisodes NOTIFY airedEpisodesChanged)
    Q_PROPERTY(QString overview READ overview WRITE setOverview NOTIFY overviewChanged)
    Q_PROPERTY(TraktImageSet *images READ images WRITE setImages NOTIFY imagesChanged)
    Q_PROPERTY(TraktShow *show READ show WRITE setShow NOTIFY showChanged)
public:
    explicit TraktSeason(TraktShow *show = 0);
    explicit TraktSeason(const QVariantMap &data, TraktShow *show);

    TraktIds *ids() const;
    void setIds(TraktIds *ids);

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

    TraktImageSet *images() const;
    void setImages(TraktImageSet *images);

    TraktShow *show() const;
    void setShow(TraktShow *show);

    void parse(const QVariantMap &data);
    Q_INVOKABLE void load();

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

private:
    TraktIds *m_ids;
    int m_number;
    double m_rating;
    int m_votes;
    int m_episodeCount;
    int m_airedEpisodes;
    QString m_overview;
    TraktImageSet *m_images;
    TraktShow *m_show;

    bool m_loaded;

private slots:
    void onFullyLoaded(TraktReply *reply);
};

#endif // TRAKTSEASON_H
