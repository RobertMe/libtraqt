#include "traktrequest.h"

#include "traktconnection.h"
#include "traktreply.h"

TraktRequest::TraktRequest(QObject *parent) :
    QObject(parent),
    m_connection(TraktConnection::instance()),
    m_operation(OperationGet)
{
}

TraktRequest::TraktRequest(TraktConnection *connection, QObject *parent) :
    QObject(parent),
    m_connection(connection)
{
}

QVariantMap TraktRequest::data() const
{
    return m_data;
}

void TraktRequest::setData(const QVariantMap &data)
{
    m_data = data;
}

TraktRequest::Operation TraktRequest::operation() const
{
    return m_operation;
}

void TraktRequest::setOperation(Operation operation)
{
    m_operation = operation;
}

QString TraktRequest::path() const
{
    return m_path;
}

void TraktRequest::setPath(const QString &path)
{
    m_path = path;
}

void TraktRequest::setPage(int page)
{
    replaceQueryItem("page", QString::number(page));
}

void TraktRequest::setLimit(int limit)
{
    replaceQueryItem("limit", QString::number(limit));
}

void TraktRequest::addQueryItem(const QString &key, const QString &value)
{
    m_query.addQueryItem(key, value);
}

void TraktRequest::replaceQueryItem(const QString &key, const QString &value)
{
    m_query.removeQueryItem(key);
    m_query.addQueryItem(key, value);
}

void TraktRequest::removeQueryItem(const QString &key)
{
    m_query.removeQueryItem(key);
}

QUrlQuery TraktRequest::query() const
{
    return m_query;
}


void TraktRequest::fire()
{
    connect(this, &TraktRequest::replyReceived, this, &TraktRequest::cleanup);
    m_connection->sendRequest(this);
}
void TraktRequest::send()
{
    m_connection->sendRequest(this);
}

void TraktRequest::cleanup(TraktReply *reply)
{
    reply->deleteLater();
}
