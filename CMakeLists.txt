cmake_minimum_required(VERSION 3.29)
project(C_serverAPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/pavel/Qt/6.7.2/gcc_64/lib/cmake/Qt6")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(C_serverAPP
        src/main.cpp
        src/lib/server/Server.cpp
        src/lib/server/Server.h
        src/lib/client/Client.cpp
        src/lib/client/Client.h
        src/lib/ui/mainwindow/mainwindow.cpp
        src/lib/ui/mainwindow/mainwindow.h
        src/lib/ui/mainwindow/mainwindow.ui
        src/lib/ui/clientgui/clientgui.cpp
        src/lib/ui/clientgui/clientgui.h
        src/lib/ui/clientgui/clientgui.ui
        src/lib/ui/servergui/servergui.cpp
        src/lib/ui/servergui/servergui.h
        src/lib/ui/servergui/servergui.ui
        src/lib/server_thread/server_thread.cpp
        src/lib/server_thread/server_thread.h
        src/lib/client_thread/client_thread.cpp
        src/lib/client_thread/client_thread.h
)
target_link_libraries(C_serverAPP
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

