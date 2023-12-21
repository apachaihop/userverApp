//
// Created by andrey on 19.12.23.
//

#ifndef USERVERAPP_WORKER_TRAFFIC_HPP
#define USERVERAPP_WORKER_TRAFFIC_HPP
#include <string>
#include <userver/formats/json.hpp>
#include <userver/formats/parse/common_containers.hpp>
#include <userver/formats/serialize/common_containers.hpp>
namespace userverApp::entity {
struct worker_traffic {
  std::string service_name;
  double traffic;
};

worker_traffic Parse(const userver::formats::json::Value& json,
                     userver::formats::parse::To<worker_traffic>);

userver::formats::json::Value Serialize(
    const worker_traffic& worker_traffic,
    userver::formats::serialize::To<userver::formats::json::Value>);

}  // namespace userverApp::entity

#endif  // USERVERAPP_WORKER_TRAFFIC_HPP
