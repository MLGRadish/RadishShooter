#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/")

# Add source and header files
file(GLOB HDRS "*.h")
file(GLOB SRCS "*.cpp")

# Create a library called "SaltedRadish".
# The extension is already found. Any number of sources could be listed here.
add_library (ImGui ${HDRS} ${SRCS})

# Make sure the compiler can find include files for our SaltedRadish library
# when other libraries or executables link to SaltedRadish
target_include_directories (ImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})