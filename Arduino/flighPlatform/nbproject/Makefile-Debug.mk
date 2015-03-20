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
CC=avr-gcc
CCC=avr-g++
CXX=avr-g++
FC=gfortran
AS=avr-as

# Macros
CND_PLATFORM=arduino161-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/libs/ADXL345.o \
	${OBJECTDIR}/libs/HMC5883.o \
	${OBJECTDIR}/libs/L3G4200D.o \
	${OBJECTDIR}/libs/PID.o \
	${OBJECTDIR}/libs/Tilt.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=${FLAGS_GCC}

# CC Compiler Flags
CCFLAGS=${FLAGS_GPP}
CXXFLAGS=${FLAGS_GPP}

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flighplatform

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flighplatform: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	avr-gcc -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flighplatform ${OBJECTFILES} ${LDLIBSOPTIONS} ${FLAGS_LINKER}

${OBJECTDIR}/libs/ADXL345.o: libs/ADXL345.cpp 
	${MKDIR} -p ${OBJECTDIR}/libs
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libs/ADXL345.o libs/ADXL345.cpp

${OBJECTDIR}/libs/HMC5883.o: libs/HMC5883.cpp 
	${MKDIR} -p ${OBJECTDIR}/libs
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libs/HMC5883.o libs/HMC5883.cpp

${OBJECTDIR}/libs/L3G4200D.o: libs/L3G4200D.cpp 
	${MKDIR} -p ${OBJECTDIR}/libs
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libs/L3G4200D.o libs/L3G4200D.cpp

${OBJECTDIR}/libs/PID.o: libs/PID.cpp 
	${MKDIR} -p ${OBJECTDIR}/libs
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libs/PID.o libs/PID.cpp

${OBJECTDIR}/libs/Tilt.o: libs/Tilt.cpp 
	${MKDIR} -p ${OBJECTDIR}/libs
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/libs/Tilt.o libs/Tilt.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCLUDE} -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flighplatform

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
