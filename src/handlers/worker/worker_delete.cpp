//
// Created by andrey on 17.12.23.
//

#include "worker_delete.hpp"
#include "../../DTO/worker.hpp"
#include "../../db/sql.hpp"
#include "userver/crypto/hash.hpp"
#include "userver/formats/parse/common_containers.hpp"
#include "userver/formats/serialize/common_containers.hpp"
namespace userverApp::handlers::worker {
userverApp::handlers::worker::worker_delete::worker_delete(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      pg_cluster_(context.FindComponent<components::Postgres>("postgres-db-1")
                      .GetCluster()) {
  using storages::postgres::ClusterHostType;
}
formats::json::Value worker_delete::HandleRequestJsonThrow(
    const server::http::HttpRequest& request,
    const formats::json::Value& worker,
    server::request::RequestContext&) const {
  const auto id = worker["id"].As<std::string>();
  auto worker_res =
      pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                           userverApp::sql::kDeleteWorkerById.data(), id);
  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
  return {};
}

}  // namespace userverApp::handlers::worker