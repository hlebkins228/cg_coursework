cmake_minimum_required(VERSION 3.20)

# Название вашего проекта
project("triangle")

# Установка стандартов C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

set(SOURCES "triangle.cpp")

# Создать исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})     # WIN 32 указывает, что приложение графическое, а не консольное

target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)

#   --- Конфигурация desktop ---
# cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/Libs/Sources/vcpkg-2024.09.23/scripts/buildsystems/vcpkg.cmake

#   --- Конфигурация laptop ---
# cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=D:/Libs/vcpkg/scripts/buildsystems/vcpkg.cmake

#   ---    Сборка    ---
# cmake --build build