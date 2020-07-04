cmake_minimum_required( VERSION 3.12 FATAL_ERROR )
set( CMAKE_CXX_STANDARD 11 )

project( naive-bayes )

get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE )

include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

ci_make_app(
    APP_NAME    naive-bayes-app
    CINDER_PATH ${CINDER_PATH}
    SOURCES     ${APP_PATH}/app/app.cpp ${APP_PATH}/src/sketchpad.cpp
)

ci_make_app(
    APP_NAME    naive-bayes-test
    CINDER_PATH ${CINDER_PATH}
    SOURCES     ${APP_PATH}/tests/test.cpp ${APP_PATH}/src/sketchpad.cpp
)

if(WIN32)
    set_property(TARGET test APPEND_STRING PROPERTY LINK_FLAGS " /SUBSYSTEM:CONSOLE")
endif()
