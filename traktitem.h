#ifndef TRAKTITEM_H
#define TRAKTITEM_H

#include <QObject>

#include "traktids.h"
#include "traktimageset.h"

class TraktReply;

class TraktItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TraktIds *ids READ ids WRITE setIds NOTIFY idsChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(TraktImageSet *images READ images WRITE setImages NOTIFY imagesChanged)
public:
    explicit TraktItem(QObject *parent = 0);

    virtual TraktIds *ids() const;
    virtual void setIds(TraktIds *ids);

    virtual QString title() const;
    virtual void setTitle(const QString &title);

    virtual TraktImageSet *images() const;
    virtual void setImages(TraktImageSet *images);

    virtual void parse(const QVariantMap &data) = 0;
    Q_INVOKABLE virtual void load();

signals:
    void idsChanged();
    void titleChanged();
    void imagesChanged();

protected:
    virtual QString itemUrl() const = 0;
    void setLoaded(bool loaded);

    TraktIds *m_ids;
    QString m_title;
    TraktImageSet *m_images;

private:
    bool m_loaded;

private slots:
    void onFullyLoaded(TraktReply *reply);

};

#endif // TRAKTITEM_H
