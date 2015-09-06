#ifndef TRAKTSEARCHMODEL_H
#define TRAKTSEARCHMODEL_H

#include "traktpaginatedmodel.h"

class TraktSearchModel : public TraktPaginatedModel<TraktItem*>
{
    Q_OBJECT
    Q_PROPERTY(QString query READ query WRITE setQuery NOTIFY queryChanged)
    Q_PROPERTY(Types type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(int year READ year WRITE setYear NOTIFY yearChanged)

    Q_FLAGS(Types)
    Q_ENUMS(Types)
public:
    enum Type {
        TypeMovie = 1,
        TypeShow = 2,
        TypeEpisode = 4,
        TypePerson = 8,
        TypeList = 16
    };
    Q_DECLARE_FLAGS(Types, Type)

    explicit TraktSearchModel(QObject *parent = 0);

    QString query() const;
    void setQuery(const QString &query);

    Types type() const;
    void setType(Types type);

    int year() const;
    void setYear(int year);

    virtual void fetchMore(const QModelIndex &parent) Q_DECL_OVERRIDE;

    TraktItem *convertItem(const QVariantMap &item) Q_DECL_OVERRIDE;

    Q_INVOKABLE TraktItem *at(int i) const Q_DECL_OVERRIDE;

signals:
    void queryChanged();
    void typeChanged();
    void yearChanged();

private:
    TraktRequest *buildRequest() const;

    void refresh();

    QString m_query;
    Types m_type;
    int m_year;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(TraktSearchModel::Types)

#endif // TRAKTSEARCHMODEL_H
