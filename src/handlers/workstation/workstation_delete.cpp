//
// Created by andrey on 18.12.23.
//

#include "workstation_delete.hpp"
#include "../../DTO/workstation.hpp"
#include "../../db/sql.hpp"
#include "userver/formats/parse/common_containers.hpp"
#include "userver/formats/serialize/common_containers.hpp"
namespace userverApp::handlers::workstation {
userverApp::handlers::workstation::workstation_delete::workstation_delete(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      pg_cluster_(context.FindComponent<components::Postgres>("postgres-db-1")
                      .GetCluster()) {
  using storages::postgres::ClusterHostType;
}
formats::json::Value workstation_delete::HandleRequestJsonThrow(
    const server::http::HttpRequest& request,
    const formats::json::Value& workstation,
    server::request::RequestContext&) const {
  const auto ip = workstation["ip"].As<std::string>();

  auto workstation_res =
      pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                           userverApp::sql::kDeleteWorkstation.data(), ip);
  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
  return {};
}
}  // namespace userverApp::handlers::workstation