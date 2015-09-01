#include "traktpeople.h"

#include "traktids.h"
#include "traktpeoplemodel.h"

TraktPeople::TraktPeople(QObject *parent) :
    QObject(parent)
{
}

TraktPeopleModel *TraktPeople::people(TraktIds *ids)
{
    return new TraktPeopleModel(ids);
}

TraktPersonMoviesModel *TraktPeople::getMovies(TraktPerson *person)
{
    return new TraktPersonMoviesModel(person);
}

TraktPersonShowsModel *TraktPeople::getShows(TraktPerson *person)
{
    return new TraktPersonShowsModel(person);
}
