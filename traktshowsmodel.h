#ifndef TRAKTSHOWSMODEL_H
#define TRAKTSHOWSMODEL_H

#include "traktpaginatedmodel.h"
#include "traktshow.h"

class TraktShowsModel : public TraktPaginatedModel<TraktShow*>
{
    Q_OBJECT
public:
    enum Roles {
        RoleYear = TraktModel::RoleImage + 1,
        RoleOverview,
        RoleFirstAired,
        RoleRuntime,
        RoleCertification,
        RoleNetwork,
        RoleCountry,
        RoleUpdatedAt,
        RoleTrailer,
        RoleHomepage,
        RoleStatus,
        RoleRating,
        RoleVotes,
        RoleLanguage,
        RoleAvailableTranslations,
        RoleGenres,
        RoleAiredEpisodes
    };

    explicit TraktShowsModel(TraktRequest *request, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    TraktShow *convertItem(const QVariantMap &item) Q_DECL_OVERRIDE;

    Q_INVOKABLE TraktShow *at(int i) const Q_DECL_OVERRIDE;

};

#endif // TRAKTSHOWSMODEL_H
