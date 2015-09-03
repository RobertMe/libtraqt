#include "traktpersonshowsmodel.h"

#include "traktperson.h"

TraktPersonShowsModel::TraktPersonShowsModel(TraktPerson *person, QObject *parent) :
    TraktShowsModel(buildRequest(person), parent)
{
}

TraktRequest *TraktPersonShowsModel::buildRequest(TraktPerson *person)
{
    TraktRequest *request = new TraktRequest();
    request->setPath(QString("/people/%1/shows").arg(person->ids()->trakt()));
    request->addQueryItem("extended", "full,images");

    return request;
}

void TraktPersonShowsModel::onReplyReceived(TraktReply *reply)
{
    reply->deleteLater();

    QVariantMap value = reply->asMap();
    QList<TraktShow*> newItems;

    addItems(newItems, value.value("cast").toList());

    QVariantMap crew = value.value("crew").toMap();
    foreach (QString type, crew.keys()) {
        addItems(newItems, crew.value(type).toList());
    }

    beginResetModel();
    m_items.append(newItems);
    endResetModel();

    this->setLoading(false);
    this->setLoaded(true);
}

void TraktPersonShowsModel::addItems(QList<TraktShow*> &list, const QVariantList &items)
{
    foreach (QVariant item, items) {
        QVariantMap map = item.toMap();
        list.append(convertItem(map));
    }
}
