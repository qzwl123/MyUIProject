# 定义可执行文件
qt_add_executable(GalleryAppBin
    main.cpp    
    backend/GrpcTest.cpp
)

qt_add_protobuf(GalleryAppBin
    PROTO_FILES
        ${CMAKE_SOURCE_DIR}/protos/stream.proto
)

qt_add_grpc(GalleryAppBin CLIENT
    PROTO_FILES
        ${CMAKE_SOURCE_DIR}/protos/stream.proto
)

# 将 GalleryApp 也定义为 QML 模块 (这是 Qt6 的最佳实践)
qt_add_qml_module(GalleryAppBin
    URI "GalleryApp"
    VERSION 1.0
    RESOURCE_PREFIX "/qt/qml"
    QML_FILES
        Main.qml
        pages/IconBrowser.qml
        pages/PageHome.qml
        pages/PageIcons.qml    
        SOURCES backend/GrpcClient.h backend/GrpcClient.cpp  # ✨ 把源码加到这里，让 QML 模块识别
)

target_include_directories(GalleryAppBin PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backend
)

# 【关键】链接我们的 UI 库
# 只要链接了 MyUI，CMake 会自动处理所有的 import 路径
target_link_libraries(GalleryAppBin
    PRIVATE
    Qt6::Quick
    Qt6::Protobuf
    Qt6::Grpc
    MyUI
    MyUIplugin
)

