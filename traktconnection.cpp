#include "traktconnection.h"

#include <QNetworkRequest>
#include <QJsonDocument>

#include "traktrequest.h"

TraktConnection *TraktConnection::s_instance = 0;

TraktConnection::TraktConnection(QObject *parent) :
    QObject(parent)
{
}

TraktConnection *TraktConnection::instance()
{
    if (!s_instance) {
        s_instance = new TraktConnection();
    }

    return s_instance;
}

void TraktConnection::sendRequest(TraktRequest *traktRequest)
{
    QUrl url(TRAKT_API_URL);
    url.setPath(traktRequest->path());

    QNetworkRequest request;
    request.setUrl(url);
    request.setOriginatingObject(traktRequest);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonDocument jsonDoc = QJsonDocument::fromVariant(traktRequest->data());
    m_nam.post(request, jsonDoc.toJson());
}

void TraktConnection::setAuthenticator(TraktAuthenticator *authenticator)
{
    m_authenticator = authenticator;
}
