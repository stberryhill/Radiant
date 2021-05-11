cmake_minimum_required(VERSION 3.0.0)
project(Radiant VERSION 0.0.1)

# Set default visibility to hidden (only functions bearing Radiant_API will be exported)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

option(BUILD_SHARED_LIBS "Build shared library" ON)
include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# Set intall RPATH info for library.
if (NOT APPLE)
  set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

set(openglImplementation
  src/opengl/GpuProgram.c
  src/opengl/Input.c
  src/opengl/Internal_Opengl.h
  src/opengl/Video.c
  src/opengl/Internal_KeyDefines.h
  )


set(linuxSources
  src/linux/Clock.c
  )

set(windowsSources )

set(macSources
  src/mac/Clock.c
  )

set(platformDependentSources )
if (LINUX)
  list(APPEND platformDependentSources ${linuxSources})
endif(LINUX)

if (WIN32)
  list(APPEND platformDependentSources ${windowsSources})
endif(WIN32)

if (APPLE)
  list(APPEND platformDependentSources ${macSources})
endif(APPLE)

add_library(${PROJECT_NAME} SHARED
  src/BBox.c
  src/Button.c
  src/Internal.h
  src/Internal_Physics.h
  src/LinkedBBoxList.c
  src/Math_Fast.c
  src/Math_Utils.c
  src/Matrix4f.c
  src/MatrixMNf.c
  src/MatrixNf.c
  src/Physics.c
  src/PhysicsMaterial.c
  src/Radiant.c
  src/RadiantEvent.c
  src/Vector2f.c
  src/Vector3f.c
  src/Vector4f.c
  src/String.c
  src/Clock.c
  src/Internal_Time.h
  src/Internal_Logger.h
  src/Logger.c
  src/Internal_File.h
  src/File.c
  ${openglImplementation}
  ${platformDependentSources}
  )

# Allows to use in a subdirectory (and in examples)
add_library(Radiant::Radiant ALIAS Radiant)


find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(Radiant
  OpenGL
  glfw
)

generate_export_header(Radiant
  EXPORT_MACRO_NAME RADIANT_API
  EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/include/RadiantAPIMacro.h
  )

target_include_directories(Radiant
  PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/opengl>
  )

# Make shared lib version follow project version.
set_target_properties(Radiant PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/RadiantConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/RadiantConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Radiant
  PATH_VARS
    CMAKE_INSTALL_LIBDIR
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/RadiantConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(TARGETS Radiant
  EXPORT RadiantTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT Radiant_Development
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT Radiant_Runtime
    NAMELINK_COMPONENT Radiant_Development
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT Radiant_Runtime
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# install(FILES ${publicHeaders} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
  
install(EXPORT RadiantTargets
  FILE RadiantTargets.cmake
  COMPONENT Radiant_Development
  NAMESPACE Radiant::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Radiant
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/RadiantConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/RadiantConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Radiant
)

add_subdirectory(examples)
