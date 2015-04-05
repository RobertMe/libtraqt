#ifndef TRAKTREPLY_H
#define TRAKTREPLY_H

#include <QObject>
#include <QNetworkReply>

#include "traktrequest.h"

class TraktReply : public QObject
{
    Q_OBJECT
public:
    explicit TraktReply(TraktRequest *request, QNetworkReply *reply, QObject *parent = 0);

    TraktRequest *request();

    QVariant value();
    QVariantMap asMap();
    QVariantList asList();

    int statusCode();

private:
    TraktRequest *m_request;
    QNetworkReply *m_reply;
    QVariant m_value;

    void parseReply();
};

#endif // TRAKTREPLY_H
