QT       += core

QT       -= gui

TARGET = ParserTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../..

DEFINES += _DEBUG

SOURCES += \
    ParserTest.cpp \
    IrToken.cpp \
    IrLexer.cpp \
    IrParser.cpp \
    IrSynTree.cpp \
    IrTokenType.cpp

HEADERS += \
    IrToken.h \
    IrLexer.h \
    IrParser.h \
    IrSynTree.h \
    IrTokenType.h



