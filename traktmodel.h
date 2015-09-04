#ifndef TRAKTMODEL_H
#define TRAKTMODEL_H

#include "traktmodelbase.h"
#include "traktrequest.h"
#include "traktreply.h"

class TraktItem;
class TraktMovie;
class TraktPerson;
class TraktShow;
class TraktSeason;
class TraktEpisode;

template<class T>
class TraktModel : public TraktModelBase
{
public:
    explicit TraktModel(TraktRequest *request, QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    TraktItem *get(int i) const Q_DECL_OVERRIDE;
    virtual T at(int i) const;

protected:
    explicit TraktModel(QObject *parent = 0);

    virtual T convertItem(const QVariantMap &item) = 0;

    QList<T> m_items;

protected slots:
    virtual void onReplyReceived(TraktReply *reply);
};

#endif // TRAKTMODEL_H
