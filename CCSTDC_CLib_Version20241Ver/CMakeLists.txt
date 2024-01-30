if(${CMAKE_VERSION} VERSION_LESS 3.24)
    cmake_minimum_required(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
    message(STATUS "version less 3.24, switch to ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}")
else()
    cmake_minimum_required(VERSION 3.24)
    message(STATUS "version is good, no need to switch")
endif()

project	(CUtilityLibs
        	VERSION 1.0
        	DESCRIPTION "A demo for Abs factory")

SET(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_INSTALL_PREFIX "./install")
message(
    STATUS 
    "Ready to config the project:> ${PROJECT_NAME}\n
     The Project Version is ${PROJECT_VERSION}\n
     Project descriptions are follows:> ${PROJECT_DESCRIPTION}\n
     Build start\n\n\n"
)


message("will set the project source dir in:> ${PROJECT_SOURCE_DIR}\n")
include_directories(${PROJECT_SOURCE_DIR}/include)

file(
    GLOB_RECURSE mySource    
    ${PROJECT_SOURCE_DIR}/*.c
)

message("Find Sources:> ${mySource}")

file(
    GLOB_RECURSE myHeader  
    ${PROJECT_SOURCE_DIR}/include/*.h
)
message("Find headers:> ${myHeader}")


message("About ready to config the static lib")
add_library(CUtilsLib STATIC ${mySource})
message("About ready to config the dynamic lib")
add_library(CUtilsLibDynamic SHARED ${mySource})


# 注意现在变成相对跟目录在build下讨论
# 安装在../install/lib下
install(TARGETS CUtilsLib DESTINATION lib)
# 安装在../install/bin下
install(TARGETS CUtilsLibDynamic  DESTINATION bin)
# 安装在../install/include下
install(FILES ${myHeader} DESTINATION include)