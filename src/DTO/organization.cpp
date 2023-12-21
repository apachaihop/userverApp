//
// Created by andrey on 16.12.23.
//
#include "organization.hpp"
namespace userverApp::entity {
organization Parse(const userver::formats::json::Value& json,
                   userver::formats::parse::To<organization>) {
  return organization{
      json["id"].As<std::string>(""), json["org_name"].As<std::string>(""),
      // return `1` if "field2" is missing
  };
}

userver::formats::json::Value Serialize(
    const organization& organization,
    userver::formats::serialize::To<userver::formats::json::Value>) {
  userver::formats::json::ValueBuilder builder;
  builder["id"] = organization.id;
  builder["org_name"] = organization.org_name;

  return builder.ExtractValue();
}
}  // namespace userverApp::entity