load("@rules_cc//cc:defs.bzl", "cc_test", "cc_library")

cc_library(
  name = "mocks",
  hdrs = [
    "mocks.h",
  ],
  deps = [
    "@skywalking_data_collect_protocol//language-agent:tracing_protocol_cc_proto",
    "@com_google_googletest//:gtest_main",
    "//cpp2sky:async_client_interface",
    "//cpp2sky:random_interface",
  ]
)

cc_test(
  name = "propagation_test",
  srcs = [
    "propagation_test.cc",
  ],
  deps = [
    "@com_google_googletest//:gtest_main",
    "//source:cpp2sky_lib",
  ],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "segment_context_test",
  srcs = [
    "segment_context_test.cc",
  ],
  deps = [
    "@com_google_googletest//:gtest_main",
    "@com_google_protobuf//:protobuf",
    "//source:cpp2sky_lib",
    ":mocks",
  ],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "grpc_async_client_test",
  srcs = [
    "grpc_async_client_test.cc",
  ],
  deps = [
    "@com_google_googletest//:gtest_main",
    "//source:cpp2sky_lib",
    ":mocks",
  ],
  visibility = ["//visibility:public"],
)
