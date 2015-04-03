#include "traktauthenticator.h"

#include <QUrl>
#include <QUrlQuery>

#include "traktrequest.h"

TraktAuthenticator::TraktAuthenticator(const QString clientId, const QString &clientSecret, const QString &redirectUrl, QObject *parent) :
    QObject(parent),
    m_clientId(clientId),
    m_clientSecret(clientSecret),
    m_redirectUrl(redirectUrl)
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

void TraktAuthenticator::authorizeCode(const QString &code)
{
    QVariantMap data;
    data["code"] = code;
    data["client_id"] = m_clientId;
    data["client_secret"] = m_clientSecret;
    data["redirect_uri"] = m_redirectUrl;
    data["grant_type"] = "authorization_code";

    TraktRequest request;
    request.setPath("/oauth/token");
    request.setData(data);
    request.send();
}
