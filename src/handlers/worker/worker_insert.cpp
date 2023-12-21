//
// Created by andrey on 17.12.23.
//

#include "worker_insert.hpp"
#include "../../DTO/worker.hpp"
#include "../../db/sql.hpp"
#include "userver/crypto/hash.hpp"
#include "userver/formats/parse/common_containers.hpp"
#include "userver/formats/serialize/common_containers.hpp"
namespace userverApp::handlers::worker {
userverApp::handlers::worker::worker_insert::worker_insert(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      pg_cluster_(context.FindComponent<components::Postgres>("postgres-db-1")
                      .GetCluster()) {
  using storages::postgres::ClusterHostType;
}
formats::json::Value worker_insert::HandleRequestJsonThrow(
    const server::http::HttpRequest& request,
    const formats::json::Value& worker,
    server::request::RequestContext&) const {
  const auto name = worker["name"].As<std::string>();
  const auto surname = worker["surname"].As<std::string>();
  const auto working_time_start =
      worker["working_time_start"].As<std::string>();
  const auto working_time_end = worker["working_time_end"].As<std::string>();
  const auto org_id = worker["org_id"].As<std::string>();
  auto worker_res =
      pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                           userverApp::sql::kInsertWorker.data(), org_id, name,
                           surname, working_time_start, working_time_end);
  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
  return {};
}

}  // namespace userverApp::handlers::worker