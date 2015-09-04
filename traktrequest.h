#ifndef TRAKTREQUEST_H
#define TRAKTREQUEST_H

#include <QObject>
#include <QUrlQuery>
#include <QVariantMap>

class TraktConnection;
class TraktReply;

class TraktRequest : public QObject
{
    Q_OBJECT
public:
    enum Operation {
        OperationGet,
        OperationPost
    };

    explicit TraktRequest(QObject *parent = 0);
    explicit TraktRequest(TraktConnection *connection, QObject *parent = 0);

    QVariantMap data() const;
    void setData(const QVariantMap &data);

    Operation operation() const;
    void setOperation(Operation operation);

    QString path() const;
    void setPath(const QString &path);

    void setPage(int page);

    void setLimit(int limit);

    void addQueryItem(const QString &key, const QString &value);
    void replaceQueryItem(const QString &key, const QString &value);
    void removeQueryItem(const QString &key);
    QUrlQuery query() const;

    Q_INVOKABLE void fire();
    Q_INVOKABLE void send();

signals:
    void replyReceived(TraktReply *reply);

private:
    TraktConnection *m_connection;
    QVariantMap m_data;
    Operation m_operation;
    QString m_path;
    QUrlQuery m_query;

private slots:
    void cleanup(TraktReply *reply);
};

#endif // TRAKTREQUEST_H
