
QT       -= core
QT       -= gui

TARGET = ecc
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CFLAGS += -std=c99

TEMPLATE = app

SOURCES += \ 
    codegen.c \
    hashmap.c \
    main.c \
    parse.c \
    preprocess.c \
    strings.c \
    tokenize.c \
    type.c \
    unicode.c

HEADERS += \
    chibicc.h \
    hostdetect.h
