cmake_minimum_required (VERSION 3.5)
project (RadishShooter CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory (RadishShooter)
add_subdirectory (SaltedRadish)
add_subdirectory (ImGui)
add_subdirectory (ENet)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})
