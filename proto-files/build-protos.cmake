find_package(gRPC CONFIG REQUIRED)

add_library(proto-library OBJECT "${CMAKE_CURRENT_LIST_DIR}/objecthandler.proto")

target_link_libraries(proto-library PUBLIC protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection)

set(PROTO_BINARY_DIR "${CMAKE_BINARY_DIR}")
set(PROTO_IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}")

target_include_directories(proto-library PUBLIC "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>")

protobuf_generate(
    TARGET proto-library
    IMPORT_DIRS ${PROTO_IMPORT_DIRS}
    PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")

protobuf_generate(
    TARGET proto-library
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
    IMPORT_DIRS ${PROTO_IMPORT_DIRS}
    PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")
