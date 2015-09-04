#include "traktpeoplemodel.h"

TraktPeopleModel::TraktPeopleModel(TraktIds *ids, QObject *parent) :
    TraktModel(buildRequest(ids), parent),
    m_cast(0),
    m_crew(0)
{
}

TraktRequest *TraktPeopleModel::buildRequest(TraktIds *ids) const
{
    TraktRequest *request = new TraktRequest();
    request->setPath(QString("/%1/%2/people").arg(ids->type()).arg(ids->trakt()));
    request->addQueryItem("extended", "images");

    return request;
}

QVariant TraktPeopleModel::data(const QModelIndex &index, int role) const
{
    TraktPerson *person = at(index.row());

    if (!person) {
        return QVariant();
    }

    switch (role) {
    case RoleName:
        return person->name();
    case RoleIds:
    {
        QVariant var;
        var.setValue(person->ids());
        return var;
    }
    case RoleBiography:
        return person->biography();
    case RoleBirthday:
        return person->birthday();
    case RoleDeath:
        return person->death();
    case RoleBirthplace:
        return person->birthplace();
    case RoleHomepage:
        return person->homepage();
    case RoleImages:
    {
        QVariant var;
        var.setValue(person->images());
        return var;
    }
    }

    return QVariant();
}

QHash<int, QByteArray> TraktPeopleModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames.insert(RoleIds, "ids");
    roleNames.insert(RoleName, "name");
    roleNames.insert(RoleBiography, "biography");
    roleNames.insert(RoleBirthday, "birthday");
    roleNames.insert(RoleDeath, "death");
    roleNames.insert(RoleBirthplace, "birthplace");
    roleNames.insert(RoleHomepage, "homepage");
    roleNames.insert(RoleImages, "images");
    return roleNames;
}

TraktPerson *TraktPeopleModel::convertItem(const QVariantMap &item)
{
    return new TraktPerson(item.value("person").toMap(), this);
}

TraktPerson *TraktPeopleModel::at(int i) const
{
    return TraktModel::at(i);
}

TraktPeopleFilterModel *TraktPeopleModel::cast()
{
    if (!m_cast) {
        m_cast = new TraktPeopleFilterModel(this);
        m_cast->setSourceModel(this);
        m_cast->setTypeFilter("cast");
    }
    return m_cast;
}

TraktPeopleFilterModel *TraktPeopleModel::crew()
{
    if (!m_crew) {
        m_crew = new TraktPeopleFilterModel(this);
        m_crew->setSourceModel(this);
        m_crew->setTypeFilter("crew");
    }
    return m_crew;
}

void TraktPeopleModel::onReplyReceived(TraktReply *reply)
{
    reply->deleteLater();

    QVariantMap value = reply->asMap();
    QList<TraktPerson*> newItems;

    addItems(newItems, value.value("cast").toList(), "cast");

    QVariantMap crew = value.value("crew").toMap();
    foreach (QString type, crew.keys()) {
        addItems(newItems, crew.value(type).toList(), type);
    }

    beginResetModel();
    m_items.append(newItems);
    endResetModel();

    this->setLoading(false);
    this->setLoaded(true);
}

void TraktPeopleModel::addItems(QList<TraktPerson*> &list, const QVariantList &items, const QString &type)
{
    foreach (QVariant item, items) {
        QVariantMap map = item.toMap();
        TraktPerson *person = convertItem(map);
        person->setType(type);
        person->setCharacter(map.value("character").toString());
        person->setJob(map.value("job").toString());
        list.append(person);
    }
}
