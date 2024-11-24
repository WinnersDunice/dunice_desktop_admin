greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Указываем, что используем libcurl
LIBS += -lcurl

# Путь к включаемым файлам (заголовкам) libcurl

INCLUDEPATH += $$PWD/include
LIBS += -L$$PWD/lib -lcurl

win32 {
    INCLUDEPATH += $$PWD/include
    LIBS += -L$$PWD/lib -lcurl
}

unix {
    INCLUDEPATH += /usr/include
    LIBS += -L/usr/lib -lcurl
}

# Источники проекта
SOURCES += \
    CheckProcessor.cpp \
    DataSender.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CheckProcessor.h \
    DataSender.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Переводы
TRANSLATIONS += \
    duniceDesktopAdmin_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

QT += core network gui widgets

# Указываем ресурсы
RESOURCES += resources.qrc

# Правила для развертывания
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
