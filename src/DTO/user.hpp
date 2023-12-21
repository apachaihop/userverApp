//
// Created by andrey on 14.11.23.
//

#pragma once
#include <userver/formats/json.hpp>
#include <userver/formats/parse/common_containers.hpp>
#include <userver/formats/serialize/common_containers.hpp>
#include <vector>
namespace userverApp::entity {
struct user {
  std::string id;
  std::string name;
  std::string surname;
  std::string email;
};

user Parse(const userver::formats::json::Value& json,
           userver::formats::parse::To<user>);

userver::formats::json::Value Serialize(
    const user& user,
    userver::formats::serialize::To<userver::formats::json::Value>);

}  // namespace userverApp::entity
