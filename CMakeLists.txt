cmake_minimum_required(VERSION 3.16)

project(TeDa VERSION 0.1 LANGUAGES CXX)

# Настройка автоматической генерации Meta Object Compiler (moc), UI-компонентов (uic) и ресурсов (rcc)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск модулей Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Sql Widgets Network)

# Источники проекта
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    user.h
    user.cpp
    inputdialog.h
    inputdialog.cpp
)

# Генерация приложения с помощью команд Qt6
qt_add_executable(TeDa
    ${PROJECT_SOURCES}
)

# Подключение библиотек Qt6
target_link_libraries(TeDa PRIVATE Qt6::Core Qt6::Sql Qt6::Widgets Qt6::Network)

# Конфигурация OpenSSL (если требуется поддержка SSL/TLS)
set(OPENSSL_ROOT_DIR "C:/openssl-output")
set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
set(OPENSSL_LIBRARIES "${OPENSSL_ROOT_DIR}/lib64")

find_package(OpenSSL REQUIRED)
target_link_libraries(TeDa PRIVATE OpenSSL::Crypto OpenSSL::SSL)

# Свойства приложения
if(Qt6_VERSION VERSION_LESS 6.1.0)
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

# Завершаем сборку с помощью специальной команды Qt6
qt_finalize_executable(TeDa)
