QT       += core gui widgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += lrelease
CONFIG += embed_translations

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/controllers/classescontroller.cpp \
    src/controllers/initdb.cpp \
    src/controllers/userscontroller.cpp \
    src/gui/auth/authwidget.cpp \
    src/gui/auth/loginwidget.cpp \
    src/gui/auth/registerwidget.cpp \
    src/gui/navigation/navigationbar.cpp \
    src/gui/navigation/pagesmanagerwidget.cpp \
    src/gui/notenote.cpp \
    src/gui/pages/activities/graded/gradedactivitieswidget.cpp \
    src/gui/pages/activities/ungraded/ungradedactivitieswidget.cpp \
    src/gui/pages/assiduity/absences/absenceswidget.cpp \
    src/gui/pages/assiduity/lates/lateswidget.cpp \
    src/gui/pages/grades/classtrimestersubjectpicker.cpp \
    src/gui/pages/grades/gradesdisplay.cpp \
    src/gui/pages/grades/gradeswidget.cpp \
    src/gui/pages/lessons/extensionpickerwidget.cpp \
    src/gui/pages/lessons/filecreatorwidget.cpp \
    src/gui/pages/lessons/lessonscontextmenu.cpp \
    src/gui/pages/lessons/namepickerwidget.cpp \
    src/gui/pages/lessons/lessonswidget.cpp \
    src/gui/pages/reports/reportswidget.cpp \
    src/gui/pages/sanctions/sanctionswidget.cpp \
    src/gui/pages/schedules/scheduleswidget.cpp \
    src/gui/pages/settings/settingswidget.cpp \
    src/gui/pages/students/studentswidget.cpp \
    src/gui/pages/themes/themeswidget.cpp \
    src/gui/utils/pageswitcher.cpp \
    src/main.cpp \
    src/models/classesmodel.cpp \
    src/models/general.cpp \
    src/models/usersmodel.cpp \
    src/controllers/utils/authutils.cpp \
    src/utils/fileutils.cpp \
    src/utils/formatutils.cpp \
    src/utils/logger.cpp

HEADERS += \
    include/controllers/classescontroller.h \
    include/controllers/initdb.h \
    include/controllers/userscontroller.h \
    include/gui/auth/authwidget.h \
    include/gui/auth/loginwidget.h \
    include/gui/auth/registerwidget.h \
    include/gui/navigation/navigationbar.h \
    include/gui/navigation/pagesmanagerwidget.h \
    include/gui/notenote.h \
    include/gui/pages/activities/graded/gradedactivitieswidget.h \
    include/gui/pages/activities/ungraded/ungradedactivitieswidget.h \
    include/gui/pages/assiduity/absences/absenceswidget.h \
    include/gui/pages/assiduity/lates/lateswidget.h \
    include/gui/pages/grades/classtrimestersubjectpicker.h \
    include/gui/pages/grades/gradesdisplay.h \
    include/gui/pages/grades/gradeswidget.h \
    include/gui/pages/lessons/extensionpickerwidget.h \
    include/gui/pages/lessons/filecreatorwidget.h \
    include/gui/pages/lessons/lessonscontextmenu.h \
    include/gui/pages/lessons/namepickerwidget.h \
    include/gui/pages/lessons/lessonswidget.h \
    include/gui/pages/reports/reportswidget.h \
    include/gui/pages/sanctions/sanctionswidget.h \
    include/gui/pages/schedules/scheduleswidget.h \
    include/gui/pages/settings/settingswidget.h \
    include/gui/pages/students/studentswidget.h \
    include/gui/pages/themes/themeswidget.h \
    include/gui/utils/pageswitcher.h \
    include/models/classesmodel.h \
    include/models/general.h \
    include/models/usersmodel.h \
    include/controllers/utils/authutils.h \
    include/utils/exceptions.hpp \
    include/utils/fileutils.h \
    include/utils/formatutils.h \
    include/utils/logger.h \
    include/utils/sessionmanager.hpp

INCLUDEPATH += include

TRANSLATIONS += \
    assets/translations/NoteNote_fr_FR.ts

RESOURCES += \
    assets/resources.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
