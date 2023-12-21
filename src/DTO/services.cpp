//
// Created by andrey on 16.12.23.
#include "services.hpp"
namespace userverApp::entity {
services Parse(const userver::formats::json::Value& json,
               userver::formats::parse::To<services>) {
  return services{
      json["id"].As<std::string>(""), json["service_name"].As<std::string>(""),
      // return `1` if "field2" is missing
  };
}
userver::formats::json::Value Serialize(
    const services& services,
    userver::formats::serialize::To<userver::formats::json::Value>) {
  userver::formats::json::ValueBuilder builder;
  builder["id"] = services.id;
  builder["service_name"] = services.service_name;

  return builder.ExtractValue();
}

}  // namespace userverApp::entity