cmake_minimum_required(VERSION 3.20)

project(MyUIProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

find_package(Qt6 REQUIRED COMPONENTS Protobuf Grpc)

# find_package(Qt6ProtobufTools REQUIRED)
# find_package(Qt6Protobuf REQUIRED)
# find_package(Qt6Grpc REQUIRED)
qt_standard_project_setup()
add_custom_target(ProtoFiles SOURCES protos/stream.proto)

# 只做这两件事：添加子目录
add_subdirectory(src)
add_subdirectory(gallery)
