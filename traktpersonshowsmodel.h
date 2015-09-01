#ifndef TRAKTPERSONSHOWSMODEL_H
#define TRAKTPERSONSHOWSMODEL_H

#include "traktshowsmodel.h"

class TraktPersonShowsModel : public TraktShowsModel
{
    Q_OBJECT
public:
    explicit TraktPersonShowsModel(TraktPerson *person, QObject *parent = 0);

protected slots:
    virtual void onReplyReceived(TraktReply *reply) Q_DECL_OVERRIDE;

private:
    void addItems(QList<TraktShow*> &list, const QVariantList &items);

    TraktRequest *buildRequest(TraktPerson *person);
};

#endif // TRAKTPERSONSHOWSMODEL_H
