#ifndef TRAKTPAGINATEDMODEL_H
#define TRAKTPAGINATEDMODEL_H

#include "traktmodel.h"

template<class T>
class TraktPaginatedModel : public TraktModel<T>
{
public:
    explicit TraktPaginatedModel(TraktRequest *request, QObject *parent = 0, bool sendRequest = true);

    virtual void fetchMore(const QModelIndex &parent) Q_DECL_OVERRIDE;
    bool canFetchMore(const QModelIndex &parent) const Q_DECL_OVERRIDE;

protected:
    void reset();

    TraktRequest *m_request;

private:
    bool m_canFetchMore;
    int m_currentPage;

protected slots:
    virtual void onReplyReceived(TraktReply *reply) Q_DECL_OVERRIDE;
};

#endif // TRAKTPAGINATEDMODEL_H
