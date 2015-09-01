#ifndef TRAKTPEOPLE_H
#define TRAKTPEOPLE_H

#include <QObject>
#include <QHash>

#include "traktpeoplemodel.h"
#include "traktpersonmoviesmodel.h"
#include "traktpersonshowsmodel.h"

class TraktIds;

class TraktPeople : public QObject
{
    Q_OBJECT
public:
    explicit TraktPeople(QObject *parent = 0);

    Q_INVOKABLE TraktPeopleModel *people(TraktIds *ids);

    Q_INVOKABLE TraktPersonMoviesModel *getMovies(TraktPerson *person);
    Q_INVOKABLE TraktPersonShowsModel *getShows(TraktPerson *person);

};

#endif // TRAKTPEOPLE_H
