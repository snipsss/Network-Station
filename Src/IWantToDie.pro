QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ButtonsCLS.cpp \
    ButtonsServerCLS.cpp \
    NetWorkCLS.cpp \
    Package.cpp \
    ServerInit.cpp \
    ServerRunnerCLS.cpp \
    SocketCLS.cpp \
    TableCLS.cpp \
    ValidatorCLS.cpp \
    ipEndPoint.cpp \
    main.cpp

HEADERS += \
    ButtonsCLS.h \
    ButtonsServerCLS.h \
    ConstantCLS.h \
    NetWorkCLS.h \
    PResultCLS.h \
    Package.h \
    PackageExtenntionCLS.h \
    PackageType.h \
    ServerRunnerCLS.h \
    ServerWidget.h \
    SocketCLS.h \
    SocketHandle.h \
    SocketOptions.h \
    TableCLS.h \
    ValidatorCLS.h \
    includeMe.h \
    ipEndPoint.h \
    ipVersion.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    CMakeLists
