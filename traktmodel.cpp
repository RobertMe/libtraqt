#include "traktmodel.h"

template<class T>
TraktModel<T>::TraktModel(TraktRequest *request, QObject *parent) :
    QAbstractItemModel(parent)
{
    connect(request, &TraktRequest::replyReceived, this, &TraktModel::onReplyReceived);
    request->send();
}

template<class T>
TraktModel<T>::TraktModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

template<class T>
QModelIndex TraktModel<T>::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return createIndex(row, column);
}

template<class T>
QModelIndex TraktModel<T>::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

template<class T>
int TraktModel<T>::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_items.size();
}

template<class T>
int TraktModel<T>::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

template<class T>
QObject *TraktModel<T>::get(int i) const
{
    return (QObject*)at(i);
}

template<class T>
T TraktModel<T>::at(int i) const
{
    if (i < 0 || i >= m_items.size()) {
        return 0;
    }

    return m_items.at(i);
}

template<class T>
void TraktModel<T>::onReplyReceived(TraktReply *reply)
{
    reply->deleteLater();

    QList<T> newItems;
    QVariantList items = reply->asList();
    foreach (QVariant item, items) {
        newItems.append(convertItem(item.toMap()));
    }

    beginResetModel();
    m_items = newItems;
    endResetModel();
}

template class TraktModel<TraktMovie*>;
template class TraktModel<TraktPerson*>;
template class TraktModel<TraktShow*>;
template class TraktModel<TraktSeason*>;
template class TraktModel<TraktEpisode*>;
