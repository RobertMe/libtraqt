#ifndef TRAKTREQUEST_H
#define TRAKTREQUEST_H

#include <QObject>

class TraktRequest : public QObject
{
    Q_OBJECT
public:
    explicit TraktRequest(QObject *parent = 0);

    QString test;
signals:

public slots:

};

#endif // TRAKTREQUEST_H
