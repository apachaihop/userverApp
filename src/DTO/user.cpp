//
// Created by andrey on 1.12.23.
//
#include "user.hpp"
#include "../utils/jwt.hpp"
namespace userverApp::entity {
user Parse(const userver::formats::json::Value& json,
           userver::formats::parse::To<user>) {
  return user{
      json["id"].As<std::string>(""),
      json["name"].As<std::string>(""),
      json["surname"].As<std::string>(""),  // return `1` if "field2" is missing
      json["email"].As<std::string>(""),
  };
}

userver::formats::json::Value Serialize(
    const user& user,
    userver::formats::serialize::To<userver::formats::json::Value>) {
  userver::formats::json::ValueBuilder builder;
  builder["user_id"] = user.id;
  builder["name"] = user.name;
  builder["surname"] = user.surname;
  builder["email"] = user.email;
  builder["token"] = utils::jwt::GenerateJWT(user.id);

  return builder.ExtractValue();
}
}  // namespace userverApp::entity