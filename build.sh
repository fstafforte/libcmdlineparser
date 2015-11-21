#!/bin/bash

EXIT_STR="Exit"
PREVIOUS_STR="Previous"
ALL_STR="All"
COMPILE_STR=Compile
CLEAN_STR=Clean


STATIC_LIBFMT="Static"
SHARED_LIBFMT="Shared"

BUILD_TYPE_DEBUG="Debug"
BUILD_TYPE_RELEASE="Release"

PS3="Choose: "

DEFAULT_INSTALLATION_PREFIX=/usr/local
INSTALL_FLAG=0

function menu() {
local MENU_ITEM=""
select MENU_ITEM in $@
do
        echo $MENU_ITEM
        return 0
done
}


function yes_or_no() {
local PROMPT=$1
local ANSWER='?'

  while [ "${ANSWER}" != 'n' ]  && [ "${ANSWER}" != 'y' ]
  do
    echo -n ${PROMPT}
    read
    ANSWER=`echo ${REPLY} | tr [A-Z] [a-z]`
    [ "${ANSWER}" == "" ] && ANSWER='n'
  done

  [ "${ANSWER}" == 'y' ] && return 1
  return 0 
}

function lib_install_selection() {
  yes_or_no "Would you like to install too [N/y]:"
  INSTALL_FLAG=$?
  if [ ${INSTALL_FLAG} -ne 0 ]; then
    echo -n "Enter the installation directory [${DEFAULT_INSTALLATION_PREFIX}]:"
    read
    INSTALLATION_PREFIX=${REPLY}
    [ "${INSTALLATION_PREFIX}" == "" ] && INSTALLATION_PREFIX=${DEFAULT_INSTALLATION_PREFIX}
    [ ! -d ${INSTALLATION_PREFIX} ] && echo "${INSTALLATION_PREFIX} no such a directory or it does not exist" && exit -1
    [ ! -w ${INSTALLATION_PREFIX} ] && echo "you don't have the permission to install in '${INSTALLATION_PREFIX}' directory" && exit -1
  fi
}


function lib_format_selection() {
local MENU_ITEMS="${EXIT_STR} ${STATIC_LIBFMT} ${SHARED_LIBFMT} ${ALL_STR}"
  SELECTED_LIBFMT=`menu ${MENU_ITEMS}`
}

function lib_command_selection() {
local MENU_ITEMS="${EXIT_STR} ${PREVIOUS_STR} ${COMPILE_STR} ${CLEAN_STR}"
  SELECTED_COMMAND=`menu ${MENU_ITEMS}`
  [ "${SELECTED_COMMAND}" == ${COMPILE_STR} ] && lib_install_selection 
}

function build_type_selection() {
local MENU_ITEMS="${EXIT_STR} ${PREVIOUS_STR} ${BUILD_TYPE_DEBUG} ${BUILD_TYPE_RELEASE} ${ALL_STR}"
  SELECTED_BUILD_TYPE=`menu ${MENU_ITEMS}`
}



function do_build() {
local L_SELECTED_LIBFMT=$1
local L_SELECTED_BUILD_TYPE=$2
local L_SELECTED_COMMAND=$3
local MAKEFILENAME="Makefile.$L_SELECTED_LIBFMT.$L_SELECTED_BUILD_TYPE"

      cmake -DCMAKE_INSTALL_PREFIX=${INSTALLATION_PREFIX} -DLIBFMT=${L_SELECTED_LIBFMT} -DCMAKE_BUILD_TYPE=${L_SELECTED_BUILD_TYPE} CMakeLists.txt
      [ $? -ne 0 ] && exit $?
      L_SELECTED_LIBFMT=`echo $1 | tr [A-Z] [a-z]`
      L_SELECTED_BUILD_TYPE=`echo $2 | tr [A-Z] [a-z]`
      MAKEFILENAME="Makefile.$L_SELECTED_LIBFMT.$L_SELECTED_BUILD_TYPE"
      mv Makefile ${MAKEFILENAME}
      make -f ${MAKEFILENAME} ${L_SELECTED_COMMAND}
      [ $? -ne 0 ] && exit $?
      rm Makefile
      [ ${INSTALL_FLAG} -ne 0 ] && make -f ${MAKEFILENAME} install
}


LOOP=1

while [ $LOOP -eq 1 ]
do
  lib_format_selection
  [ ${SELECTED_LIBFMT} == ${EXIT_STR} ] && exit 0  

  lib_command_selection
  [ ${SELECTED_COMMAND} == ${EXIT_STR} ] && exit 0

  if [ ${SELECTED_COMMAND} != ${PREVIOUS_STR} ]; then
    build_type_selection
    [ ${SELECTED_BUILD_TYPE} == ${EXIT_STR} ] && exit 0
  
    [ ${SELECTED_COMMAND} == ${COMPILE_STR} ] && SELECTED_COMMAND=${ALL_STR}
    SELECTED_COMMAND=`echo ${SELECTED_COMMAND} | tr [A-Z] [a-z]`
  

    if [ ${SELECTED_LIBFMT} == ${ALL_STR} ]; then
      if [ ${SELECTED_BUILD_TYPE} == ${ALL_STR} ]; then
        do_build STATIC Debug ${SELECTED_COMMAND}
        do_build STATIC Release ${SELECTED_COMMAND}
        do_build SHARED Debug ${SELECTED_COMMAND}
        do_build SHARED Release ${SELECTED_COMMAND}
      else
        do_build STATIC ${SELECTED_BUILD_TYPE} ${SELECTED_COMMAND}
        do_build SHARED ${SELECTED_BUILD_TYPE} ${SELECTED_COMMAND} 
      fi
    else 
      SELECTED_LIBFMT=`echo ${SELECTED_LIBFMT} | tr [a-z] [A-Z]`
      if [ ${SELECTED_BUILD_TYPE} == ${ALL_STR} ]; then
        do_build ${SELECTED_LIBFMT} Debug ${SELECTED_COMMAND}
        do_build ${SELECTED_LIBFMT} Release ${SELECTED_COMMAND}
      else  
        do_build ${SELECTED_LIBFMT} ${SELECTED_BUILD_TYPE} ${SELECTED_COMMAND}
      fi
    fi
  fi
done







