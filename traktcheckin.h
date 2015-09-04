#ifndef TRAKTCHECKIN_H
#define TRAKTCHECKIN_H

#include <QObject>

class TraktIds;

class TraktCheckin : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TraktIds *item READ item WRITE setItem NOTIFY itemChanged)
    Q_PROPERTY(bool shareOnFacebook READ shareOnFacebook WRITE setShareOnFacebook NOTIFY shareOnFacebookChanged)
    Q_PROPERTY(bool shareOnTwitter READ shareOnTwitter WRITE setShareOnTwitter NOTIFY shareOnTwitterChanged)
    Q_PROPERTY(bool shareOnTumblr READ shareOnTumblr WRITE setShareOnTumblr NOTIFY shareOnTumblrChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(QString appVersion READ appVersion WRITE setAppVersion NOTIFY appVersionChanged)
    Q_PROPERTY(QString appDate READ appDate WRITE setAppDate NOTIFY appDateChanged)
public:
    explicit TraktCheckin(QObject *parent = 0);

    TraktIds *item() const;
    void setItem(TraktIds *ids);

    bool shareOnFacebook() const;
    void setShareOnFacebook(bool share);

    bool shareOnTwitter() const;
    void setShareOnTwitter(bool share);

    bool shareOnTumblr() const;
    void setShareOnTumblr(bool share);

    QString message() const;
    void setMessage(const QString &message);

    QString appVersion() const;
    void setAppVersion(const QString &appVersion);

    QString appDate() const;
    void setAppDate(const QString &appDate);

signals:
    void itemChanged();
    void shareOnFacebookChanged();
    void shareOnTwitterChanged();
    void shareOnTumblrChanged();
    void messageChanged();
    void appVersionChanged();
    void appDateChanged();

public slots:
    void checkIn();

private:
    TraktIds *m_item;
    bool m_shareOnFacebook;
    bool m_shareOnTwitter;
    bool m_shareOnTumblr;
    QString m_message;
    QString m_appVersion;
    QString m_appDate;

};

#endif // TRAKTCHECKIN_H
