#ifndef TRAKTREPLY_H
#define TRAKTREPLY_H

#include <QObject>
#include <QNetworkReply>

class TraktRequest;

class TraktReply : public QObject
{
    Q_OBJECT
public:
    explicit TraktReply(TraktRequest *request, QNetworkReply *reply, QObject *parent = 0);

    TraktRequest *request() const;

    QVariant value() const;
    QVariantMap asMap() const;
    QVariantList asList() const;
    bool isValid() const;

    int statusCode() const;
    QByteArray header(const QByteArray &headerName) const;

private:
    TraktRequest *m_request;
    QNetworkReply *m_reply;
    QVariant m_value;

    void parseReply();
};

#endif // TRAKTREPLY_H
