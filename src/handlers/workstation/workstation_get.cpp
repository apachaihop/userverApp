//
// Created by andrey on 18.12.23.
//

#include "workstation_get.hpp"
#include "../../DTO/workstation.hpp"
#include "../../db/sql.hpp"
#include "userver/formats/parse/common_containers.hpp"
#include "userver/formats/serialize/common_containers.hpp"
namespace userverApp::handlers::workstation {
userverApp::handlers::workstation::workstation_get::workstation_get(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      pg_cluster_(context.FindComponent<components::Postgres>("postgres-db-1")
                      .GetCluster()) {
  using storages::postgres::ClusterHostType;
}
formats::json::Value workstation_get::HandleRequestJsonThrow(
    const server::http::HttpRequest& request,
    const formats::json::Value& workstation,
    server::request::RequestContext&) const {
  const auto ip = workstation["ip"].As<std::string>();

  auto workstation_res =
      pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                           userverApp::sql::kSelectWorkstationByIp.data(), ip);
  auto response =
      workstation_res.AsSingleRow<userverApp::entity::workstation>();
  userver::formats::json::ValueBuilder builder;
  builder["workstation"] = response;
  auto resultResponse = *(builder.begin());
  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
  return resultResponse.ExtractValue();
}

}  // namespace userverApp::handlers::workstation