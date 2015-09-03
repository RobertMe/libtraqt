#include "traktpersonmoviesmodel.h"

#include "traktperson.h"

TraktPersonMoviesModel::TraktPersonMoviesModel(TraktPerson *person, QObject *parent) :
    TraktMoviesModel(buildRequest(person), parent)
{
}

TraktRequest *TraktPersonMoviesModel::buildRequest(TraktPerson *person)
{
    TraktRequest *request = new TraktRequest();
    request->setPath(QString("/people/%1/movies").arg(person->ids()->trakt()));
    request->addQueryItem("extended", "full,images");

    return request;
}

void TraktPersonMoviesModel::onReplyReceived(TraktReply *reply)
{
    reply->deleteLater();

    QVariantMap value = reply->asMap();
    QList<TraktMovie*> newItems;

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

void TraktPersonMoviesModel::addItems(QList<TraktMovie *> &list, const QVariantList &items)
{
    foreach (QVariant item, items) {
        QVariantMap map = item.toMap();
        list.append(convertItem(map));
    }
}
