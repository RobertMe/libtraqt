#include "traktshows.h"

#include "traktseasonsmodel.h"
#include "traktepisodesmodel.h"

TraktShows::TraktShows(QObject *parent) :
    QObject(parent)
{
}

TraktShowsModel *TraktShows::popular()
{
    TraktRequest *request = new TraktRequest(this);
    request->setPath("/shows/popular");
    request->addQueryItem("extended", "images");

    return new TraktShowsModel(request);
}

TraktShowsModel *TraktShows::trending()
{
    TraktRequest *request = new TraktRequest(this);
    request->setPath("/shows/trending");
    request->addQueryItem("extended", "images");

    return new TraktShowsModel(request);
}

TraktSeasonsModel *TraktShows::getSeasons(TraktShow *show)
{
    return new TraktSeasonsModel(show);
}

TraktEpisodesModel *TraktShows::getEpisodes(TraktSeason *season)
{
    return new TraktEpisodesModel(season);
}
