TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    fraction.cpp \
    fractionfriends.cpp \
    polynomial.cpp \
    term.cpp \
    expression.cpp

HEADERS += \
    fraction.h \
    polynomial.h \
    term.h \
    term_error.h \
    expression.h
