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
