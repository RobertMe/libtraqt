#include "traktmovies.h"

#include "traktmoviesmodel.h"

TraktMovies::TraktMovies(QObject *parent) :
    QObject(parent)
{
}

TraktMoviesModel *TraktMovies::popular()
{
    TraktRequest *request = new TraktRequest(this);
    request->setPath("/movies/popular");
    request->addQueryItem("extended", "images");

    return new TraktMoviesModel(request);
}

TraktMoviesModel *TraktMovies::trending()
{
    TraktRequest *request = new TraktRequest(this);
    request->setPath("/movies/trending");
    request->addQueryItem("extended", "images");

    return new TraktMoviesModel(request);
}
