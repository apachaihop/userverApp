//
// Created by andrey on 16.12.23.
//

#include "user_update.hpp"
#include "../../DTO/user.hpp"
#include "../../db/sql.hpp"
#include "userver/crypto/hash.hpp"
#include "userver/formats/parse/common_containers.hpp"
#include "userver/formats/serialize/common_containers.hpp"
#include "userver/logging/log.hpp"
namespace userverApp::handlers::user {
userverApp::handlers::user::user_update::user_update(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      pg_cluster_(context.FindComponent<components::Postgres>("postgres-db-1")
                      .GetCluster()) {
  using storages::postgres::ClusterHostType;
}
formats::json::Value user_update::HandleRequestJsonThrow(
    const server::http::HttpRequest& request, const formats::json::Value& user,
    server::request::RequestContext&) const {
  LOG_DEBUG() << request.GetCookie("id");
  const auto id = user["id"].As<std::string>();
  const std::optional<std::string> email =
      user["email"].As<std::optional<std::string>>();
  const std::optional<std::string> password =
      user["password"].As<std::optional<std::string>>();
  const std::optional<std::string> name =
      user["name"].As<std::optional<std::string>>();
  const std::optional<std::string> surname =
      user["surname"].As<std::optional<std::string>>();
  std::optional<std::string> password_hash = std::nullopt;
  if (password) {
    password_hash = userver::crypto::hash::Sha256(password.value());
  }

  auto user_res =
      pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                           userverApp::sql::kUpdateUser.data(), name, surname,
                           email, password_hash, id);
  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
  user_res = pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                                  userverApp::sql::kSelectUserById.data(), id);
  auto response = user_res.AsSingleRow<userverApp::entity::user>(
      userver::storages::postgres::kRowTag);
  userver::formats::json::ValueBuilder builder;
  builder["user"] = response;
  auto resultResponse = *(builder.begin());
  return resultResponse.ExtractValue();
}

}  // namespace userverApp::handlers::user