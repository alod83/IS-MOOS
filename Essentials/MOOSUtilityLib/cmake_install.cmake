# Install script for directory: /home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Essentials/MOOSUtilityLib

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/include/MOOSUtilityLib" TYPE FILE FILES
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Essentials/MOOSUtilityLib/MOOSTerrain.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Essentials/MOOSUtilityLib/ScalarPID.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Essentials/MOOSUtilityLib/PitchZPID.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Essentials/MOOSUtilityLib/MOOSGeodesy.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Essentials/MOOSUtilityLib/ThirdPartyRequest.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Essentials/MOOSUtilityLib/MOOSTimeJournal.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Essentials/MOOSUtilityLib/InterpBuffer.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Essentials/MOOSUtilityLib/MOOSThread.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Essentials/MOOSUtilityLib/MOOSThreadedTimeJournal.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Essentials/MOOSUtilityLib/TMaxPair.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Essentials/MOOSUtilityLib/TMinPair.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Essentials/MOOSUtilityLib/MOOSMemoryMapped.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/lib" TYPE STATIC_LIBRARY FILES "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/MOOSBin/libMOOSUtility.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

