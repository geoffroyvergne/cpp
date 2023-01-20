load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_test(
    name = "json-test",
    srcs = ["json-test.cc"],
    deps = [
        "@boost//:json",
    ],
)

cc_binary(
    name = "json",
    srcs = ["json.cc"],
    deps = [
        "@boost//:json",
    ],
)
