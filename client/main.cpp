#include "objecthandler.grpc.pb.h"
#include "objecthandler.pb.h"
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <iostream>
#include <memory>

class ObjectHandlerClient {
private:
  std::shared_ptr<objecthandler::ObjectHandlerService::Stub> stub_{nullptr};

public:
  ObjectHandlerClient(std::shared_ptr<grpc::Channel> channel)
      : stub_(objecthandler::ObjectHandlerService::NewStub(channel)) {}
  void GetPosition(const std::string &name) {
    if (name.empty()) {
      std::cerr << "No valid name provided! " << std::endl;
      return;
    }

    objecthandler::ObjectName object_name{};
    object_name.set_name(name);

    objecthandler::Object result_object{};

    grpc::ClientContext client{};
    grpc::Status status =
        stub_->GetObject(&client, object_name, &result_object);
    if (status.ok()) {
      std::cout << result_object.name().name() << " <=> ("
                << result_object.position().x() << ", "
                << result_object.position().y() << ", "
                << result_object.position().z() << ")" << std::endl;
    } else {
      std::cerr << status.error_message() << std::endl;
    }
  }
};

int main(void) {

  ObjectHandlerClient client{grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials())};

  client.GetPosition("robert");

  return 0;
}