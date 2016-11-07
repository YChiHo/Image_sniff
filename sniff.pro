QT += core
QT -= gui

CONFIG += c++11

TARGET = sniff
CONFIG += console
CONFIG -= app_bundle
LIBS += -lpcap
LIBS += -ltins
LIBS += -lpthread
TEMPLATE = app

SOURCES += main.cpp \
    http_parser.cpp

HEADERS += \
    http_parser.h
