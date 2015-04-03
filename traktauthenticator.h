#ifndef TRAKTAUTHENTICATOR_H
#define TRAKTAUTHENTICATOR_H

#include <QObject>

class TraktAuthenticator : public QObject
{
    Q_OBJECT
public:
    explicit TraktAuthenticator(const QString clientId, const QString &clientSecret, const QString &redirectUrl, QObject *parent = 0);

    Q_INVOKABLE QString buildAuthorizeUrl() const;
    Q_INVOKABLE void authorizeCode(const QString &code);

signals:

public slots:

private:
    QString m_clientId;
    QString m_clientSecret;
    QString m_redirectUrl;
};

#endif // TRAKTAUTHENTICATOR_H
