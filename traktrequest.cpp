#include "traktrequest.h"

#include "traktconnection.h"

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
    m_query.removeQueryItem("page");
    addQueryItem("page", QString::number(page));
}

void TraktRequest::setLimit(int limit)
{
    m_query.removeQueryItem("limit");
    addQueryItem("limit", QString::number(limit));
}

void TraktRequest::addQueryItem(const QString &key, const QString &value)
{
    m_query.addQueryItem(key, value);
}

QUrlQuery TraktRequest::query() const
{
    return m_query;
}

void TraktRequest::send()
{
    m_connection->sendRequest(this);
}
