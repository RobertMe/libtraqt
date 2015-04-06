#ifndef TRAKTIMAGES_H
#define TRAKTIMAGES_H

#include <QObject>

class TraktImages : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString full READ full WRITE setFull NOTIFY fullChanged)
    Q_PROPERTY(QString medium READ medium WRITE setMedium NOTIFY mediumChanged)
    Q_PROPERTY(QString thumb READ thumb WRITE setThumb NOTIFY thumbChanged)
public:
    explicit TraktImages(QObject *parent = 0);
    explicit TraktImages(const QVariantMap &data, QObject *parent = 0);

    QString full() const;
    void setFull(const QString &url);

    QString medium() const;
    void setMedium(const QString &url);

    QString thumb() const;
    void setThumb(const QString &url);

signals:
    void fullChanged();
    void mediumChanged();
    void thumbChanged();

private:
    QString m_full;
    QString m_medium;
    QString m_thumb;
};

Q_DECLARE_METATYPE(TraktImages*)

#endif // TRAKTIMAGES_H
