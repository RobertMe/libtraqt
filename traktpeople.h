#ifndef TRAKTPEOPLE_H
#define TRAKTPEOPLE_H

#include <QObject>
#include <QHash>

#include "traktpeoplemodel.h"

class TraktIds;

class TraktPeople : public QObject
{
    Q_OBJECT
public:
    explicit TraktPeople(QObject *parent = 0);

    Q_INVOKABLE TraktPeopleModel *people(TraktIds *ids);

};

#endif // TRAKTPEOPLE_H
