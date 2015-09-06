#include "traktepisodesmodel.h"

#include "traktseason.h"
#include "traktshow.h"

TraktEpisodesModel::TraktEpisodesModel(TraktSeason *season, QObject *parent) :
    TraktModel(buildRequest(season), parent),
    m_season(season)
{
}

TraktRequest *TraktEpisodesModel::buildRequest(TraktSeason *season) const
{
    TraktRequest *request = new TraktRequest();
    request->setPath(QString("/shows/%1/seasons/%2").arg(season->show()->ids()->trakt()).arg(season->number()));
    request->addQueryItem("extended", "full,images");

    return request;
}

QVariant TraktEpisodesModel::data(const QModelIndex &index, int role) const
{
    TraktEpisode *episode = at(index.row());

    if (!episode) {
        return QVariant();
    }

    switch (role) {
    case RoleTitle:
        return episode->title();
    case RoleIds:
    {
        QVariant var;
        var.setValue(episode->ids());
        return var;
    }
    case RoleNumber:
        return episode->number();
    case RoleImages:
    {
        QVariant var;
        var.setValue(episode->images());
        return var;
    }
    }

    return TraktModel<TraktEpisode*>::data(index, role);
}

QHash<int, QByteArray> TraktEpisodesModel::roleNames() const
{
    QHash<int, QByteArray> roleNames = TraktModel<TraktEpisode*>::roleNames();
    roleNames.insert(RoleNumber, "number");
    return roleNames;
}

TraktEpisode *TraktEpisodesModel::convertItem(const QVariantMap &item)
{
    return new TraktEpisode(item, m_season);
}

TraktEpisode *TraktEpisodesModel::at(int i) const
{
    return TraktModel::at(i);
}
