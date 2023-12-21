//
// Created by andrey on 19.12.23.
//

#include "service_insert.hpp"
#include "../../DTO/services.hpp"
#include "../../db/sql.hpp"
#include "userver/formats/parse/common_containers.hpp"
#include "userver/formats/serialize/common_containers.hpp"
namespace userverApp::handlers::service {
userverApp::handlers::service::service_insert::service_insert(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      pg_cluster_(context.FindComponent<components::Postgres>("postgres-db-1")
                      .GetCluster()) {
  using storages::postgres::ClusterHostType;
}
formats::json::Value service_insert::HandleRequestJsonThrow(
    const server::http::HttpRequest& request,
    const formats::json::Value& service,
    server::request::RequestContext&) const {
  const auto name = service["name"].As<std::string>();
  auto service_res =
      pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                           userverApp::sql::kInsertService.data(), name);
  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
  return {};
}

}  // namespace userverApp::handlers::service