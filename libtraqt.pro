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
    traktreply.h

SOURCES += \
    traktrequest.cpp \
    traktauthenticator.cpp \
    traktconnection.cpp \
    traktreply.cpp



