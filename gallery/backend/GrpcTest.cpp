#include <QDebug>
#include <QGrpcHttp2Channel>
// 引入生成的头文件 (根据你的 proto 文件名)
#include "stream.qpb.h"
#include "stream_client.grpc.qpb.h"

void GrpcTest_Func() {
    // ================= gRPC 客户端逻辑开始  =================

    // 1. 创建频道 (Channel) - 连接到服务端 (例如 localhost:50051)
    // 注意：Qt gRPC 目前主要支持 HTTP/2
    auto channel = std::make_shared<QGrpcHttp2Channel>(
        QUrl("http://127.0.0.1:5200")
        );

    // 2. 创建客户端对象 (Client Stub)
    // 命名空间 'routeguide' 来自你的 proto 文件 package routeguide;
    // 类名 'RouteGuide' 来自 service RouteGuide { ... }
    auto client = std::make_shared<routeguide::RouteGuide::Client>();

    // 3. 把频道挂载给客户端
    client->attachChannel(channel);

    // 4. (可选) 发送一个简单的测试请求
    // 假设你有一个 rpc sayHello(Request) 方法
    routeguide::Request request;
    request.setId_proto(123);
    request.setData("Hello from Qt Client!");

    // 【修正点 1】直接调用，不传回调，它会返回一个 reply 指针
    auto reply = client->sayHello(request);
    auto* raw_ptr = reply.get();
    qDebug() << "【✅ Send sayHello 】";
    // 【修正点 2】使用 Qt 的 connect 监听“完成”信号
    // 注意：lambda 里面必须 [reply] 捕获这个指针，否则它可能还没跑完就销毁了
    QObject::connect(raw_ptr, &QGrpcCallReply::finished, [raw_ptr]() { // , &app

        // 【修正点 3】检查结果
        // read<T>() 会尝试反序列化，如果成功返回 std::optional<T>
        if (const auto response = raw_ptr->read<routeguide::Response>()) {
            qDebug() << "✅ 收到服务器回复:" << response->message();
        } else {
            // 2. 打印错误信息
            qDebug() << "❌ RPC 失败";
        }
    });

    // ================= gRPC Tesst 客户端逻辑结束 =================
}
