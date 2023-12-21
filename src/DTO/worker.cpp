//
// Created by andrey on 16.12.23.
//
#include "worker.hpp"

namespace userverApp::entity {

worker Parse(const userver::formats::json::Value& json,
             userver::formats::parse::To<worker>) {
  return worker{
      json["worker_id"].As<std::string>(""),
      json["org_name"].As<std::string>(""),
      json["worker_surname"].As<std::string>(
          ""),  // return `1` if "field2" is missing
      json["working_time_start"].As<std::string>(
          ""),  // return `1` if "field2" is missing
      json["working_time_end"].As<std::string>(
          ""),  // return `1` if "field2" is missing

  };
}

userver::formats::json::Value Serialize(
    const worker& worker,
    userver::formats::serialize::To<userver::formats::json::Value>) {
  userver::formats::json::ValueBuilder builder;
  builder["worker_id"] = worker.worker_id;
  builder["worker_name"] = worker.worker_name;
  builder["worker_surname"] = worker.worker_surname;
  builder["working_time_start"] = worker.working_time_start;
  builder["working_time_end"] = worker.working_time_end;

  return builder.ExtractValue();
}

}  // namespace userverApp::entity
