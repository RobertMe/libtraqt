#include "traktperson.h"

#include <QVariantMap>

#include "traktrequest.h"
#include "traktreply.h"

TraktPerson::TraktPerson(QObject *parent) :
    TraktItem(parent)
{
}

TraktPerson::TraktPerson(const QVariantMap &data, QObject *parent) :
    TraktItem(parent)
{
    m_ids = new TraktIds(data.value("ids").toMap(), "people", this);
    m_name = data.value("name").toString();
    m_images = new TraktImageSet(data.value("images").toMap(), this);
}

QString TraktPerson::name() const
{
    return m_name;
}

void TraktPerson::setName(const QString &name)
{
    m_name = name;
    emit nameChanged();
    emit titleChanged();
}

QString TraktPerson::biography() const
{
    return m_biography;
}

void TraktPerson::setBiography(const QString &biography)
{
    m_biography = biography;
    emit biographyChanged();
}

QDate TraktPerson::birthday() const
{
    return m_birthday;
}

void TraktPerson::setBirthday(const QDate &birthday)
{
    m_birthday = birthday;
    emit birthdayChanged();
}

QDate TraktPerson::death() const
{
    return m_death;
}

void TraktPerson::setDeath(const QDate &death)
{
    m_death = death;
    emit deathChanged();
}

QString TraktPerson::birthplace() const
{
    return m_birthplace;
}

void TraktPerson::setBirthplace(const QString &birthplace)
{
    m_birthplace = birthplace;
    emit birthplaceChanged();
}

QString TraktPerson::homepage() const
{
    return m_homepage;
}

void TraktPerson::setHomepage(const QString &homepage)
{
    m_homepage = homepage;
    emit homepageChanged();
}

QString TraktPerson::type() const
{
    return m_type;
}

void TraktPerson::setType(const QString &type)
{
    m_type = type;
    emit typeChanged();
}

QString TraktPerson::character() const
{
    return m_character;
}

void TraktPerson::setCharacter(const QString &character)
{
    m_character = character;
    emit characterChanged();
}

QString TraktPerson::job() const
{
    return m_job;
}

void TraktPerson::setJob(const QString &job)
{
    m_job = job;
    emit jobChanged();
}

QString TraktPerson::title() const
{
    return m_name;
}

void TraktPerson::setTitle(const QString &title)
{
    Q_UNUSED(title)
}

void TraktPerson::parse(const QVariantMap &data)
{
    setBiography(data.value("biography").toString());
    setBirthday(data.value("birthday").toDate());
    setDeath(data.value("death").toDate());
    setBirthplace(data.value("birthplace").toString());
    setHomepage(data.value("homepage").toString());

    setLoaded(true);
}

QString TraktPerson::itemUrl() const
{
    return QString("/people/%1").arg(ids()->trakt());
}
