proto_library(
    name = "helloworld_proto",
    srcs = ["helloworld.proto"],
    deps = ["@com_google_protobuf//:timestamp_proto"],
)
cc_proto_library(
    name = "helloworld_cc_proto",
    deps = [":helloworld_proto"],
)

cc_binary(
    name = "add_details_cpp",
    srcs = ["add_details.cc"],
    deps = [":helloworld_cc_proto"],
)
