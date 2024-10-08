#Variables
#-----------------------------------------------------------------------------------------
set(PROJ_NAME CLogicSim)
set(MAJOR_VER 0)
set(MINOR_VER 1)
#-----------------------------------------------------------------------------------------

#Setup
#-----------------------------------------------------------------------------------------
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_minimum_required(VERSION 3.18)
project(${PROJ_NAME} LANGUAGES C CXX)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
file(STRINGS "./build.nr" BUILD_NUMBER)
#-----------------------------------------------------------------------------------------

message("** Building ${PROJ_NAME} ${MAJOR_VER}.${MINOR_VER}.${BUILD_NUMBER}")

#Sources
#-----------------------------------------------------------------------------------------
list(APPEND INCLUDE_DIRS
	${CMAKE_CURRENT_LIST_DIR}/src
)
list(APPEND SOURCE_FILES
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/BaseComponent.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/MainWindow.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ComponentManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Global.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Board.cpp
)
#-----------------------------------------------------------------------------------------

#Targets
#-----------------------------------------------------------------------------------------
set(RUNTIME_TARGET CLogicSim)
add_executable(${RUNTIME_TARGET} ${SOURCE_FILES})
target_include_directories(${RUNTIME_TARGET} PUBLIC ${INCLUDE_DIRS})

target_compile_definitions(${RUNTIME_TARGET} PUBLIC  BUILD_NR=${BUILD_NUMBER} MAJ_V=${MAJOR_VER} MIN_V=${MINOR_VER} VERSION_STR="${MAJOR_VER}.${MINOR_VER}.${BUILD_NUMBER}")

#TODO: Different flags for Release/Debug
add_compile_options(-O3 -m32 -MMD -MP -Wall -ggdb)
if (UNIX)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'$ORIGIN',-rpath,/usr/lib"					)
	target_link_libraries(${RUNTIME_TARGET} xcb xcb-randr boost_regex)
endif (UNIX)
if (WIN32)
	target_link_libraries(${RUNTIME_TARGET} mingw32)
endif (WIN32)
target_link_libraries(${RUNTIME_TARGET} SDL2main SDL2)
#-----------------------------------------------------------------------------------------

#Linking 
#-----------------------------------------------------------------------------------------
target_link_libraries(${RUNTIME_TARGET} ostd)
target_link_libraries(${RUNTIME_TARGET} ogfx)
#-----------------------------------------------------------------------------------------

add_custom_command(TARGET ${RUNTIME_TARGET} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/extra/ $<TARGET_FILE_DIR:${RUNTIME_TARGET}>
	VERBATIM
)
