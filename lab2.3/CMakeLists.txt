cmake_minimum_required(VERSION 3.15) # Проверка версии CMake.
									 # Если версия установленой программы
									 # старее указаной, произайдёт аварийный выход.

set(PROJECT_NAME lab2.3) 			 # задать значение PROJECT_NAME		 
project("${PROJECT_NAME}")           # установить имя проекта


set(CMAKE_CXX_STANDARD 20)			 # устанавливаем 17 стандарт языка

# Сказать программе, что должен быть исполняемый файл
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# СОЗДАЕМ БИБЛИОТЕКУ (НОВОЕ)
add_library(country_lib 
    src/country_lib.cpp
)

# Указываем где искать заголовочные файлы для библиотеки (НОВОЕ)
target_include_directories(country_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# СОЗДАЕМ ИСПОЛНЯЕМЫЙ ФАЙЛ
add_executable("${PROJECT_NAME}" 
    main.cpp
    Country.cpp
)

# СВЯЗЫВАЕМ С БИБЛИОТЕКОЙ (НОВОЕ)
target_link_libraries("${PROJECT_NAME}" PRIVATE country_lib)

# Добавляем путь к include для исполняемого файла (НОВОЕ)
target_include_directories("${PROJECT_NAME}" PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)