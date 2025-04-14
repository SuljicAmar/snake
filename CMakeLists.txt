cmake_minimum_required(VERSION 3.10)
project(snake)

set(CMAKE_CXX_STANDARD 17)


#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

include_directories("${CMAKE_SOURCE_DIR}/include")

include_directories("/usr/local/include")

link_directories("/usr/local/lib")

set(SDL3_LIBRARIES "-lSDL3")
set(SDL3_TTF_LIBRARIES "-lSDL3_ttf")
set(SDL3_MIXER_LIBRARIES "-lSDL3_mixer")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include")

add_executable(main ${SRC_FILES})

target_link_libraries(main PRIVATE ${SDL3_LIBRARIES} ${SDL3_TTF_LIBRARIES} ${SDL3_MIXER_LIBRARIES})

set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/main
    DEPENDS main
    COMMENT "Running the program..."
)

add_dependencies(run main)
