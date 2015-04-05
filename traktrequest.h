#ifndef TRAKTREQUEST_H
#define TRAKTREQUEST_H

#include <QObject>
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

    Q_INVOKABLE void send();

signals:
    void replyReceived(TraktReply *reply);

public slots:

private:
    TraktConnection *m_connection;
    QVariantMap m_data;
    Operation m_operation;
    QString m_path;
};

#endif // TRAKTREQUEST_H
