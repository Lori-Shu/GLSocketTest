set(glIncludeDirs ${PROJECT_SOURCE_DIR}/include)

include_directories(${glIncludeDirs})

file(GLOB clientcpp  
${PROJECT_SOURCE_DIR}/src/GLSocketClient.cpp
${PROJECT_SOURCE_DIR}/src/ClientApp.cpp
)

file(GLOB servercpp  
${PROJECT_SOURCE_DIR}/src/GLSocketServer.cpp
${PROJECT_SOURCE_DIR}/src/ServerApp.cpp
${PROJECT_SOURCE_DIR}/src/GGLSelectMultiIO.cpp
${PROJECT_SOURCE_DIR}/src/GGLThreadPool.cpp
)


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


# SET(CMAKE_CXX_FLAGS_DEBUG "-fexec-charset=UTF-8")
add_executable(${PROJECT_NAME}Client ${clientcpp})

target_link_libraries(${PROJECT_NAME}Client ws2_32)

add_executable(${PROJECT_NAME}Server ${servercpp})
target_link_libraries(${PROJECT_NAME}Server ws2_32)