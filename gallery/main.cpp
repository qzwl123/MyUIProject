// 调试专用 main.cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDirIterator>
#include <QDebug>

// #include "backend/GrpcClient.h" // 引入头文件

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // qmlRegisterType<GrpcClient>("MyCompany.Network", 1, 0, "GrpcClient");

    // --- 侦探代码 ---
    qDebug() << "=== 开始扫描内存资源 ===";
    QDirIterator it(":", QDirIterator::Subdirectories);
    bool foundMyUI = false;
    while (it.hasNext()) {
        QString path = it.next();
        // 过滤一下，只看相关的
        if (path.contains("MyCompany")) {
            qDebug() << "发现资源:" << path;
            foundMyUI = true;
        }
    }
    qDebug() << "=== 扫描结束 ===";

    if (!foundMyUI) {
        qDebug() << "❌ 严重错误：内存里根本没有 MyCompany 的相关文件！";
        qDebug() << "原因可能是：MyUI.dll 虽然编译了，但程序运行时没加载它。";
    } else {
        qDebug() << "✅ 资源存在！路径问题已缩小。";
    }
    // ----------------

    // 正常的加载逻辑...
    engine.addImportPath(u"qrc:/qt/qml"_qs);
    engine.load(QUrl(u"qrc:/qt/qml/GalleryApp/Main.qml"_qs));
    return app.exec();
}
