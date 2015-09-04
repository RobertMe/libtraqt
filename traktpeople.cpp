#include "traktpeople.h"

#include "traktpeoplemodel.h"
#include "traktpersonmoviesmodel.h"
#include "traktpersonshowsmodel.h"

TraktPeople::TraktPeople(QObject *parent) :
    QObject(parent)
{
}

TraktPeopleModel *TraktPeople::people(TraktIds *ids)
{
    return new TraktPeopleModel(ids);
}

TraktMoviesModel *TraktPeople::getMovies(TraktPerson *person)
{
    return new TraktPersonMoviesModel(person);
}

TraktShowsModel *TraktPeople::getShows(TraktPerson *person)
{
    return new TraktPersonShowsModel(person);
}
