#include "traktconnection.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QUrlQuery>

#include "traktauthenticator.h"
#include "traktrequest.h"
#include "traktreply.h"

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
    url.setQuery(traktRequest->query());

    QNetworkRequest request;
    request.setUrl(url);
    request.setOriginatingObject(traktRequest);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("trakt-api-version", "2");
    m_authenticator->appendHeaders(request);

    QJsonDocument jsonDoc = QJsonDocument::fromVariant(traktRequest->data());
    QNetworkReply *reply;
    if (traktRequest->operation() == TraktRequest::OperationPost) {
        reply = m_nam.post(request, jsonDoc.toJson());
    } else {
        reply = m_nam.get(request);
    }
    connect(reply, &QNetworkReply::finished, this, &TraktConnection::onReplyReceived);
}

void TraktConnection::setAuthenticator(TraktAuthenticator *authenticator)
{
    m_authenticator = authenticator;
}

void TraktConnection::onReplyReceived()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply)
        return;

    TraktRequest *request = qobject_cast<TraktRequest*>(reply->request().originatingObject());
    if (!request)
        return;

    emit request->replyReceived(new TraktReply(request, reply));
}
