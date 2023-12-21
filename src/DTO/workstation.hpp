//
// Created by andrey on 16.12.23.
//

#ifndef USERVERAPP_WORKSTATION_HPP
#define USERVERAPP_WORKSTATION_HPP
#include <string>
#include <userver/formats/json.hpp>
#include <userver/formats/parse/common_containers.hpp>
#include <userver/formats/serialize/common_containers.hpp>
namespace userverApp::entity {
struct workstation {
  std::string ip;
  std::string worker_id;
};

workstation Parse(const userver::formats::json::Value& json,
                  userver::formats::parse::To<workstation>);

userver::formats::json::Value Serialize(
    const workstation& workstation,
    userver::formats::serialize::To<userver::formats::json::Value>);
}  // namespace userverApp::entity
#endif  // USERVERAPP_WORKSTATION_HPP
