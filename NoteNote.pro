QT       += core gui widgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/gui/notenote.cpp \
    src/gui/auth/authwidget.cpp \
    src/gui/auth/loginwidget.cpp \
    src/gui/auth/registerwidget.cpp \
    src/gui/navigation/navigationbar.cpp \
    src/gui/navigation/pagesmanagerwidget.cpp \
    src/gui/pages/activities/graded/gradedactivitieswidget.cpp \
    src/gui/pages/activities/ungraded/ungradedactivitieswidget.cpp \
    src/gui/pages/assiduity/absences/absenceswidget.cpp \
    src/gui/pages/assiduity/lates/lateswidget.cpp \
    src/gui/pages/grades/gradeswidget.cpp \
    src/gui/pages/lessons/lessonswidget.cpp \
    src/gui/pages/reports/reportswidget.cpp \
    src/gui/pages/sanctions/sanctionswidget.cpp \
    src/gui/pages/schedules/scheduleswidget.cpp \
    src/gui/pages/students/studentswidget.cpp \
    src/gui/pages/themes/themeswidget.cpp \
    src/controllers/initdb.cpp \
    src/controllers/userscontroller.cpp \
    src/models/general.cpp \
    src/models/usersmodel.cpp \
    src/utils/authutils.cpp \
    src/utils/logger.cpp \
    src/gui/utils/pageswitcher.cpp \
    src/gui/pages/grades/classtrimestersubjectpicker.cpp \
    src/utils/formatutils.cpp \
    src/models/classesmodel.cpp \
    src/controllers/classescontroller.cpp

HEADERS += \
    src/gui/notenote.h \
    src/gui/auth/authwidget.h \
    src/gui/auth/loginwidget.h \
    src/gui/auth/registerwidget.h \
    src/gui/navigation/navigationbar.h \
    src/gui/navigation/pagesmanagerwidget.h \
    src/gui/pages/activities/graded/gradedactivitieswidget.h \
    src/gui/pages/activities/ungraded/ungradedactivitieswidget.h \
    src/gui/pages/assiduity/absences/absenceswidget.h \
    src/gui/pages/assiduity/lates/lateswidget.h \
    src/gui/pages/grades/gradeswidget.h \
    src/gui/pages/lessons/lessonswidget.h \
    src/gui/pages/reports/reportswidget.h \
    src/gui/pages/sanctions/sanctionswidget.h \
    src/gui/pages/schedules/scheduleswidget.h \
    src/gui/pages/students/studentswidget.h \
    src/gui/pages/themes/themeswidget.h \
    src/controllers/initdb.h \
    src/controllers/userscontroller.h \
    src/models/general.h \
    src/models/usersmodel.h \
    src/utils/authutils.h \
    src/utils/exceptions.hpp \
    src/utils/logger.h \
    src/gui/utils/pageswitcher.h \
    src/gui/pages/grades/classtrimestersubjectpicker.h \
    src/utils/sessionmanager.hpp \
    src/utils/formatutils.h \
    src/models/classesmodel.h \
    src/controllers/classescontroller.h

TRANSLATIONS += \
    NoteNote_fr_FR.ts

# Resources
RESOURCES += \
    assets/resources.qrc

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
