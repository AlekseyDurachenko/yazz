# Copyright 2014, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
TARGET          = yazz
TEMPLATE        = app

CONFIG         += console debug_and_release
QT             += core gui network xml

# Release build options
release:DESTDIR     = bin
release:OBJECTS_DIR = build/release/obj
release:MOC_DIR     = build/release/moc
release:RCC_DIR     = build/release/rcc
release:UI_DIR      = build/release/ui
# Debug build options
debug:DESTDIR       = bin
debug:OBJECTS_DIR   = build/debug/obj
debug:MOC_DIR       = build/debug/moc
debug:RCC_DIR       = build/debug/rcc
debug:UI_DIR        = build/debug/ui

DEFINES        +=                                           \

INCLUDEPATH    +=                                           \
    $$PWD/src                                               \
    $$PWD/src/browser                                       \
    $$PWD/src/webdav                                        \

HEADERS        +=                                           \
    src/webdav/qtwebdav.h                                   \
    src/webdav/qtabstractwebdavreply.h                      \
    src/webdav/qtmakedirwebdavreply.h                       \
    src/webdav/qtremovewebdavreply.h                        \
    src/webdav/qtcopywebdavreply.h                          \
    src/webdav/qtmovewebdavreply.h                          \
    src/webdav/qtputwebdavreply.h                           \
    src/webdav/qtgetwebdavreply.h                           \
    src/webdav/qtgetfreespacewebdavreply.h                  \
    src/webdav/qtlistwebdavreply.h                          \
    src/caboutdialog.h                                      \
    src/ctest.h                                             \
    src/global.h                                            \
    src/consts.h                                            \
    src/webdav/qtwebdavfilerecord.h \
    src/browser/cwebdavitemmodel.h \
    src/browser/cwebdavdatamodel.h

SOURCES        +=                                           \
    src/webdav/qtwebdav.cpp                                 \
    src/webdav/qtabstractwebdavreply.cpp                    \
    src/webdav/qtmakedirwebdavreply.cpp                     \
    src/webdav/qtremovewebdavreply.cpp                      \
    src/webdav/qtcopywebdavreply.cpp                        \
    src/webdav/qtmovewebdavreply.cpp                        \
    src/webdav/qtputwebdavreply.cpp                         \
    src/webdav/qtgetwebdavreply.cpp                         \
    src/webdav/qtgetfreespacewebdavreply.cpp                \
    src/webdav/qtlistwebdavreply.cpp                        \
    src/caboutdialog.cpp                                    \
    src/ctest.cpp                                           \
    src/webdav/qtwebdavfilerecord.cpp \
    src/browser/cwebdavitemmodel.cpp \
    src/browser/cwebdavdatamodel.cpp

FORMS          +=                                           \
    src/caboutdialog.ui                                     \

RESOURCES      +=                                           \
    qrc/about.qrc                                           \
    qrc/icons.qrc                                           \

OTHER_FILES    +=                                           \
    AUTHORS                                                 \
    CHANGELOG                                               \
    LICENSE                                                 \

# if you want to test the project, do: qmake "QT += testlib"
contains(QT, testlib) {
    SOURCES   +=                                            \

    HEADERS   +=                                            \

} else {
    SOURCES   +=                                            \
        src/main.cpp                                        \

}

win32 {
    CONFIG += embed_manifest_exe
    RC_FILE = yazz.rc
}

# debug
build_pass:CONFIG(debug, debug|release) {
    win32 {
    }

    unix {
        LIBS +=
        DEFINES += "G_VERSION=\"\\\"$$system($$PWD/get_version.sh)\\\"\""
    }
}

# release
build_pass:CONFIG(release, debug|release) {
    win32 {
        CONFIG -= console 
        LIBS +=
        DEFINES += "G_VERSION=\"\\\"$$system('sh -c $$PWD/get_version.sh')\\\"\""
    }

    unix {
        LIBS +=
        DEFINES += "G_VERSION=\"\\\"$$system($$PWD/get_version.sh)\\\"\""
    }
}
