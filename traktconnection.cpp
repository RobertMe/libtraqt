#include "traktconnection.h"

#include <QNetworkRequest>
#include <QNetworkReply>
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
    request.setRawHeader("trakt-api-version", "2");
    m_authenticator->appendHeaders(request);

    QJsonDocument jsonDoc = QJsonDocument::fromVariant(traktRequest->data());
    QNetworkReply *reply = m_nam.post(request, jsonDoc.toJson());
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

    reply->deleteLater();

    QByteArray data = reply->readAll();
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "JSON parse error:" << error.errorString() << "data: " << data;
        return;
    }

    TraktRequest *request = qobject_cast<TraktRequest*>(reply->request().originatingObject());
    if (!request)
        return;

    request->deleteLater();
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    emit request->replyReceived(jsonDoc.toVariant().toMap(), statusCode);
}
