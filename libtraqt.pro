TARGET = traqt
TEMPLATE = lib
CONFIG += staticlib c++11

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
    traktimageset.h \
    traktmodel.h \
    traktpeoplemodel.h \
    traktperson.h \
    traktpeoplefiltermodel.h \
    traktshow.h \
    traktshowsmodel.h \
    traktshows.h \
    traktseason.h \
    traktseasonsmodel.h \
    traktcheckin.h \
    traktpeople.h \
    traktepisode.h \
    traktepisodesmodel.h \
    traktpersonmoviesmodel.h \
    traktpersonshowsmodel.h \
    traktitem.h

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
    traktimageset.cpp \
    traktmodel.cpp \
    traktpeoplemodel.cpp \
    traktperson.cpp \
    traktpeoplefiltermodel.cpp \
    traktshow.cpp \
    traktshowsmodel.cpp \
    traktshows.cpp \
    traktseason.cpp \
    traktseasonsmodel.cpp \
    traktcheckin.cpp \
    traktpeople.cpp \
    traktepisode.cpp \
    traktepisodesmodel.cpp \
    traktpersonmoviesmodel.cpp \
    traktpersonshowsmodel.cpp \
    traktitem.cpp



