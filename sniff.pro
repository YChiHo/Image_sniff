QT += core
QT -= gui
CONFIG += c++11

TARGET = sniff
CONFIG += console
CONFIG -= app_bundle
LIBS += -lpcap
LIBS += -ltins
LIBS += -lpthread
LIBS += -L/usr/lib/mysql -lmysqlclient_r
TEMPLATE = app

SOURCES += main.cpp \
    http_parser.cpp \
    db.cpp

HEADERS += \
    http_parser.h \
    db.h
