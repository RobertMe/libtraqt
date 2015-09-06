#ifndef TRAKTMOVIESMODEL_H
#define TRAKTMOVIESMODEL_H

#include "traktpaginatedmodel.h"
#include "traktmovie.h"

class TraktMoviesModel : public TraktPaginatedModel<TraktMovie*>
{
    Q_OBJECT
public:
    enum Roles {
        RoleYear = TraktModel::RoleImage + 1,
        RoleTagline,
        RoleOverview,
        RoleReleased,
        RoleRuntime,
        RoleUpdatedAt,
        RoleTrailer,
        RoleHomepage,
        RoleRating,
        RoleVotes,
        RoleLanguage,
        RoleGenres,
        RoleCertification
    };

    explicit TraktMoviesModel(TraktRequest *request, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    TraktMovie *convertItem(const QVariantMap &item) Q_DECL_OVERRIDE;

    Q_INVOKABLE TraktMovie *at(int i) const;
};

#endif // TRAKTMOVIESMODEL_H
