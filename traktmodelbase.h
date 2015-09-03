#ifndef TRAKTMODELBASE_H
#define TRAKTMODELBASE_H

#include <QAbstractItemModel>

class TraktItem;

class TraktModelBase : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged)
public:
    explicit TraktModelBase(QObject *parent = 0);

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const Q_DECL_OVERRIDE;
    virtual QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;

    virtual int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    virtual TraktItem *get(int i) const = 0;

    bool loading() const;
    bool loaded() const;

signals:
    void loadingChanged();
    void loadedChanged();

protected:
    void setLoading(bool loading);
    void setLoaded(bool loaded);

private:
    bool m_loading;
    bool m_loaded;
};

#endif // TRAKTMODELBASE_H
