cmake_minimum_required(VERSION 3.16)

project(IpValidatorUI VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt5Charts)

add_executable(IpValidatorUI /
IWantToDie.pro
ButtonsCLS.cpp
PlotNetCLS.cpp
ButtonsServerCLS.cpp
ipEndPoint.cpp
main.cpp
NetWorkCLS.cpp
Package.cpp
ServerInit.cpp
ServerRunnerCLS.cpp
SocketCLS.cpp
TableCLS.cpp
TableCLS.cpp
ValidatorCLS.cpp
ButtonsCLS.h
PlotNetCLS.h
ButtonsServerCLS.h
ConstantCLS.h
includeMe.h
ipEndPoint.h
ipVersion.h
NetWorkCLS.h
Package.h
PackageExtenntionCLS.h
PackageType.h
PResultCLS.h
ServerWidget.h
SocketCLS.h
SocketHandle.h
SocketOptions.h
TableCLS.h
ValidatorCLS.h
)

target_link_libraries(IpValidatorUI PRIVATE Qt5::Widgets Qt5::Charts)
set_target_properties(IpValidatorUI PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
