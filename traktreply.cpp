#include "traktreply.h"

#include <QJsonDocument>

#include "traktrequest.h"

TraktReply::TraktReply(TraktRequest *request, QNetworkReply *reply, QObject *parent) :
    QObject(parent),
    m_request(request),
    m_reply(reply)
{
    request->setParent(this);
    reply->setParent(this);
    parseReply();
}

TraktRequest *TraktReply::request() const
{
    return m_request;
}

QVariant TraktReply::value() const
{
    return m_value;
}

QVariantMap TraktReply::asMap() const
{
    return m_value.toMap();
}

QVariantList TraktReply::asList() const
{
    return m_value.toList();
}

bool TraktReply::isValid() const
{
    return m_value.isValid();
}

int TraktReply::statusCode() const
{
    return m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
}

QByteArray TraktReply::header(const QByteArray &headerName) const
{
    return m_reply->rawHeader(headerName);
}

void TraktReply::parseReply()
{
    QByteArray data = m_reply->readAll();
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "JSON parse error:" << error.errorString() << "data: " << data;
        return;
    }

    m_value = jsonDoc.toVariant();
}
