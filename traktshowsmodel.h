#ifndef TRAKTSHOWSMODEL_H
#define TRAKTSHOWSMODEL_H

#include "traktpaginatedmodel.h"
#include "traktshow.h"

class TraktShowsModel : public TraktPaginatedModel<TraktShow*>
{
    Q_OBJECT
public:
    enum Roles {
        RoleTitle = Qt::DisplayRole,
        RoleIds = Qt::UserRole + 1,
        RoleYear,
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
        RoleAiredEpisodes,
        RoleImages
    };

    explicit TraktShowsModel(TraktRequest *request, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    TraktShow *convertItem(const QVariantMap &item);

    Q_INVOKABLE TraktShow *at(int i) const;

};

#endif // TRAKTSHOWSMODEL_H
