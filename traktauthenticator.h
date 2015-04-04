#ifndef TRAKTAUTHENTICATOR_H
#define TRAKTAUTHENTICATOR_H

#include <QObject>
#include <QNetworkRequest>

class TraktAuthenticator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool authorized READ authorized NOTIFY authorizedChanged)

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

signals:
    void tokensReceived(const QString &refreshToken);
    void authorizedChanged();

private:
    QString m_clientId;
    QString m_clientSecret;
    QString m_redirectUrl;
    QString m_accessToken;
    bool m_authorized;

private slots:
    void onTokenReceived(const QVariantMap &data, int statusCode);
};

#endif // TRAKTAUTHENTICATOR_H
