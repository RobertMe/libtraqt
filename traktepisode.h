#ifndef TRAKTEPISODE_H
#define TRAKTEPISODE_H

#include <QObject>
#include <QDateTime>
#include <QStringList>

class TraktIds;
class TraktImageSet;
class TraktSeason;
class TraktReply;

class TraktEpisode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TraktIds *ids READ ids WRITE setIds NOTIFY idsChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(int number READ number WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(QString overview READ overview WRITE setOverview NOTIFY overviewChanged)
    Q_PROPERTY(QDateTime firstAired READ firstAired WRITE setFirstAired NOTIFY firstAiredChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)
    Q_PROPERTY(double rating READ rating WRITE setRating NOTIFY ratingChanged)
    Q_PROPERTY(int votes READ votes WRITE setVotes NOTIFY votesChanged)
    Q_PROPERTY(QStringList availableTranslations READ availableTranslations WRITE setAvailableTranslations NOTIFY availableTranslationsChanged)
    Q_PROPERTY(TraktImageSet *images READ images WRITE setImages NOTIFY imagesChanged)
    Q_PROPERTY(TraktSeason *season READ season WRITE setSeason NOTIFY seasonChanged)
public:
    explicit TraktEpisode(TraktSeason *season = 0);
    explicit TraktEpisode(const QVariantMap &data, TraktSeason *season = 0);

    TraktIds *ids() const;
    void setIds(TraktIds *ids);

    QString title() const;
    void setTitle(const QString &title);

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

    TraktImageSet *images() const;
    void setImages(TraktImageSet *images);

    TraktSeason *season() const;
    void setSeason(TraktSeason *season);

    void parse(const QVariantMap &data);
    Q_INVOKABLE void load();

signals:
    void idsChanged();
    void titleChanged();
    void numberChanged();
    void overviewChanged();
    void firstAiredChanged();
    void updatedAtChanged();
    void ratingChanged();
    void votesChanged();
    void availableTranslationsChanged();
    void imagesChanged();
    void seasonChanged();

private:
    TraktIds *m_ids;
    QString m_title;
    int m_number;
    QString m_overview;
    QDateTime m_firstAired;
    QDateTime m_updatedAt;
    double m_rating;
    int m_votes;
    QStringList m_availableTranslations;
    TraktImageSet *m_images;
    TraktSeason *m_season;

    bool m_loaded;

private slots:
    void onFullyLoaded(TraktReply *reply);
};

#endif // TRAKTEPISODE_H
