#include "traktseasonsmodel.h"

#include "traktshow.h"

TraktSeasonsModel::TraktSeasonsModel(TraktShow *show, QObject *parent) :
    TraktModel(buildRequest(show), parent),
    m_show(show)
{
}

TraktRequest *TraktSeasonsModel::buildRequest(TraktShow *show) const
{
    TraktRequest *request = new TraktRequest();
    request->setPath(QString("/shows/%1/seasons").arg(show->ids()->trakt()));
    request->addQueryItem("extended", "full,images");

    return request;
}

QVariant TraktSeasonsModel::data(const QModelIndex &index, int role) const
{
    TraktSeason *season = at(index.row());

    if (!season) {
        return QVariant();
    }

    switch (role) {
    case RoleNumber:
        return season->number();
    case RoleRating:
        return season->rating();
    case RoleVotes:
        return season->votes();
    case RoleEpisodeCount:
        return season->episodeCount();
    case RoleAiredEpisodes:
        return season->airedEpisodes();
    }

    return TraktModel<TraktSeason*>::data(index, role);
}

QHash<int, QByteArray> TraktSeasonsModel::roleNames() const
{
    QHash<int, QByteArray> roleNames = TraktModel<TraktSeason*>::roleNames();
    roleNames.insert(RoleNumber, "number");
    roleNames.insert(RoleRating, "rating");
    roleNames.insert(RoleVotes, "votes");
    roleNames.insert(RoleEpisodeCount, "episodeCount");
    roleNames.insert(RoleAiredEpisodes, "airedEpisodes");
    return roleNames;
}

TraktSeason *TraktSeasonsModel::convertItem(const QVariantMap &item)
{
    TraktSeason *season = new TraktSeason(item, m_show);
    season->parse(item);
    return season;
}

TraktSeason *TraktSeasonsModel::at(int i) const
{
    return TraktModel::at(i);
}
