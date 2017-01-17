QT += core testlib
QT -= gui

CONFIG += c++14

TARGET = tests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    directoryexplorertest.cpp \
    duplicatefindertest.cpp

HEADERS += main.h \
    directoryexplorertest.h \
    duplicatefindertest.h

INCLUDEPATH += $$PWD/../image-duplicate-finder-lib/include $$PWD/../../../ext_lib/include

#Name of the directories to create
DIRS = samples debug/samples release/samples

#Loop through all the directories and add their path as arguments for the mkdir command
for(DIR, DIRS) : mkcommands += $$OUT_PWD/$$DIR

#Create the command call
create_dirs = $(MKDIR) $$mkcommands

#Make the Makefile build step "first" depend on the create_dirs
first.depends += create_dirs

#Add this target to the one Qt generates
QMAKE_EXTRA_TARGETS += create_dirs

#Create the install instruction for the samples
samples.path = $$OUT_PWD/samples #The path where the samples will be copied
samples.files = $$PWD/samples/* #All the files inside the samples folder need to be copied

#All the samples files, this time for the folder where the .exe is
samples_deploy.files = $$PWD/samples/*

#Link all the dlls required
include($$PWD/../libs_linker.pri)

win32:CONFIG(release, debug|release): samples_deploy.path = $$OUT_PWD/release/samples
else:win32:CONFIG(debug, debug|release): samples_deploy.path = $$OUT_PWD/debug/samples


#Add the install instructions
INSTALLS += samples \
            samples_deploy
