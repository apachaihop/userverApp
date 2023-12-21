//
// Created by andrey on 16.12.23.
//

#include "user_register.hpp"
#include "../../DTO/user.hpp"
#include "../../db/sql.hpp"
#include "userver/crypto/hash.hpp"
#include "userver/formats/parse/common_containers.hpp"
#include "userver/formats/serialize/common_containers.hpp"
namespace userverApp::handlers::user {
userverApp::handlers::user::user_register::user_register(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      pg_cluster_(context.FindComponent<components::Postgres>("postgres-db-1")
                      .GetCluster()) {
  using storages::postgres::ClusterHostType;
}
formats::json::Value user_register::HandleRequestJsonThrow(
    const server::http::HttpRequest& request, const formats::json::Value& user,
    server::request::RequestContext&) const {
  const auto email = user["email"].As<std::string>();
  const auto password = user["password"].As<std::string>();
  const auto name = user["name"].As<std::string>();
  const auto surname = user["surname"].As<std::string>();
  const auto org_name = user["org_name"].As<std::string>();
  auto user_res =
      pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                           userverApp::sql::kSelectUserByEmail.data(), email);

  if (!user_res.IsEmpty()) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kBadRequest);
    return {};
  }
  const auto hash_password = userver::crypto::hash::Sha256(password);
  auto org_res = pg_cluster_->Execute(
      storages::postgres::ClusterHostType::kMaster,
      userverApp::sql::kSelectOrganizationByName.data(), org_name);

  user_res = pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                                  userverApp::sql::kInsertUser.data(), name,
                                  surname, email, hash_password);

  auto org_id = user_res[0].As<std::string>();
  auto insert_org_res = pg_cluster_->Execute(
      storages::postgres::ClusterHostType::kMaster,
      userverApp::sql::kInsertOrganization.data(), org_id, org_name);
  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
  return {};
}

}  // namespace userverApp::handlers::user