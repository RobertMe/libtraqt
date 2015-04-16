#ifndef TRAKTPEOPLEFILTERMODEL_H
#define TRAKTPEOPLEFILTERMODEL_H

#include <QSortFilterProxyModel>

class TraktPeopleFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TraktPeopleFilterModel(QObject *parent = 0);

    void setTypeFilter(const QString &type);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const Q_DECL_OVERRIDE;

private:
    QString m_typeFilter;
};

#endif // TRAKTPEOPLEFILTERMODEL_H
