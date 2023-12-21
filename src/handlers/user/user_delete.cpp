//
// Created by andrey on 16.12.23.
//

#include "user_delete.hpp"
#include "../../DTO/user.hpp"
#include "../../db/sql.hpp"
#include "userver/crypto/hash.hpp"
#include "userver/formats/parse/common_containers.hpp"
#include "userver/formats/serialize/common_containers.hpp"
namespace userverApp::handlers::user {
userverApp::handlers::user::user_delete::user_delete(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      pg_cluster_(context.FindComponent<components::Postgres>("postgres-db-1")
                      .GetCluster()) {
  using storages::postgres::ClusterHostType;
}
formats::json::Value user_delete::HandleRequestJsonThrow(
    const server::http::HttpRequest& request, const formats::json::Value& user,
    server::request::RequestContext&) const {
  const auto id = user["id"].As<std::string>();
  auto user_res =
      pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                           userverApp::sql::kDeleteUser.data(), id);
  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
  return {};
}

}  // namespace userverApp::handlers::user