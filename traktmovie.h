#ifndef TRAKTMOVIE_H
#define TRAKTMOVIE_H

#include <QObject>
#include <QDate>
#include <QDateTime>
#include <QStringList>
#include <QTime>

#include "traktitem.h"

class TraktMovie : public TraktItem
{
    Q_OBJECT
    Q_PROPERTY(int year READ year WRITE setYear NOTIFY yearChanged)
    Q_PROPERTY(QString tagline READ tagline WRITE setTagline NOTIFY taglineChanged)
    Q_PROPERTY(QString overview READ overview WRITE setOverview NOTIFY overviewChanged)
    Q_PROPERTY(QDate released READ released WRITE setReleased NOTIFY releasedChanged)
    Q_PROPERTY(QTime runtime READ runtime WRITE setRuntime NOTIFY runtimeChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)
    Q_PROPERTY(QString trailer READ trailer WRITE setTrailer NOTIFY trailerChanged)
    Q_PROPERTY(QString homepage READ homepage WRITE setHomepage NOTIFY homepageChanged)
    Q_PROPERTY(double rating READ rating WRITE setRating NOTIFY ratingChanged)
    Q_PROPERTY(int votes READ votes WRITE setVotes NOTIFY votesChanged)
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(QStringList genres READ genres WRITE setGenres NOTIFY genresChanged)
    Q_PROPERTY(QString certification READ certification WRITE setCertification NOTIFY certificationChanged)
public:
    explicit TraktMovie(QObject *parent = 0);
    explicit TraktMovie(const QVariantMap &data, QObject *parent = 0);

    int year() const;
    void setYear(int year);

    QString tagline() const;
    void setTagline(QString tagline);

    QString overview() const;
    void setOverview(QString overview);

    QDate released() const;
    void setReleased(QDate released);

    QTime runtime() const;
    void setRuntime(QTime runtime);

    QDateTime updatedAt() const;
    void setUpdatedAt(QDateTime updatedAt);

    QString trailer() const;
    void setTrailer(QString trailer);

    QString homepage() const;
    void setHomepage(QString homepage);

    double rating() const;
    void setRating(double rating);

    int votes() const;
    void setVotes(int votes);

    QString language() const;
    void setLanguage(QString language);

    QStringList genres() const;
    void setGenres(QStringList genres);

    QString certification() const;
    void setCertification(QString certification);

    void parse(const QVariantMap &data) Q_DECL_OVERRIDE;

signals:
    void yearChanged();
    void taglineChanged();
    void overviewChanged();
    void releasedChanged();
    void runtimeChanged();
    void updatedAtChanged();
    void trailerChanged();
    void homepageChanged();
    void ratingChanged();
    void votesChanged();
    void languageChanged();
    void genresChanged();
    void certificationChanged();

protected:
    QString itemUrl() const Q_DECL_OVERRIDE;

private:
    int m_year;
    QString m_tagline;
    QString m_overview;
    QDate m_released;
    QTime m_runtime;
    QDateTime m_updatedAt;
    QString m_trailer;
    QString m_homepage;
    int m_rating;
    int m_votes;
    QString m_language;
    QStringList m_genres;
    QString m_certification;
};

#endif // TRAKTMOVIE_H
