TARGET = traqt
TEMPLATE = lib
CONFIG += staticlib

QT += network

DEFINES += TRAKT_API_URL=\\\"https://api-v2launch.trakt.tv\\\"
DEFINES += TRAKT_WEB_URL=\\\"https://trakt.tv\\\"

HEADERS += \
    traktrequest.h \
    traktauthenticator.h \
    traktconnection.h \
    traktmovies.h \
    traktpaginatedmodel.h \
    traktmoviesmodel.h \
    traktmovie.h \
    traktreply.h \
    traktids.h \
    traktimages.h \
    traktimageset.h

SOURCES += \
    traktrequest.cpp \
    traktauthenticator.cpp \
    traktconnection.cpp \
    traktmovies.cpp \
    traktpaginatedmodel.cpp \
    traktmoviesmodel.cpp \
    traktmovie.cpp \
    traktreply.cpp \
    traktids.cpp \
    traktimages.cpp \
    traktimageset.cpp



