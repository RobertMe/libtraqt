#include "traktpaginatedmodel.h"

template<class T>
TraktPaginatedModel<T>::TraktPaginatedModel(TraktRequest *request, QObject *parent) :
    TraktModel<T>(parent),
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
void TraktPaginatedModel<T>::onReplyReceived(TraktReply *reply)
{
    reply->request()->setParent(this);
    reply->deleteLater();

    QList<T> newItems;
    QVariantList items = reply->asList();
    foreach (QVariant item, items) {
        newItems.append(this->convertItem(item.toMap()));
    }

    beginInsertRows(QModelIndex(), this->m_items.size(), this->m_items.size() + newItems.size() - 1);
    this->m_items.append(newItems);
    m_canFetchMore = newItems.size() == 15;
    this->endInsertRows();
}

template class TraktPaginatedModel<TraktMovie*>;
template class TraktPaginatedModel<TraktShow*>;
