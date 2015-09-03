#include "traktmodelbase.h"

#include <QTimer>
#include <QDebug>

TraktModelBase::TraktModelBase(QObject *parent) :
    QAbstractItemModel(parent),
    m_loading(false),
    m_loaded(false)
{
}

bool TraktModelBase::loading() const
{
    return m_loading;
}

bool TraktModelBase::loaded() const
{
    return m_loaded;
}

void TraktModelBase::setLoading(bool loading)
{
    if (m_loading != loading) {
        m_loading = loading;
        emit loadingChanged();
    }
}

void TraktModelBase::setLoaded(bool loaded)
{
    if (m_loaded != loaded) {
        m_loaded = loaded;
        emit loadedChanged();
    }
}

QModelIndex TraktModelBase::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return createIndex(row, column);
}

QModelIndex TraktModelBase::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

int TraktModelBase::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}
