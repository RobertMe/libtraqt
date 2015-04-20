#ifndef TRAKTMODEL_H
#define TRAKTMODEL_H

#include <QAbstractItemModel>

#include "traktrequest.h"
#include "traktreply.h"

class TraktMovie;
class TraktPerson;
class TraktShow;

template<class T>
class TraktModel : public QAbstractItemModel
{
public:
    explicit TraktModel(TraktRequest *request, QObject *parent = 0);

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const Q_DECL_OVERRIDE;
    virtual QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;

    virtual int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    virtual int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    T at(int i) const;

protected:
    explicit TraktModel(QObject *parent = 0);

    virtual T convertItem(const QVariantMap &item) = 0;

    QList<T> m_items;

protected slots:
    virtual void onReplyReceived(TraktReply *reply);
};

#endif // TRAKTMODEL_H
