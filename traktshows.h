#ifndef TRAKTSHOWS_H
#define TRAKTSHOWS_H

#include <QObject>

class TraktShow;
class TraktSeason;
class TraktShowsModel;
class TraktSeasonsModel;
class TraktEpisodesModel;

class TraktShows : public QObject
{
    Q_OBJECT
public:
    explicit TraktShows(QObject *parent = 0);

    Q_INVOKABLE TraktShowsModel *popular();
    Q_INVOKABLE TraktShowsModel *trending();

    Q_INVOKABLE TraktSeasonsModel *getSeasons(TraktShow *show);

    Q_INVOKABLE TraktEpisodesModel *getEpisodes(TraktSeason *season);
};

#endif // TRAKTSHOWS_H
