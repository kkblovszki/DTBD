# Install script for directory: /mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.38-wave-debug.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.38-wave-debug.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.38-wave-debug.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/build/lib/libns3.38-wave-debug.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.38-wave-debug.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.38-wave-debug.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.38-wave-debug.so"
         OLD_RPATH "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/build/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.38-wave-debug.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ns3" TYPE FILE FILES
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave/helper/wave-bsm-helper.h"
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave/helper/wave-bsm-stats.h"
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave/helper/wave-helper.h"
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave/helper/wave-mac-helper.h"
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave/helper/wifi-80211p-helper.h"
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave/model/bsm-application.h"
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave/model/channel-coordinator.h"
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave/model/channel-manager.h"
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave/model/channel-scheduler.h"
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave/model/default-channel-scheduler.h"
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave/model/higher-tx-tag.h"
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave/model/ocb-wifi-mac.h"
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave/model/vendor-specific-action.h"
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave/model/vsa-manager.h"
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave/model/wave-frame-exchange-manager.h"
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/src/wave/model/wave-net-device.h"
    "/mnt/c/Users/Mikkel/Documents/GitHub/DTBD/SMIs/NS3-SMI/ns-3.38/ns-3.38/build/include/ns3/wave-module.h"
    )
endif()

