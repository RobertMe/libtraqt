#ifndef TRAKTPERSONMOVIESMODEL_H
#define TRAKTPERSONMOVIESMODEL_H

#include "traktmoviesmodel.h"

class TraktPersonMoviesModel : public TraktMoviesModel
{
    Q_OBJECT
public:
    explicit TraktPersonMoviesModel(TraktPerson *person, QObject *parent = 0);

protected slots:
    virtual void onReplyReceived(TraktReply *reply) Q_DECL_OVERRIDE;

private:
    void addItems(QList<TraktMovie*> &list, const QVariantList &items);

    TraktRequest *buildRequest(TraktPerson *person) const;
};

#endif // TRAKTPERSONMOVIESMODEL_H
