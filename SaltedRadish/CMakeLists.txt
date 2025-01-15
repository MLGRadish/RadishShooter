# Add source and header files
file(GLOB HDRS "*.h")
file(GLOB SRCS "*.cpp")

find_package(SDL2 REQUIRED)
find_package (OpenGL REQUIRED OpenGL)
find_package (GLEW REQUIRED)

# Create a library called "SaltedRadish".
add_library (SaltedRadish ${HDRS} ${SRCS})

# Make sure the compiler can find include files for our SaltedRadish library
target_include_directories (SaltedRadish PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(SaltedRadish enet SDL2::SDL2 OpenGL::GL GLEW::glew)