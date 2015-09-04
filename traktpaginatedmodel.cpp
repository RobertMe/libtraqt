#include "traktpaginatedmodel.h"

template<class T>
TraktPaginatedModel<T>::TraktPaginatedModel(TraktRequest *request, QObject *parent) :
    TraktModel<T>(parent),
    m_request(request),
    m_canFetchMore(false),
    m_currentPage(1)
{
    this->connect(request, &TraktRequest::replyReceived, this, &TraktPaginatedModel::onReplyReceived);
    m_request->setLimit(15);
    fetchMore(QModelIndex());
}

template<class T>
void TraktPaginatedModel<T>::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent)
    m_request->setPage(m_currentPage++);
    m_request->send();
    this->setLoading(true);
}

template<class T>
bool TraktPaginatedModel<T>::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_canFetchMore;
}

template<class T>
void TraktPaginatedModel<T>::reset()
{
    this->beginResetModel();
    this->m_items.clear();

    m_currentPage = 1;
    m_canFetchMore = true;

    this->endResetModel();
}

template<class T>
void TraktPaginatedModel<T>::onReplyReceived(TraktReply *reply)
{
    reply->request()->setParent(this);
    reply->deleteLater();

    QList<T> newItems;
    QVariantList items = reply->asList();
    foreach (QVariant item, items) {
        T convertedItem = this->convertItem(item.toMap());
        if (convertedItem) {
            newItems.append(convertedItem);
        }
    }

    this->beginInsertRows(QModelIndex(), this->m_items.size(), this->m_items.size() + newItems.size() - 1);
    this->m_items.append(newItems);
    m_canFetchMore = items.size() == 15;
    this->endInsertRows();

    this->setLoading(false);
    this->setLoaded(true);
}

template class TraktPaginatedModel<TraktItem*>;
template class TraktPaginatedModel<TraktMovie*>;
template class TraktPaginatedModel<TraktShow*>;
