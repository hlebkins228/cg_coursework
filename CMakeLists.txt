cmake_minimum_required(VERSION 3.20)

# Название вашего проекта
project(App)

# Установка стандартов C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Задаем свои ключи компиляции
option(COMP_KEYS "Включает ключи компиляции -Wall -Werror -Wpedantic" OFF)

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# заголовочные файлы приложения
include_directories(./inc)

file(GLOB_RECURSE SOURCES "./src/*.cpp")

# Создать исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})     # WIN 32 указывает, что приложение графическое, а не консольное

target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

# опции компиляции
if (COMP_KEYS)
    if (MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()
endif()


#   --- Конфигурация desktop ---
# cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/Libs/Sources/vcpkg-2024.09.23/scripts/buildsystems/vcpkg.cmake

#   --- Конфигурация laptop ---
# cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/Libs/vcpkg/scripts/buildsystems/vcpkg.cmake

#   ---    Сборка    ---
# cmake --build build