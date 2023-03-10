cc_library(
    name = "CPPLib",
    srcs = ["q.cc"],
    hdrs = ["q.h"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "student_test",
    srcs = ["student_test.cc"],
    deps = [
        ":CPPLib",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "grader_test",
    srcs = ["grader_test.cc"],
    deps = [
        ":CPPLib",
        "@com_google_googletest//:gtest_main",
    ],
)
