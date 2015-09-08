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
    Q_PROPERTY(TraktImages *image READ image NOTIFY imageChanged)
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged)
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
    Q_PROPERTY(bool error READ error NOTIFY errorChanged)
public:
    explicit TraktItem(QObject *parent = 0);

    virtual TraktIds *ids() const;
    virtual void setIds(TraktIds *ids);

    virtual QString title() const;
    virtual void setTitle(const QString &title);

    virtual TraktImageSet *images() const;
    virtual void setImages(TraktImageSet *images);

    virtual TraktImages *image() const;

    bool loaded() const;
    bool loading() const;
    bool error() const;

    virtual void parse(const QVariantMap &data) = 0;
    Q_INVOKABLE virtual void load();

signals:
    void idsChanged();
    void titleChanged();
    void imagesChanged();
    void imageChanged();
    void loadedChanged();
    void loadingChanged();
    void errorChanged();

protected:
    virtual QString itemUrl() const = 0;
    virtual void connectImageChanged(TraktImageSet *images) const;
    void setLoaded(bool loaded);
    void setLoading(bool loading);
    void setError(bool error);

    TraktIds *m_ids;
    QString m_title;
    TraktImageSet *m_images;

private:
    bool m_loaded;
    bool m_loading;
    bool m_error;

private slots:
    void onFullyLoaded(TraktReply *reply);

};

#endif // TRAKTITEM_H
