//
// Created by andrey on 18.12.23.
//

#include "worker_get_workstations.hpp"
#include "../../DTO/workstation.hpp"
#include "../../db/sql.hpp"
#include "userver/crypto/hash.hpp"
#include "userver/formats/parse/common_containers.hpp"
#include "userver/formats/serialize/common_containers.hpp"
namespace userverApp::handlers::worker {
userverApp::handlers::worker::worker_get_workstations::worker_get_workstations(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      pg_cluster_(context.FindComponent<components::Postgres>("postgres-db-1")
                      .GetCluster()) {
  using storages::postgres::ClusterHostType;
}
formats::json::Value worker_get_workstations::HandleRequestJsonThrow(
    const server::http::HttpRequest&, const formats::json::Value& worker,
    server::request::RequestContext&) const {
  const auto id = worker["id"].As<std::string>();
  auto worker_res = pg_cluster_->Execute(
      storages::postgres::ClusterHostType::kMaster,
      userverApp::sql::kSelectWorkstationsByWorkerId.data(), id);
  auto response =
      worker_res.AsContainer<std::vector<userverApp::entity::workstation>>();
  userver::formats::json::ValueBuilder builder;
  builder["worker"] = response;
  auto resultResponse = *(builder.begin());
  return resultResponse.ExtractValue();
}

}  // namespace userverApp::handlers::worker