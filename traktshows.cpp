#include "traktshows.h"

#include "traktseasonsmodel.h"

TraktShows::TraktShows(QObject *parent) :
    QObject(parent)
{
}

TraktShowsModel *TraktShows::popular()
{
    TraktRequest *request = new TraktRequest(this);
    request->setPath("/shows/popular");
    request->addQueryItem("extended", "images");

    return new TraktShowsModel(request, this);
}

TraktShowsModel *TraktShows::trending()
{
    TraktRequest *request = new TraktRequest(this);
    request->setPath("/shows/trending");
    request->addQueryItem("extended", "images");

    return new TraktShowsModel(request, this);
}

TraktSeasonsModel *TraktShows::getSeasons(TraktShow *show)
{
    return new TraktSeasonsModel(show);
}
