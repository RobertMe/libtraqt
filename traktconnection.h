#ifndef TRAKTCONNECTION_H
#define TRAKTCONNECTION_H

#include <QObject>
#include <QNetworkAccessManager>

#include "traktauthenticator.h"

class TraktRequest;

class TraktConnection : public QObject
{
    Q_OBJECT
public:
    explicit TraktConnection(QObject *parent = 0);

    static TraktConnection *instance();

    void setAuthenticator(TraktAuthenticator *authenticator);

    void sendRequest(TraktRequest *request);

private:
    static TraktConnection *s_instance;

    TraktAuthenticator *m_authenticator;
    QNetworkAccessManager m_nam;
};

#endif // TRAKTCONNECTION_H
