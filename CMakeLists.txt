cmake_minimum_required(VERSION 3.10)
project(snake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

# Collect all source files
file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Include the include directory for header files
include_directories("${CMAKE_SOURCE_DIR}/include")

# Manually add the SDL3 and SDL3_ttf include directories
include_directories("/usr/local/include")

# Manually specify the SDL3 and SDL3_ttf libraries
link_directories("/usr/local/lib")

# Manually add the required SDL3 and SDL3_ttf flags
set(SDL3_LIBRARIES "-lSDL3")
set(SDL3_TTF_LIBRARIES "-lSDL3_ttf")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include")

# Create the executable
add_executable(main ${SRC_FILES})

# Link libraries for SDL3 and SDL3_ttf
target_link_libraries(main PRIVATE ${SDL3_LIBRARIES} ${SDL3_TTF_LIBRARIES})

# Set output directory (no subdirectory)
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# Add custom target to run the executable after building
add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/main
    DEPENDS main
    COMMENT "Running the program..."
)

# Ensure the 'run' target is executed after 'all' target
add_dependencies(run main)
