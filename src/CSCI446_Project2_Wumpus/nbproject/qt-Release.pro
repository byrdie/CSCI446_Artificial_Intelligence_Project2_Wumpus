# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux
TARGET = CSCI446_Project2_Wumpus
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui widgets
SOURCES += engine.cpp human_agent.cpp inference.cpp knowledge.cpp main.cpp qt_world.cpp reactive_agent.cpp resolve.cpp rule_parser.cpp tests.cpp typedef.cpp unify.cpp world_gen.cpp
HEADERS += engine.h human_agent.h inference.h knowledge.h main.h predicate.h qt_world.h reactive_agent.h resolve.h rule_parser.h tests.h typedef.h world_gen.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
