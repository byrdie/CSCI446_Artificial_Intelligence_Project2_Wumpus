#############################################################################
# Makefile for building: dist/Debug/GNU-Linux/CSCI446_Project2_Wumpus
# Generated by qmake (2.01a) (Qt 4.8.7) on: Mon Oct 24 13:05:01 2016
# Project:  nbproject/qt-Debug.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt4/bin/qmake VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -std=c++11 -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -Inbproject -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -Inbproject -I.
LINK          = g++
LFLAGS        = -m64
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/x86_64-linux-gnu/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = build/Debug/GNU-Linux/

####### Files

SOURCES       = engine.cpp \
		human_agent.cpp \
		inference.cpp \
		knowledge.cpp \
		logic_agent.cpp \
		main.cpp \
		qt_world.cpp \
		reactive_agent.cpp \
		resolve.cpp \
		rule_parser.cpp \
		tests.cpp \
		typedef.cpp \
		unify.cpp \
		world_gen.cpp 
OBJECTS       = build/Debug/GNU-Linux/engine.o \
		build/Debug/GNU-Linux/human_agent.o \
		build/Debug/GNU-Linux/inference.o \
		build/Debug/GNU-Linux/knowledge.o \
		build/Debug/GNU-Linux/logic_agent.o \
		build/Debug/GNU-Linux/main.o \
		build/Debug/GNU-Linux/qt_world.o \
		build/Debug/GNU-Linux/reactive_agent.o \
		build/Debug/GNU-Linux/resolve.o \
		build/Debug/GNU-Linux/rule_parser.o \
		build/Debug/GNU-Linux/tests.o \
		build/Debug/GNU-Linux/typedef.o \
		build/Debug/GNU-Linux/unify.o \
		build/Debug/GNU-Linux/world_gen.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		nbproject/qt-Debug.pro
QMAKE_TARGET  = CSCI446_Project2_Wumpus
DESTDIR       = dist/Debug/GNU-Linux/
TARGET        = dist/Debug/GNU-Linux/CSCI446_Project2_Wumpus

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: qttmp-Debug.mk $(TARGET)

$(TARGET):  $(OBJECTS)  
	@$(CHK_DIR_EXISTS) dist/Debug/GNU-Linux/ || $(MKDIR) dist/Debug/GNU-Linux/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9][^0-9]*\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

qttmp-Debug.mk: nbproject/qt-Debug.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro

dist: 
	@$(CHK_DIR_EXISTS) build/Debug/GNU-Linux/CSCI446_Project2_Wumpus1.0.0 || $(MKDIR) build/Debug/GNU-Linux/CSCI446_Project2_Wumpus1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) build/Debug/GNU-Linux/CSCI446_Project2_Wumpus1.0.0/ && $(COPY_FILE) --parents engine.h human_agent.h inference.h knowledge.h logic_agent.h main.h predicate.h qt_world.h reactive_agent.h resolve.h rule_parser.h tests.h typedef.h world_gen.h build/Debug/GNU-Linux/CSCI446_Project2_Wumpus1.0.0/ && $(COPY_FILE) --parents engine.cpp human_agent.cpp inference.cpp knowledge.cpp logic_agent.cpp main.cpp qt_world.cpp reactive_agent.cpp resolve.cpp rule_parser.cpp tests.cpp typedef.cpp unify.cpp world_gen.cpp build/Debug/GNU-Linux/CSCI446_Project2_Wumpus1.0.0/ && (cd `dirname build/Debug/GNU-Linux/CSCI446_Project2_Wumpus1.0.0` && $(TAR) CSCI446_Project2_Wumpus1.0.0.tar CSCI446_Project2_Wumpus1.0.0 && $(COMPRESS) CSCI446_Project2_Wumpus1.0.0.tar) && $(MOVE) `dirname build/Debug/GNU-Linux/CSCI446_Project2_Wumpus1.0.0`/CSCI446_Project2_Wumpus1.0.0.tar.gz . && $(DEL_FILE) -r build/Debug/GNU-Linux/CSCI446_Project2_Wumpus1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) qttmp-Debug.mk


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all:
compiler_moc_header_clean:
compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

build/Debug/GNU-Linux/engine.o: engine.cpp engine.h \
		world_gen.h \
		logic_agent.h \
		qt_world.h \
		typedef.h \
		human_agent.h \
		knowledge.h \
		rule_parser.h \
		reactive_agent.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/engine.o engine.cpp

build/Debug/GNU-Linux/human_agent.o: human_agent.cpp human_agent.h \
		typedef.h \
		world_gen.h \
		logic_agent.h \
		qt_world.h \
		reactive_agent.h \
		engine.h \
		knowledge.h \
		rule_parser.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/human_agent.o human_agent.cpp

build/Debug/GNU-Linux/inference.o: inference.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/inference.o inference.cpp

build/Debug/GNU-Linux/knowledge.o: knowledge.cpp knowledge.h \
		typedef.h \
		rule_parser.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/knowledge.o knowledge.cpp

build/Debug/GNU-Linux/logic_agent.o: logic_agent.cpp logic_agent.h \
		qt_world.h \
		typedef.h \
		human_agent.h \
		world_gen.h \
		reactive_agent.h \
		engine.h \
		knowledge.h \
		rule_parser.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/logic_agent.o logic_agent.cpp

build/Debug/GNU-Linux/main.o: main.cpp main.h \
		world_gen.h \
		logic_agent.h \
		qt_world.h \
		typedef.h \
		human_agent.h \
		engine.h \
		knowledge.h \
		rule_parser.h \
		reactive_agent.h \
		tests.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/main.o main.cpp

build/Debug/GNU-Linux/qt_world.o: qt_world.cpp qt_world.h \
		typedef.h \
		human_agent.h \
		world_gen.h \
		logic_agent.h \
		engine.h \
		knowledge.h \
		rule_parser.h \
		reactive_agent.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/qt_world.o qt_world.cpp

build/Debug/GNU-Linux/reactive_agent.o: reactive_agent.cpp reactive_agent.h \
		typedef.h \
		world_gen.h \
		logic_agent.h \
		qt_world.h \
		human_agent.h \
		engine.h \
		knowledge.h \
		rule_parser.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/reactive_agent.o reactive_agent.cpp

build/Debug/GNU-Linux/resolve.o: resolve.cpp resolve.h \
		knowledge.h \
		typedef.h \
		rule_parser.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/resolve.o resolve.cpp

build/Debug/GNU-Linux/rule_parser.o: rule_parser.cpp rule_parser.h \
		knowledge.h \
		typedef.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/rule_parser.o rule_parser.cpp

build/Debug/GNU-Linux/tests.o: tests.cpp tests.h \
		knowledge.h \
		typedef.h \
		rule_parser.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/tests.o tests.cpp

build/Debug/GNU-Linux/typedef.o: typedef.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/typedef.o typedef.cpp

build/Debug/GNU-Linux/unify.o: unify.cpp knowledge.h \
		typedef.h \
		rule_parser.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/unify.o unify.cpp

build/Debug/GNU-Linux/world_gen.o: world_gen.cpp world_gen.h \
		logic_agent.h \
		qt_world.h \
		typedef.h \
		human_agent.h \
		engine.h \
		knowledge.h \
		rule_parser.h \
		reactive_agent.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux/world_gen.o world_gen.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

