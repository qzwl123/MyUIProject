# 定义一个静态库，名字叫 MyUI
qt_add_library(MyUI STATIC)

# =========================================================
# 【必须放在第一行！】
# 在定义模块之前，先告诉 CMake：Theme.qml 是个单例
# =========================================================
set_source_files_properties(Theme.qml
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE
)

set_source_files_properties(Icons.qml
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE)


# 【核心】将这个库定义为 QML 模块
qt_add_qml_module(MyUI
    URI "MyCompany.UI"        # 以后在 QML 里 import 这个名字
    VERSION 1.0
    RESOURCE_PREFIX "/qt/qml" # 资源在内存中的虚拟路径前缀
    QML_FILES        
        Theme.qml           # 包含样式文件
        Icons.qml

        controls/Button.qml
        controls/TextBox.qml

    RESOURCES
        fonts/FluentIcons.ttf
)



# 链接 Qt Quick 基础库
target_link_libraries(MyUI PRIVATE Qt6::Quick)

