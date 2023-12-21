#include "hello.hpp"

#include <userver/utest/utest.hpp>
#include "utils/jwt.hpp"
UTEST(SayHelloTo, Basic) {
  using userverApp::SayHelloTo;
  using userverApp::UserType;

  EXPECT_EQ(SayHelloTo("Developer", UserType::kFirstTime),
            "Hello, Developer!\n");
  EXPECT_EQ(SayHelloTo({}, UserType::kFirstTime), "Hello, unknown user!\n");

  EXPECT_EQ(SayHelloTo("Developer", UserType::kKnown),
            "Hi again, Developer!\n");
}
UTEST(GenerateJWT, JWT) {
  using userverApp::utils::jwt::GenerateJWT;

  EXPECT_EQ(GenerateJWT("123"), GenerateJWT("123"));
}
