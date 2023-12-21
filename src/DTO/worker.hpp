//
// Created by andrey on 27.11.23.
//

#ifndef USERVERAPP_WORKER_HPP
#define USERVERAPP_WORKER_HPP
#include <string>
#include <userver/formats/json.hpp>
#include <userver/formats/parse/common_containers.hpp>
#include <userver/formats/serialize/common_containers.hpp>

namespace userverApp::entity {
struct worker {
  std::string worker_id;
  std::string worker_name;
  std::string worker_surname;
  std::string working_time_start;
  std::string working_time_end;
};

worker Parse(const userver::formats::json::Value& json,
             userver::formats::parse::To<worker>);

userver::formats::json::Value Serialize(
    const worker& worker,
    userver::formats::serialize::To<userver::formats::json::Value>);

}  // namespace userverApp::entity
#endif  // USERVERAPP_WORKER_HPP
