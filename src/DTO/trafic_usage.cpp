//
// Created by andrey on 16.12.23.
//

#include "trafic_usage.hpp"
namespace userverApp::entity {
trafic_usage Parse(const userver::formats::json::Value& json,
                   userver::formats::parse::To<trafic_usage>) {
  return trafic_usage{
      json["ip"].As<std::string>(""), json["kbytes"].As<int>(0),
      json["date"].As<std::string>(""),
      // return `1` if "field2" is missing
  };
}

userver::formats::json::Value Serialize(
    const trafic_usage& trafic_usage,
    userver::formats::serialize::To<userver::formats::json::Value>) {
  userver::formats::json::ValueBuilder builder;
  builder["ip"] = trafic_usage.ip;
  builder["kbytes"] = trafic_usage.kbytes;
  builder["date"] = trafic_usage.date;

  return builder.ExtractValue();
}

}  // namespace userverApp::entity