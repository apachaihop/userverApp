//
// Created by andrey on 19.12.23.
//

#include "service_get.hpp"
#include "../../DTO/services.hpp"
#include "../../db/sql.hpp"
#include "userver/formats/parse/common_containers.hpp"
#include "userver/formats/serialize/common_containers.hpp"
namespace userverApp::handlers::service {
userverApp::handlers::service::service_get::service_get(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      pg_cluster_(context.FindComponent<components::Postgres>("postgres-db-1")
                      .GetCluster()) {
  using storages::postgres::ClusterHostType;
}
formats::json::Value service_get::HandleRequestJsonThrow(
    const server::http::HttpRequest& request,
    const formats::json::Value& service,
    server::request::RequestContext&) const {
  const auto id = service["id"].As<std::string>();
  auto service_res =
      pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                           userverApp::sql::kSelectServiceById.data(), id);
  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);

  if (service_res.IsEmpty()) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kNotFound);
    return {};
  }
  auto response = service_res.AsSingleRow<userverApp::entity::services>();
  userver::formats::json::ValueBuilder builder;
  builder["service"] = response;
  auto resultResponse = *(builder.begin());
  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
  return resultResponse.ExtractValue();
}

}  // namespace userverApp::handlers::service