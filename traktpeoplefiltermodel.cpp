#include "traktpeoplefiltermodel.h"

#include "traktpeoplemodel.h"

TraktPeopleFilterModel::TraktPeopleFilterModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

void TraktPeopleFilterModel::setTypeFilter(const QString &type)
{
    m_typeFilter = type;
}

bool TraktPeopleFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    Q_UNUSED(source_parent)
    TraktPeopleModel *model = qobject_cast<TraktPeopleModel*>(sourceModel());
    if (!model) {
        return true;
    }

    TraktPerson *person = model->at(source_row);
    if (!person) {
        return true;
    }

    return m_typeFilter.isEmpty() || person->type() == m_typeFilter || (m_typeFilter == "crew" && person->type() != "cast");
}

TraktPerson *TraktPeopleFilterModel::at(int i) const
{
    TraktPeopleModel *model = qobject_cast<TraktPeopleModel*>(sourceModel());
    if (!model) {
        return 0;
    }

    int sourceIndex = mapToSource(index(i, 0, QModelIndex())).row();
    return model->at(sourceIndex);
}
