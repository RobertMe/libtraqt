#include "traktpaginatedmodel.h"

template<class T>
TraktPaginatedModel<T>::TraktPaginatedModel(TraktRequest *request, QObject *parent) :
    QAbstractItemModel(parent),
    m_request(request),
    m_canFetchMore(false),
    m_currentPage(1)
{
    connect(request, &TraktRequest::replyReceived, this, &TraktPaginatedModel::onReplyReceived);
    m_request->setLimit(15);
    fetchMore(QModelIndex());
}

template<class T>
void TraktPaginatedModel<T>::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent)
    m_request->setPage(m_currentPage++);
    m_request->send();
}

template<class T>
bool TraktPaginatedModel<T>::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_canFetchMore;
}

template<class T>
QModelIndex TraktPaginatedModel<T>::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return createIndex(row, column);
}

template<class T>
QModelIndex TraktPaginatedModel<T>::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

template<class T>
int TraktPaginatedModel<T>::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_items.size();
}

template<class T>
int TraktPaginatedModel<T>::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

template<class T>
T TraktPaginatedModel<T>::at(int i) const
{
    if (i < 0 || i >= m_items.size()) {
        return 0;
    }

    return m_items.at(i);
}

template<class T>
void TraktPaginatedModel<T>::onReplyReceived(TraktReply *reply)
{
    reply->request()->setParent(this);
    reply->deleteLater();

    QList<T> newItems;
    QVariantList items = reply->asList();
    foreach (QVariant item, items) {
        newItems.append(convertItem(item.toMap()));
    }

    beginInsertRows(QModelIndex(), m_items.size(), m_items.size() + newItems.size() - 1);
    m_items.append(newItems);
    m_canFetchMore = newItems.size() == 15;
    endInsertRows();
}

template class TraktPaginatedModel<TraktMovie*>;
