TEMPLATE = app
TARGET = NoteNote

# Input
SOURCES += \
    src/main.cpp \

HEADERS += \
    include/MainWindow.h \
    include/MyClass.h

# Resources
RESOURCES += resources.qrc

# Qt modules used by the application
QT += widgets

# Additional configuration (optional)
CONFIG += c++11
CONFIG -= app_bundle
