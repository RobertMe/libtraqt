#ifndef TRAKTPERSON_H
#define TRAKTPERSON_H

#include <QObject>
#include <QDate>

#include "traktitem.h"

class TraktPerson : public TraktItem
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString biography READ biography WRITE setBiography NOTIFY biographyChanged)
    Q_PROPERTY(QDate birthday READ birthday WRITE setBirthday NOTIFY birthdayChanged)
    Q_PROPERTY(QDate death READ death WRITE setDeath NOTIFY deathChanged)
    Q_PROPERTY(QString birthplace READ birthplace WRITE setBirthplace NOTIFY birthplaceChanged)
    Q_PROPERTY(QString homepage READ homepage WRITE setHomepage NOTIFY homepageChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString character READ character WRITE setCharacter NOTIFY characterChanged)
    Q_PROPERTY(QString job READ job WRITE setJob NOTIFY jobChanged)
public:
    explicit TraktPerson(QObject *parent = 0);
    explicit TraktPerson(const QVariantMap &data, QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    QString biography() const;
    void setBiography(const QString &biography);

    QDate birthday() const;
    void setBirthday(const QDate &birthday);

    QDate death() const;
    void setDeath(const QDate &death);

    QString birthplace() const;
    void setBirthplace(const QString &birthplace);

    QString homepage() const;
    void setHomepage(const QString &homepage);

    QString type() const;
    void setType(const QString &type);

    QString character() const;
    void setCharacter(const QString &character);

    QString job() const;
    void setJob(const QString &job);

    QString title() const Q_DECL_OVERRIDE;
    void setTitle(const QString &title) Q_DECL_OVERRIDE;

    void parse(const QVariantMap &data) Q_DECL_OVERRIDE;

signals:
    void nameChanged();
    void biographyChanged();
    void birthdayChanged();
    void deathChanged();
    void birthplaceChanged();
    void homepageChanged();
    void typeChanged();
    void characterChanged();
    void jobChanged();

protected:
    QString itemUrl() const Q_DECL_OVERRIDE;

private:
    QString m_name;
    QString m_biography;
    QDate m_birthday;
    QDate m_death;
    QString m_birthplace;
    QString m_homepage;
    QString m_type;
    QString m_character;
    QString m_job;
};

#endif // TRAKTPERSON_H
