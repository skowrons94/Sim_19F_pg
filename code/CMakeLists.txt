#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
#set(CMAKE_INSTALL_PREFIX "./" FORCE)
project(SimLUNA)
IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX "./" CACHE PATH "" FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Find ROOT (required package)
#
find_package(ROOT REQUIRED)

# ROOT version 6 required
if(ROOT_FOUND)
  STRING(REGEX MATCH "6.*" VERSION6MATCH ${ROOT_VERSION})
  if(NOT VERSION6MATCH)
    message(FATAL_ERROR "SimLUNA requires ROOT 6")
  endif()
endif()

#----------------------------------------------------------------------------
# SimLUNA requires shared libraries
#
if(NOT Geant4_shared_FOUND)
  message(FATAL_ERROR "SimLUNA must use shared libraries")
endif()

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list FOLLOW_SYMLINKS *.hh)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
	GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
	SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(header_list)

list(LENGTH header_list header_list_count)
message(STATUS "[INFO] Found ${header_list_count} header directories.")

FOREACH(I IN LISTS header_list)
  message(STATUS "[INFO] Found ${I} header directory.")
ENDFOREACH()


include_directories(${header_list} ${Geant4_INCLUDE_DIR} ${ROOT_INCLUDE_DIRS})

file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR} FOLLOW_SYMLINKS *.cc)
file(GLOB_RECURSE headers ${PROJECT_SOURCE_DIR} FOLLOW_SYMLINKS *.hh)


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(SimLUNA SimLUNA.cc ${sources} ${headers})
target_link_libraries(SimLUNA ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

install(DIRECTORY DESTINATION rootfiles)
install(DIRECTORY DESTINATION ER)
install(DIRECTORY DESTINATION OU)
