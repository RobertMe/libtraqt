#ifndef TRAKTPAGINATEDMODEL_H
#define TRAKTPAGINATEDMODEL_H

#include <QAbstractItemModel>

#include "traktrequest.h"
#include "traktreply.h"

class TraktMovie;

template<class T>
class TraktPaginatedModel : public QAbstractItemModel
{
public:
    explicit TraktPaginatedModel(TraktRequest *request, QObject *parent = 0);

    void fetchMore(const QModelIndex &parent) Q_DECL_OVERRIDE;
    bool canFetchMore(const QModelIndex &parent) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    T at(int i) const;

protected:
    virtual T convertItem(const QVariantMap &item) = 0;

private:
    TraktRequest *m_request;
    bool m_canFetchMore;
    int m_currentPage;
    QList<T> m_items;

private slots:
    void onReplyReceived(TraktReply *reply);
};

#endif // TRAKTPAGINATEDMODEL_H
