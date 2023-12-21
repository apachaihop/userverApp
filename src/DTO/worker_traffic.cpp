//
// Created by andrey on 19.12.23.
//

#include "worker_traffic.hpp"
namespace userverApp::entity {

worker_traffic Parse(const userver::formats::json::Value& json,
                     userver::formats::parse::To<worker_traffic>) {
  return worker_traffic{
      json["service_name"].As<std::string>(""), json["traffic"].As<double>(0)

  };
}
userver::formats::json::Value Serialize(
    const worker_traffic& worker_traffic,
    userver::formats::serialize::To<userver::formats::json::Value>) {
  userver::formats::json::ValueBuilder builder;
  builder["service_name"] = worker_traffic.service_name;
  builder["traffic"] = worker_traffic.traffic;

  return builder.ExtractValue();
}
}  // namespace userverApp::entity