#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin_4.x-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/sqlite-amalgamation-3080300/sqlite3.o \
	${OBJECTDIR}/sqlite3pp/sqlite3pp.o \
	${OBJECTDIR}/sqlite3pp/sqlite3ppext.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../../../../boost_1_55_0/libs

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cyclopeptidesequencing.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cyclopeptidesequencing.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cyclopeptidesequencing ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../boost_1_55_0 -Isqlite-amalgamation-3080300 -Isqlite3pp -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/sqlite-amalgamation-3080300/sqlite3.o: sqlite-amalgamation-3080300/sqlite3.c 
	${MKDIR} -p ${OBJECTDIR}/sqlite-amalgamation-3080300
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sqlite-amalgamation-3080300/sqlite3.o sqlite-amalgamation-3080300/sqlite3.c

${OBJECTDIR}/sqlite3pp/sqlite3pp.o: sqlite3pp/sqlite3pp.cpp 
	${MKDIR} -p ${OBJECTDIR}/sqlite3pp
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../boost_1_55_0 -Isqlite-amalgamation-3080300 -Isqlite3pp -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sqlite3pp/sqlite3pp.o sqlite3pp/sqlite3pp.cpp

${OBJECTDIR}/sqlite3pp/sqlite3ppext.o: sqlite3pp/sqlite3ppext.cpp 
	${MKDIR} -p ${OBJECTDIR}/sqlite3pp
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../boost_1_55_0 -Isqlite-amalgamation-3080300 -Isqlite3pp -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sqlite3pp/sqlite3ppext.o sqlite3pp/sqlite3ppext.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cyclopeptidesequencing.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
