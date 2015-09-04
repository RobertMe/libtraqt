#ifndef TRAKTMOVIES_H
#define TRAKTMOVIES_H

#include <QObject>

class TraktMoviesModel;

class TraktMovies : public QObject
{
    Q_OBJECT
public:
    explicit TraktMovies(QObject *parent = 0);

    Q_INVOKABLE TraktMoviesModel *popular();
    Q_INVOKABLE TraktMoviesModel *trending();
};

#endif // TRAKTMOVIES_H
