# Install script for directory: /home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB

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
  FILE(INSTALL DESTINATION "/usr/local/include/MOOSLIB" TYPE FILE FILES
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/MOOSVariable.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/MOOSCommClient.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/MOOSCommObject.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/MOOSCommPkt.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/MOOSCommServer.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/MOOSException.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/MOOSGlobalHelper.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/MOOSLib.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/MOOSMsg.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/MOOSApp.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/MOOSInstrument.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/XPCEndian.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/XPCException.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/XPCGetHostInfo.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/XPCGetProtocol.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/XPCSocket.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/XPCTcpSocket.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/XPCUdpSocket.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/MOOSSecurity.h"
    "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/Core/MOOSLIB/MOOSPortsManager.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/lib" TYPE STATIC_LIBRARY FILES "/home/isme/Desktop/UAN/MOOS/SecMOOS_v1.8/MOOSBin/libMOOS.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

