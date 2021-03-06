#include "traktmodel.h"

#include "traktitem.h"

template<class T>
TraktModel<T>::TraktModel(TraktRequest *request, QObject *parent) :
    TraktModel(parent)
{
    connect(request, &TraktRequest::replyReceived, this, &TraktModel::onReplyReceived);
    request->send();
    setLoading(true);
}

template<class T>
TraktModel<T>::TraktModel(QObject *parent) :
    TraktModelBase(parent)
{
}

template<class T>
int TraktModel<T>::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_items.size();
}

template<class T>
QVariant TraktModel<T>::data(const QModelIndex &index, int role) const
{
    TraktItem *item = get(index.row());

    if (!item)
        return QVariant();

    switch (role) {
    case RoleTitle:
        return item->title();
    case RoleIds:
    {
        QVariant var;
        var.setValue(item->ids());
        return var;
    }
    case RoleImages:
    {
        QVariant var;
        var.setValue(item->images());
        return var;
    }
    case RoleImage:
    {
        QVariant var;
        var.setValue(item->image());
        return var;
    }
    }

    return QVariant();
}

template<class T>
QHash<int, QByteArray> TraktModel<T>::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames.insert(RoleIds, "ids");
    roleNames.insert(RoleTitle, "title");
    roleNames.insert(RoleImages, "images");
    roleNames.insert(RoleImage, "image");
    return roleNames;
}

template<class T>
TraktItem *TraktModel<T>::get(int i) const
{
    return (TraktItem*)at(i);
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

    setLoading(false);
    setLoaded(true);
}

template class TraktModel<TraktItem*>;
template class TraktModel<TraktMovie*>;
template class TraktModel<TraktPerson*>;
template class TraktModel<TraktShow*>;
template class TraktModel<TraktSeason*>;
template class TraktModel<TraktEpisode*>;
