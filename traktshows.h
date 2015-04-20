#ifndef TRAKTSHOWS_H
#define TRAKTSHOWS_H

#include <QObject>

#include "traktshowsmodel.h"

class TraktShows : public QObject
{
    Q_OBJECT
public:
    explicit TraktShows(QObject *parent = 0);

    Q_INVOKABLE TraktShowsModel *popular();
    Q_INVOKABLE TraktShowsModel *trending();
};

#endif // TRAKTSHOWS_H
