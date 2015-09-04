#ifndef TRAKTPEOPLE_H
#define TRAKTPEOPLE_H

#include <QObject>

class TraktPerson;
class TraktPeopleModel;
class TraktMoviesModel;
class TraktShowsModel;

class TraktIds;

class TraktPeople : public QObject
{
    Q_OBJECT
public:
    explicit TraktPeople(QObject *parent = 0);

    Q_INVOKABLE TraktPeopleModel *people(TraktIds *ids);

    Q_INVOKABLE TraktMoviesModel *getMovies(TraktPerson *person);
    Q_INVOKABLE TraktShowsModel *getShows(TraktPerson *person);

};

#endif // TRAKTPEOPLE_H
