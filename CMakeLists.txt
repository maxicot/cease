cmake_minimum_required(VERSION 3.14)
project(cease VERSION 0.1.0)

add_library(cease src/lib.c)

target_include_directories(
    cease
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(cease PUBLIC c_std_23)

set_target_properties(
    cease PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

include(GNUInstallDirs)

install(
    TARGETS cease
    EXPORT cease-targets
)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT cease-targets
    FILE cease-targets.cmake
    NAMESPACE cease::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cease
)
