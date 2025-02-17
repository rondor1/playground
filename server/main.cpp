#include "objecthandler.grpc.pb.h"
#include "objecthandler.pb.h"
#include <grpcpp/completion_queue.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <iostream>
#include <memory>

using grpc::ServerUnaryReactor;

class HandlerServiceImpl final
    : public objecthandler::ObjectHandlerService::Service {
  grpc::Status GetPosition(grpc::ServerContext *context,
                           const objecthandler::ObjectName *object_name,
                           objecthandler::Object *object) {
    return grpc::Status(grpc::StatusCode::UNIMPLEMENTED,
                        "Function still not implemented!");
  }

  grpc::Status GetObject(grpc::ServerContext *context,
                         const objecthandler::ObjectName *object_name,
                         objecthandler::Object *result_object) {
    if (object_name == nullptr || result_object == nullptr) {
      std::cerr << " Invalid input parameters !" << std::endl;
      return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "Failed call");
    }

    if (object_name->name().empty()) {
      return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                          "Invalid argument provided");
    }

    result_object->mutable_name()->set_name(object_name->name());
    result_object->mutable_position()->set_x(1);
    result_object->mutable_position()->set_z(1);
    result_object->mutable_position()->set_y(1);

    return grpc::Status::OK;
  }
};

void run_server() {
  std::string server_address = std::string{"0.0.0.0:50051"};
  HandlerServiceImpl impl{};

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&impl);

  std::unique_ptr<grpc::Server> server{builder.BuildAndStart()};
  std::cout << "Listening on : " << server_address << std::endl;
  server->Wait();
}

int main(void) {

  run_server();
  return 0;
}