cmake_minimum_required(VERSION 2.8.3)
project(qt_restore_state_orientation)

find_package(Qt REQUIRED COMPONENTS QtCore QtGui)

set(sources main.cpp qt_restore_state_orientation.cpp)
set(headers qt_restore_state_orientation.h)

qt4_wrap_cpp(mocs ${headers})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

include_directories(${QT_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${sources} ${mocs})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})
