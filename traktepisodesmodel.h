#ifndef TRAKTEPISODEMODEL_H
#define TRAKTEPISODEMODEL_H

#include "traktmodel.h"
#include "traktepisode.h"

class TraktEpisodesModel : public TraktModel<TraktEpisode*>
{
    Q_OBJECT
public:
    enum Roles {
        RoleTitle = Qt::DisplayRole,
        RoleIds = Qt::UserRole + 1,
        RoleNumber,
        RoleImages
    };

    explicit TraktEpisodesModel(TraktSeason *season, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    TraktEpisode *convertItem(const QVariantMap &item) Q_DECL_OVERRIDE;

    Q_INVOKABLE TraktEpisode *at(int i) const Q_DECL_OVERRIDE;

private:
    TraktSeason *m_season;

    TraktRequest *buildRequest(TraktSeason *season) const;
};

#endif // TRAKTEPISODEMODEL_H
