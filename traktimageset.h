#ifndef TRAKTIMAGESET_H
#define TRAKTIMAGESET_H

#include <QObject>

#include "traktimages.h"

class TraktImageSet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TraktImages *poster READ poster WRITE setPoster NOTIFY posterChanged)
    Q_PROPERTY(TraktImages *fanart READ fanart WRITE setFanart NOTIFY fanartChanged)
    Q_PROPERTY(TraktImages *screenshot READ screenshot WRITE setScreenshot NOTIFY screenshotChanged)
    Q_PROPERTY(TraktImages *headshot READ headshot WRITE setHeadshot NOTIFY headshotChanged)
    Q_PROPERTY(TraktImages *banner READ banner WRITE setBanner NOTIFY bannerChanged)
    Q_PROPERTY(TraktImages *logo READ logo WRITE setLogo NOTIFY logoChanged)
    Q_PROPERTY(TraktImages *clearart READ clearart WRITE setClearart NOTIFY clearartChanged)
    Q_PROPERTY(TraktImages *thumb READ thumb WRITE setThumb NOTIFY thumbChanged)
    Q_PROPERTY(TraktImages *avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
public:
    explicit TraktImageSet(QObject *parent = 0);
    explicit TraktImageSet(const QVariantMap &data, QObject *parent = 0);

    TraktImages *poster() const;
    void setPoster(TraktImages *images);

    TraktImages *fanart() const;
    void setFanart(TraktImages *images);

    TraktImages *screenshot() const;
    void setScreenshot(TraktImages *images);

    TraktImages *headshot() const;
    void setHeadshot(TraktImages *images);

    TraktImages *banner() const;
    void setBanner(TraktImages *images);

    TraktImages *logo() const;
    void setLogo(TraktImages *images);

    TraktImages *clearart() const;
    void setClearart(TraktImages *images);

    TraktImages *thumb() const;
    void setThumb(TraktImages *images);

    TraktImages *avatar() const;
    void setAvatar(TraktImages *images);

signals:
    void posterChanged();
    void fanartChanged();
    void screenshotChanged();
    void headshotChanged();
    void bannerChanged();
    void logoChanged();
    void clearartChanged();
    void thumbChanged();
    void avatarChanged();

private:
    TraktImages *m_poster;
    TraktImages *m_fanart;
    TraktImages *m_screenshot;
    TraktImages *m_headshot;
    TraktImages *m_banner;
    TraktImages *m_logo;
    TraktImages *m_clearart;
    TraktImages *m_thumb;
    TraktImages *m_avatar;

    TraktImages *createImages(QVariant imageData);
};

#endif // TRAKTIMAGESET_H
