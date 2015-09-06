#include "traktsearchmodel.h"

#include "traktitem.h"
#include "traktmovie.h"
#include "traktshow.h"
#include "traktepisode.h"
#include "traktperson.h"

TraktSearchModel::TraktSearchModel(QObject *parent) :
    TraktPaginatedModel(buildRequest(), parent),
    m_type(TypeMovie | TypeShow),
    m_year(0)
{
}

TraktRequest *TraktSearchModel::buildRequest() const
{
    TraktRequest *request = new TraktRequest();
    request->setPath("/search");
    request->addQueryItem("extended", "full,images");

    return request;
}

QString TraktSearchModel::query() const
{
    return m_query;
}

void TraktSearchModel::setQuery(const QString &query)
{
    if (m_query != query) {
        m_query = query;
        emit queryChanged();
        refresh();
    }
}

TraktSearchModel::Types TraktSearchModel::type() const
{
    return m_type;
}

void TraktSearchModel::setType(Types type)
{
    if (type == 0) {
        type = TypeMovie | TypeShow;
    }
    if (m_type != type) {
        m_type = type;
        emit typeChanged();
        refresh();
    }
}

int TraktSearchModel::year() const
{
    return m_year;
}

void TraktSearchModel::setYear(int year)
{
    if (m_year != year) {
        m_year = year;
        emit yearChanged();
        refresh();
    }
}

void TraktSearchModel::fetchMore(const QModelIndex &parent)
{
    if (!m_request->query().queryItemValue("query").isEmpty()) {
        TraktPaginatedModel<TraktItem*>::fetchMore(parent);
    }
}

TraktItem *TraktSearchModel::convertItem(const QVariantMap &item)
{
    QString type = item.value("type").toString();
    if (type == "movie") {
        return new TraktMovie(item.value("movie").toMap(), this);
    } else if (type == "show") {
        return new TraktShow(item.value("show").toMap(), this);
    } else if (type == "episode") {
        return new TraktEpisode(item.value("episode").toMap());
    } else if (type == "person") {
        return new TraktPerson(item.value("person").toMap(), this);
    }

    return 0;
}

TraktItem *TraktSearchModel::at(int i) const
{
    return TraktPaginatedModel::at(i);
}

void TraktSearchModel::refresh()
{
    if (!m_query.isEmpty()) {
        m_request->replaceQueryItem("query", m_query);

        if (m_year > 0) {
            m_request->replaceQueryItem("year", QString::number(m_year));
        } else {
            m_request->removeQueryItem("year");
        }

        QStringList types;
        if (type().testFlag(TypeMovie)) {
            types.append("movie");
        }
        if (type().testFlag(TypeShow)) {
            types.append("show");
        }
        if (type().testFlag(TypeEpisode)) {
            types.append("episode");
        }
        if (type().testFlag(TypePerson)) {
            types.append("person");
        }
        if (type().testFlag(TypeList)) {
            types.append("list");
        }
        m_request->replaceQueryItem("type", types.join(","));
    }

    reset();
}
