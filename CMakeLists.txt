cmake_minimum_required(VERSION 3.16)

project(TeDa VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Нахождение пакета Qt и подключение нужных компонентов
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql Widgets)

# Исходные файлы проекта
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

# Создание исполнимого файла
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TeDa
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        user.h user.cpp
        inputdialog.h inputdialog.cpp


    )
else()
    if(ANDROID)
        add_library(TeDa SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(TeDa
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Связывание с библиотеками Qt
target_link_libraries(TeDa PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Widgets)

# Задайте пути к установленным OpenSSL библиотекам и заголовкам
set(OPENSSL_ROOT_DIR "C:/openssl-output") # Укажите правильный путь!
set(OPENSSL_INCLUDE_DIR "C:/openssl-output/include") # Директория с заголовочными файлами
set(OPENSSL_LIBRARIES "C:/openssl-output/lib64") # Библиотеки OpenSSL

# Далее находим OpenSSL
find_package(OpenSSL REQUIRED)
target_link_libraries(TeDa PRIVATE ${OPENSSL_LIBRARIES})

# Настройки целевого свойства для iOS/macOS/Android
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TeDa)
endif()
set_target_properties(TeDa PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Установка приложения
include(GNUInstallDirs)
install(TARGETS TeDa
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Финальизация для Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TeDa)
endif()
