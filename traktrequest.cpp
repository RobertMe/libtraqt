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

void TraktRequest::send()
{
    m_connection->sendRequest(this);
}
