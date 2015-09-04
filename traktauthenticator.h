#ifndef TRAKTAUTHENTICATOR_H
#define TRAKTAUTHENTICATOR_H

#include <QObject>
#include <QNetworkRequest>

#include "traktreply.h"

class TraktAuthenticator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool authorized READ authorized NOTIFY authorizedChanged)
    Q_PROPERTY(bool authorizing READ authorizing NOTIFY authorizingChanged)

    Q_ENUMS(GrantType)
public:
    enum GrantType {
        GrantAccessCode,
        GrantRefreshToken
    };

    explicit TraktAuthenticator(const QString clientId, const QString &clientSecret, const QString &redirectUrl, QObject *parent = 0);

    Q_INVOKABLE QString buildAuthorizeUrl() const;
    Q_INVOKABLE void authorize(GrantType type, const QString &token);

    void appendHeaders(QNetworkRequest &request) const;

    bool authorized() const;
    bool authorizing() const;

signals:
    void tokensReceived(const QString &refreshToken);
    void authorizedChanged();
    void authorizingChanged();

private:
    QString m_clientId;
    QString m_clientSecret;
    QString m_redirectUrl;
    QString m_accessToken;
    bool m_authorized;
    bool m_authorizing;

private slots:
    void onTokenReceived(TraktReply *reply);
};

#endif // TRAKTAUTHENTICATOR_H
