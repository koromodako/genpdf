QT      += core gui widgets webenginecore
CONFIG  += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    interceptor.cpp \
    main.cpp \
    pdfgenerator.cpp

HEADERS += \
    interceptor.h \
    pdfgenerator.h
