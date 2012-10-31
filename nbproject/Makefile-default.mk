#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SimpleSheduler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SimpleSheduler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/low-level/board.o ${OBJECTDIR}/src/low-level/serial.o ${OBJECTDIR}/src/low-level/timer.o ${OBJECTDIR}/src/os/jobs.o ${OBJECTDIR}/src/os/list.o ${OBJECTDIR}/src/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/low-level/board.o.d ${OBJECTDIR}/src/low-level/serial.o.d ${OBJECTDIR}/src/low-level/timer.o.d ${OBJECTDIR}/src/os/jobs.o.d ${OBJECTDIR}/src/os/list.o.d ${OBJECTDIR}/src/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/low-level/board.o ${OBJECTDIR}/src/low-level/serial.o ${OBJECTDIR}/src/low-level/timer.o ${OBJECTDIR}/src/os/jobs.o ${OBJECTDIR}/src/os/list.o ${OBJECTDIR}/src/main.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/SimpleSheduler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/low-level/board.o: src/low-level/board.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/low-level 
	@${RM} ${OBJECTDIR}/src/low-level/board.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/low-level/board.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/low-level" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/os" -MMD -MF "${OBJECTDIR}/src/low-level/board.o.d" -o ${OBJECTDIR}/src/low-level/board.o src/low-level/board.c   
	
${OBJECTDIR}/src/low-level/serial.o: src/low-level/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/low-level 
	@${RM} ${OBJECTDIR}/src/low-level/serial.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/low-level/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/low-level" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/os" -MMD -MF "${OBJECTDIR}/src/low-level/serial.o.d" -o ${OBJECTDIR}/src/low-level/serial.o src/low-level/serial.c   
	
${OBJECTDIR}/src/low-level/timer.o: src/low-level/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/low-level 
	@${RM} ${OBJECTDIR}/src/low-level/timer.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/low-level/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/low-level" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/os" -MMD -MF "${OBJECTDIR}/src/low-level/timer.o.d" -o ${OBJECTDIR}/src/low-level/timer.o src/low-level/timer.c   
	
${OBJECTDIR}/src/os/jobs.o: src/os/jobs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/os 
	@${RM} ${OBJECTDIR}/src/os/jobs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/os/jobs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/low-level" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/os" -MMD -MF "${OBJECTDIR}/src/os/jobs.o.d" -o ${OBJECTDIR}/src/os/jobs.o src/os/jobs.c   
	
${OBJECTDIR}/src/os/list.o: src/os/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/os 
	@${RM} ${OBJECTDIR}/src/os/list.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/os/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/low-level" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/os" -MMD -MF "${OBJECTDIR}/src/os/list.o.d" -o ${OBJECTDIR}/src/os/list.o src/os/list.c   
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/low-level" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/os" -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c   
	
else
${OBJECTDIR}/src/low-level/board.o: src/low-level/board.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/low-level 
	@${RM} ${OBJECTDIR}/src/low-level/board.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/low-level/board.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/low-level" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/os" -MMD -MF "${OBJECTDIR}/src/low-level/board.o.d" -o ${OBJECTDIR}/src/low-level/board.o src/low-level/board.c   
	
${OBJECTDIR}/src/low-level/serial.o: src/low-level/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/low-level 
	@${RM} ${OBJECTDIR}/src/low-level/serial.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/low-level/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/low-level" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/os" -MMD -MF "${OBJECTDIR}/src/low-level/serial.o.d" -o ${OBJECTDIR}/src/low-level/serial.o src/low-level/serial.c   
	
${OBJECTDIR}/src/low-level/timer.o: src/low-level/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/low-level 
	@${RM} ${OBJECTDIR}/src/low-level/timer.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/low-level/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/low-level" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/os" -MMD -MF "${OBJECTDIR}/src/low-level/timer.o.d" -o ${OBJECTDIR}/src/low-level/timer.o src/low-level/timer.c   
	
${OBJECTDIR}/src/os/jobs.o: src/os/jobs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/os 
	@${RM} ${OBJECTDIR}/src/os/jobs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/os/jobs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/low-level" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/os" -MMD -MF "${OBJECTDIR}/src/os/jobs.o.d" -o ${OBJECTDIR}/src/os/jobs.o src/os/jobs.c   
	
${OBJECTDIR}/src/os/list.o: src/os/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/os 
	@${RM} ${OBJECTDIR}/src/os/list.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/os/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/low-level" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/os" -MMD -MF "${OBJECTDIR}/src/os/list.o.d" -o ${OBJECTDIR}/src/os/list.o src/os/list.c   
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/low-level" -I"C:/Users/Dan/Projects/Electronics/PIC/SimpleSheduler.X/include/os" -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/SimpleSheduler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SimpleSheduler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=10240
else
dist/${CND_CONF}/${IMAGE_TYPE}/SimpleSheduler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SimpleSheduler.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=10240
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/SimpleSheduler.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
