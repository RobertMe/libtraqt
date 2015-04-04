#ifndef TRAKTREQUEST_H
#define TRAKTREQUEST_H

#include <QObject>
#include <QVariantMap>

class TraktConnection;

class TraktRequest : public QObject
{
    Q_OBJECT
public:
    explicit TraktRequest(QObject *parent = 0);
    explicit TraktRequest(TraktConnection *connection, QObject *parent = 0);

    QVariantMap data() const;
    void setData(const QVariantMap &data);

    QString path() const;
    void setPath(const QString &path);

    Q_INVOKABLE void send();

signals:
    void replyReceived(const QVariantMap &data, int statusCode);

public slots:

private:
    TraktConnection *m_connection;
    QVariantMap m_data;
    QString m_path;
};

#endif // TRAKTREQUEST_H
