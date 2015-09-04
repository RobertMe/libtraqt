#include "traktauthenticator.h"

#include <QDateTime>
#include <QDebug>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QVariant>

#include "traktrequest.h"

TraktAuthenticator::TraktAuthenticator(const QString clientId, const QString &clientSecret, const QString &redirectUrl, QObject *parent) :
    QObject(parent),
    m_clientId(clientId),
    m_clientSecret(clientSecret),
    m_redirectUrl(redirectUrl),
    m_authorized(false),
    m_authorizing(false)
{
}

QString TraktAuthenticator::buildAuthorizeUrl() const
{
    QUrlQuery query;
    query.addQueryItem("response_type", "code");
    query.addQueryItem("client_id", m_clientId);
    query.addQueryItem("redirect_uri", m_redirectUrl);
    QUrl url(TRAKT_WEB_URL);
    url.setPath("/oauth/authorize");
    url.setQuery(query);

    return url.toString();
}

void TraktAuthenticator::authorize(GrantType type, const QString &token)
{
    if (token.isEmpty()) {
        return;
    }

    QVariantMap data;
    data["client_id"] = m_clientId;
    data["client_secret"] = m_clientSecret;
    data["redirect_uri"] = m_redirectUrl;

    if (type == GrantAccessCode) {
        data["code"] = token;
        data["grant_type"] = "authorization_code";
    } else if (type == GrantRefreshToken) {
        data["refresh_token"] = token;
        data["grant_type"] = "refresh_token";
    }

    TraktRequest *request = new TraktRequest(this);
    request->setOperation(TraktRequest::OperationPost);
    request->setPath("/oauth/token");
    request->setData(data);
    request->send();

    connect(request, &TraktRequest::replyReceived, this, &TraktAuthenticator::onTokenReceived);

    m_authorizing = true;
    emit authorizingChanged();
}

bool TraktAuthenticator::authorized() const
{
    return m_authorized;
}

bool TraktAuthenticator::authorizing() const
{
    return m_authorizing;
}

void TraktAuthenticator::appendHeaders(QNetworkRequest &request) const
{
    request.setRawHeader("trakt-api-key", m_clientId.toLocal8Bit());
    if (!m_accessToken.isEmpty()) {
        request.setRawHeader("Authorization", QString("Bearer %1").arg(m_accessToken).toLocal8Bit());
    }
}

void TraktAuthenticator::onTokenReceived(TraktReply *reply)
{
    reply->deleteLater();

    QVariantMap data = reply->asMap();
    if (reply->statusCode() != 200) {
        qDebug() << "authorization failed" << data.value("error_description").toString();
        if (m_authorized) {
            m_authorized = false;
            emit authorizedChanged();
        }
        return;
    }

    m_accessToken = data.value("access_token").toString();

    emit tokensReceived(data.value("refresh_token").toString());

    if (!m_authorized) {
        m_authorized = true;
        emit authorizedChanged();
    }

    if (m_authorizing) {
        m_authorizing = false;
        emit authorizingChanged();
    }
}
