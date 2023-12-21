//
// Created by andrey on 16.12.23.
//

#include "workstation.hpp"
namespace userverApp::entity {
workstation Parse(const userver::formats::json::Value& json,
                  userver::formats::parse::To<workstation>) {
  return workstation{
      json["ip"].As<std::string>(""),
      json["worker_id"].As<std::string>(
          ""),  // return `1` if "field2" is missing
  };
}

userver::formats::json::Value Serialize(
    const workstation& workstation,
    userver::formats::serialize::To<userver::formats::json::Value>) {
  userver::formats::json::ValueBuilder builder;
  builder["ip"] = workstation.ip;
  builder["worker_id"] = workstation.worker_id;

  return builder.ExtractValue();
}
}  // namespace userverApp::entity