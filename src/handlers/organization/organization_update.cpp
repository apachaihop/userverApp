//
// Created by andrey on 17.12.23.
//

#include "organization_update.hpp"
#include "../../DTO/organization.hpp"
#include "../../db/sql.hpp"
#include "userver/crypto/hash.hpp"
#include "userver/formats/parse/common_containers.hpp"
#include "userver/formats/serialize/common_containers.hpp"
#include "userver/logging/log.hpp"
namespace userverApp::handlers::organization {
userverApp::handlers::organization::organization_update::organization_update(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      pg_cluster_(context.FindComponent<components::Postgres>("postgres-db-1")
                      .GetCluster()) {
  using storages::postgres::ClusterHostType;
}
formats::json::Value organization_update::HandleRequestJsonThrow(
    const server::http::HttpRequest& request, const formats::json::Value& org,
    server::request::RequestContext&) const {
  LOG_DEBUG() << request.GetCookie("id");
  const auto id = org["id"].As<std::string>();
  const std::optional<std::string> name =
      org["name"].As<std::optional<std::string>>();

  auto org_res = pg_cluster_->Execute(
      storages::postgres::ClusterHostType::kMaster,
      userverApp::sql::kUpdateOrganization.data(), name, id);
  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
  org_res =
      pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                           userverApp::sql::kSelectOrganizationById.data(), id);
  auto response = org_res.AsSingleRow<userverApp::entity::organization>(
      userver::storages::postgres::kRowTag);
  userver::formats::json::ValueBuilder builder;
  builder["organization"] = response;
  auto resultResponse = *(builder.begin());
  return resultResponse.ExtractValue();
}

}  // namespace userverApp::handlers::organization