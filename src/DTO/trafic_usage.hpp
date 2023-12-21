//
// Created by andrey on 16.12.23.
//

#ifndef USERVERAPP_TRAFIC_USAGE_HPP
#define USERVERAPP_TRAFIC_USAGE_HPP
#include <string>
#include <userver/formats/json.hpp>
#include <userver/formats/parse/common_containers.hpp>
#include <userver/formats/serialize/common_containers.hpp>
namespace userverApp::entity {
struct trafic_usage {
  std::string ip;
  int kbytes;
  std::string date;
};
trafic_usage Parse(const userver::formats::json::Value& json,
                   userver::formats::parse::To<trafic_usage>);
userver::formats::json::Value Serialize(
    const trafic_usage& trafic_usage,
    userver::formats::serialize::To<userver::formats::json::Value>);
}  // namespace userverApp::entity
#endif  // USERVERAPP_TRAFIC_USAGE_HPP
