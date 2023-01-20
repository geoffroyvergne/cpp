# Bazel C++ Boost

https://github.com/nelhage/rules_boost/tree/master/test
https://github.com/nelhage/rules_boost/blob/master/test/json_test.cc

bazel test --test_output=all //main:json-test

bazel build //main:json

./bazel-bin/main/json