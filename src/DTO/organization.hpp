//
// Created by andrey on 27.11.23.
//

#ifndef USERVERAPP_ORGANIZATION_HPP
#define USERVERAPP_ORGANIZATION_HPP
#include <userver/formats/json.hpp>
#include <userver/formats/parse/common_containers.hpp>
#include <userver/formats/serialize/common_containers.hpp>
#include <vector>

namespace userverApp::entity {
struct organization {
  std::string id;
  std::string org_name;
};
organization Parse(const userver::formats::json::Value& json,
                   userver::formats::parse::To<organization>);
userver::formats::json::Value Serialize(
    const organization& organization,
    userver::formats::serialize::To<userver::formats::json::Value>);

}  // namespace userverApp::entity
#endif  // USERVERAPP_ORGANIZATION_HPP
