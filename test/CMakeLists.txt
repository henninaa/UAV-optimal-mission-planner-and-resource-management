cmake_minimum_required(VERSION 3.0)
project(test CXX)
#add_definitions(_GLIBCXX_USE_C99 1)

if (NOT TARGET ampl)
  # Check for C++11 support.
  #include(cxx11.cmake)
  # Create an imported ampl target.
  set(AMPLAPI_DIR /home/henning/Documents/prosjektet/ampl/amplapi/)
  set(CMAKE_INSTALL_RPATH ${AMPLAPI_DIR}/lib)
  set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
  add_library(ampl STATIC IMPORTED)
  find_library(AMPL_LIBRARY ampl PATHS ${CMAKE_INSTALL_RPATH})
  set_target_properties(ampl PROPERTIES
    IMPORTED_LOCATION ${AMPL_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${AMPLAPI_DIR}/include)
endif ()

#set(SOURCES )
file(GLOB SOURCES "*.cpp")

include_directories(${AMPLAPI_DIR}/include)
include_directories(.)



include(CMakeParseArguments)

add_executable(testF ${SOURCES})
target_link_libraries(testF ampl)
#target_compile_options(${SOURCES} PRIVATE ${CXX11_FLAG})

target_compile_features(testF PRIVATE cxx_range_for)