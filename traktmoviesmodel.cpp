#include "traktmoviesmodel.h"

TraktMoviesModel::TraktMoviesModel(TraktRequest *request, QObject *parent) :
    TraktPaginatedModel(request, parent)
{
}

QVariant TraktMoviesModel::data(const QModelIndex &index, int role) const
{
    TraktMovie *movie = at(index.row());

    if (!movie)
        return QVariant();

    switch (role) {
    case RoleYear:
        return movie->year();
    case RoleTagline:
        return movie->tagline();
    case RoleOverview:
        return movie->overview();
    case RoleReleased:
        return movie->released();
    case RoleRuntime:
        return movie->runtime();
    case RoleUpdatedAt:
        return movie->updatedAt();
    case RoleTrailer:
        return movie->trailer();
    case RoleHomepage:
        return movie->homepage();
    case RoleRating:
        return movie->rating();
    case RoleVotes:
        return movie->votes();
    case RoleLanguage:
        return movie->language();
    case RoleGenres:
        return movie->genres();
    case RoleCertification:
        return movie->certification();
    }

    return TraktPaginatedModel<TraktMovie*>::data(index, role);
}

QHash<int, QByteArray> TraktMoviesModel::roleNames() const
{
    QHash<int, QByteArray> roleNames = TraktPaginatedModel<TraktMovie*>::roleNames();
    roleNames.insert(RoleYear, "year");
    roleNames.insert(RoleTagline, "tagline");
    roleNames.insert(RoleOverview, "overview");
    roleNames.insert(RoleReleased, "released");
    roleNames.insert(RoleRuntime, "runtime");
    roleNames.insert(RoleUpdatedAt, "updatedAt");
    roleNames.insert(RoleTrailer, "trailer");
    roleNames.insert(RoleHomepage, "homepage");
    roleNames.insert(RoleRating, "rating");
    roleNames.insert(RoleVotes, "votes");
    roleNames.insert(RoleLanguage, "language");
    roleNames.insert(RoleGenres, "genres");
    roleNames.insert(RoleCertification, "certification");
    return roleNames;
}

TraktMovie *TraktMoviesModel::convertItem(const QVariantMap &item)
{
    if (item.contains("movie")) {
        return new TraktMovie(item.value("movie").toMap(), this);
    } else {
        return new TraktMovie(item, this);
    }
}

TraktMovie *TraktMoviesModel::at(int i) const
{
    return TraktPaginatedModel::at(i);
}
