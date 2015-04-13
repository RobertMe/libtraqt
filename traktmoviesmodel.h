#ifndef TRAKTMOVIESMODEL_H
#define TRAKTMOVIESMODEL_H

#include "traktpaginatedmodel.h"
#include "traktmovie.h"

class TraktMoviesModel : public TraktPaginatedModel<TraktMovie*>
{
    Q_OBJECT
public:
    enum Roles {
        RoleTitle = Qt::DisplayRole,
        RoleIds = Qt::UserRole + 1,
        RoleYear,
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
        RoleCertification,
        RoleImages
    };

    explicit TraktMoviesModel(TraktRequest *request, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    TraktMovie *convertItem(const QVariantMap &item);

    Q_INVOKABLE TraktMovie *at(int i) const;
};

#endif // TRAKTMOVIESMODEL_H
