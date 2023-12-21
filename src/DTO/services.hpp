//
// Created by andrey on 16.12.23.
//

#ifndef USERVERAPP_SERVICES_HPP
#define USERVERAPP_SERVICES_HPP
#include <string>
#include <userver/formats/json.hpp>
#include <userver/formats/parse/common_containers.hpp>
#include <userver/formats/serialize/common_containers.hpp>

namespace userverApp::entity {
struct services {
  std::string id;
  std::string service_name;
};
services Parse(const userver::formats::json::Value& json,
               userver::formats::parse::To<services>);
userver::formats::json::Value Serialize(
    const services& services,
    userver::formats::serialize::To<userver::formats::json::Value>);

}  // namespace userverApp::entity
#endif  // USERVERAPP_SERVICES_HPP
