cmake_minimum_required (VERSION 3.5)
project (RadishShooter)

# Add source and header files
file (GLOB HDRS "*.h")
file (GLOB SRCS "*.cpp")
file (GLOB PROTOS "*.proto")

find_package (OpenGL REQUIRED OpenGL)
find_package (GLEW REQUIRED)

# Add executable called "RadishShooter" that is built from the source files.
add_executable (RadishShooter ${HDRS} ${SRCS} ${PROTOS})
# Link the executable to the SaltedRadish library
target_link_libraries (RadishShooter LINK_PUBLIC SaltedRadish ImGui OpenGL::GL GLEW::glew)
include_directories (RadishShooter ${CMAKE_CURRENT_BINARY_DIR})
