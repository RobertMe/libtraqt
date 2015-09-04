#ifndef TRAKTSEASONSMODEL_H
#define TRAKTSEASONSMODEL_H

#include "traktmodel.h"
#include "traktseason.h"

class TraktSeasonsModel : public TraktModel<TraktSeason*>
{
    Q_OBJECT
public:
    enum Roles {
        RoleNumber = Qt::DisplayRole,
        RoleIds = Qt::UserRole + 1,
        RoleRating,
        RoleVotes,
        RoleEpisodeCount,
        RoleAiredEpisodes,
        RoleOverview,
        RoleImages
    };

    explicit TraktSeasonsModel(TraktShow *show, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    TraktSeason *convertItem(const QVariantMap &item) Q_DECL_OVERRIDE;

    Q_INVOKABLE TraktSeason *at(int i) const Q_DECL_OVERRIDE;

private:
    TraktShow *m_show;

    TraktRequest *buildRequest(TraktShow *show) const;
};

#endif // TRAKTSEASONSMODEL_H
