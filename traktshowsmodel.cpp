#include "traktshowsmodel.h"

TraktShowsModel::TraktShowsModel(TraktRequest *request, QObject *parent) :
    TraktPaginatedModel(request, parent)
{
}

QVariant TraktShowsModel::data(const QModelIndex &index, int role) const
{
    TraktShow *show = at(index.row());

    if (!show)
        return QVariant();

    switch (role) {
    case RoleYear:
        return show->year();
    case RoleOverview:
        return show->overview();
    case RoleFirstAired:
        return show->firstAired();
    case RoleRuntime:
        return show->runtime();
    case RoleCertification:
        return show->certification();
    case RoleNetwork:
        return show->network();
    case RoleCountry:
        return show->country();
    case RoleUpdatedAt:
        return show->updatedAt();
    case RoleTrailer:
        return show->trailer();
    case RoleHomepage:
        return show->homepage();
    case RoleStatus:
        return show->status();
    case RoleRating:
        return show->rating();
    case RoleVotes:
        return show->votes();
    case RoleLanguage:
        return show->language();
    case RoleAvailableTranslations:
        return show->availableTranslations();
    case RoleGenres:
        return show->genres();
    case RoleAiredEpisodes:
        return show->airedEpisodes();
    }

    return TraktPaginatedModel<TraktShow*>::data(index, role);
}

QHash<int, QByteArray> TraktShowsModel::roleNames() const
{
    QHash<int, QByteArray> roleNames = TraktPaginatedModel::roleNames();
    roleNames.insert(RoleYear, "year");
    roleNames.insert(RoleOverview, "overview");
    roleNames.insert(RoleFirstAired, "firstAired");
    roleNames.insert(RoleRuntime, "runtime");
    roleNames.insert(RoleCertification, "certification");
    roleNames.insert(RoleNetwork, "network");
    roleNames.insert(RoleCountry, "country");
    roleNames.insert(RoleUpdatedAt, "updatedAt");
    roleNames.insert(RoleTrailer, "trailer");
    roleNames.insert(RoleHomepage, "homepage");
    roleNames.insert(RoleStatus, "status");
    roleNames.insert(RoleRating, "rating");
    roleNames.insert(RoleVotes, "votes");
    roleNames.insert(RoleLanguage, "language");
    roleNames.insert(RoleAvailableTranslations, "availableTranslations");
    roleNames.insert(RoleGenres, "genres");
    roleNames.insert(RoleAiredEpisodes, "airedEpisodes");
    return roleNames;
}

TraktShow *TraktShowsModel::convertItem(const QVariantMap &item)
{
    if (item.contains("show")) {
        return new TraktShow(item.value("show").toMap(), this);
    } else {
        return new TraktShow(item, this);
    }
}

TraktShow *TraktShowsModel::at(int i) const
{
    return TraktPaginatedModel::at(i);
}
