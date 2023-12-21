//
// Created by andrey on 17.12.23.
//

#include "organization_delete.hpp"
#include "../../DTO/organization.hpp"
#include "../../db/sql.hpp"
#include "userver/crypto/hash.hpp"
#include "userver/formats/parse/common_containers.hpp"
#include "userver/formats/serialize/common_containers.hpp"
namespace userverApp::handlers::organization {
userverApp::handlers::organization::organization_delete::organization_delete(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      pg_cluster_(context.FindComponent<components::Postgres>("postgres-db-1")
                      .GetCluster()) {
  using storages::postgres::ClusterHostType;
}
formats::json::Value organization_delete::HandleRequestJsonThrow(
    const server::http::HttpRequest& request, const formats::json::Value& org,
    server::request::RequestContext&) const {
  const auto id = org["id"].As<std::string>();
  auto org_res =
      pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                           userverApp::sql::kDeleteOrganization.data(), id);
  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
  return {};
}

}  // namespace userverApp::handlers::organization