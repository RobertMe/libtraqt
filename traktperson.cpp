#include "traktperson.h"

#include <QVariantMap>

#include "traktrequest.h"
#include "traktreply.h"

TraktPerson::TraktPerson(QObject *parent) :
    QObject(parent),
    m_loaded(false)
{
}

TraktPerson::TraktPerson(const QVariantMap &data, QObject *parent) :
    QObject(parent),
    m_loaded(false)
{
    m_ids = new TraktIds(data.value("ids").toMap(), "people", this);
    m_name = data.value("name").toString();
    m_images = new TraktImageSet(data.value("images").toMap(), this);
}

TraktIds *TraktPerson::ids() const
{
    return m_ids;
}

void TraktPerson::setIds(TraktIds *ids)
{
    m_ids = ids;
    emit idsChanged();
}

QString TraktPerson::name() const
{
    return m_name;
}

void TraktPerson::setName(const QString &name)
{
    m_name = name;
    emit nameChanged();
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

TraktImageSet *TraktPerson::images() const
{
    return m_images;
}

void TraktPerson::setImages(TraktImageSet *images)
{
    m_images = images;
    emit imagesChanged();
}

void TraktPerson::parse(const QVariantMap &data)
{
    setBiography(data.value("biography").toString());
    setBirthday(data.value("birthday").toDate());
    setDeath(data.value("death").toDate());
    setBirthplace(data.value("birthplace").toString());
    setHomepage(data.value("homepage").toString());

    m_loaded = true;
}

void TraktPerson::load()
{
    if (m_loaded) {
        return;
    }

    TraktRequest *request = new TraktRequest(this);
    request->setPath(QString("/people/%1").arg(ids()->trakt()));
    request->addQueryItem("extended", "full");
    connect(request, &TraktRequest::replyReceived, this, &TraktPerson::onFullyLoaded);
    request->send();
}

void TraktPerson::onFullyLoaded(TraktReply *reply)
{
    reply->deleteLater();
    parse(reply->asMap());
}
