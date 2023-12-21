//
// Created by andrey on 17.12.23.
//

#include "worker_get.hpp"
#include "../../DTO/worker.hpp"
#include "../../db/sql.hpp"
#include "userver/crypto/hash.hpp"
#include "userver/formats/parse/common_containers.hpp"
#include "userver/formats/serialize/common_containers.hpp"
namespace userverApp::handlers::worker {
userverApp::handlers::worker::worker_get::worker_get(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      pg_cluster_(context.FindComponent<components::Postgres>("postgres-db-1")
                      .GetCluster()) {
  using storages::postgres::ClusterHostType;
}
formats::json::Value worker_get::HandleRequestJsonThrow(
    const server::http::HttpRequest& request,
    const formats::json::Value& worker,
    server::request::RequestContext&) const {
  const auto id = worker["id"].As<std::string>();
  auto worker_res =
      pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                           userverApp::sql::kSelectWorkerById.data(), id);
  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
  auto response = worker_res.AsSingleRow<userverApp::entity::worker>();
  userver::formats::json::ValueBuilder builder;
  builder["worker"] = response;
  auto resultResponse = *(builder.begin());
  return resultResponse.ExtractValue();
}

}  // namespace userverApp::handlers::worker