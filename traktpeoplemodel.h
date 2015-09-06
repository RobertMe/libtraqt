#ifndef TRAKTPEOPLEMODEL_H
#define TRAKTPEOPLEMODEL_H

#include "traktmodel.h"
#include "traktperson.h"
#include "traktpeoplefiltermodel.h"

class TraktPeopleModel : public TraktModel<TraktPerson*>
{
    Q_OBJECT
    Q_PROPERTY(TraktPeopleFilterModel *cast READ cast CONSTANT)
    Q_PROPERTY(TraktPeopleFilterModel *crew READ crew CONSTANT)
public:
    enum Roles {
        RoleName = Qt::DisplayRole,
        RoleBiography  = TraktModel::RoleImage + 1,
        RoleBirthday,
        RoleDeath,
        RoleBirthplace,
        RoleHomepage
    };

    explicit TraktPeopleModel(TraktIds *ids, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    TraktPerson *convertItem(const QVariantMap &item) Q_DECL_OVERRIDE;

    Q_INVOKABLE TraktPerson *at(int i) const Q_DECL_OVERRIDE;

    TraktPeopleFilterModel *cast();
    TraktPeopleFilterModel *crew();

protected slots:
    virtual void onReplyReceived(TraktReply *reply) Q_DECL_OVERRIDE;

private:
    TraktRequest *buildRequest(TraktIds *ids) const;
    void addItems(QList<TraktPerson*> &list, const QVariantList &items, const QString &type);

    TraktPeopleFilterModel *m_cast;
    TraktPeopleFilterModel *m_crew;
};

#endif // TRAKTPEOPLEMODEL_H
