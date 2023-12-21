//
// Created by andrey on 1.12.23.
//

#include "user_login.hpp"
#include "../../DTO/user.hpp"
#include "userver/crypto/hash.hpp"
#include "userver/formats/parse/common_containers.hpp"
#include "userver/formats/serialize/common_containers.hpp"
namespace userverApp::handlers::user {

user_login ::user_login(const userver::components::ComponentConfig& config,
                        const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      pg_cluster_(context.FindComponent<components::Postgres>("postgres-db-1")
                      .GetCluster()) {
  using storages::postgres::ClusterHostType;
}
const storages::postgres::Query kSelectLoginUser{
    "SELECT * FROM logic.users where email=$1 and password=$2",
    storages::postgres::Query::Name{"select_login_user"},
};
formats::json::Value user_login::HandleRequestJsonThrow(
    const server::http::HttpRequest& request, const formats::json::Value& user,
    server::request::RequestContext&) const {
  auto email = user["email"].As<std::string>();
  auto password = user["password"].As<std::string>();
  auto hash_password = userver::crypto::hash::Sha256(password);
  auto res = pg_cluster_->Execute(storages::postgres::ClusterHostType::kSlave,
                                  kSelectLoginUser, email, hash_password);
  if (res.IsEmpty()) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kNotFound);
    return {};
  }
  std::string name;
  std::string surname;
  std::string id;
  auto response = res.AsSingleRow<userverApp::entity::user>(
      userver::storages::postgres::kRowTag);
  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
  userver::formats::json::ValueBuilder builder;
  builder["user"] = response;
  auto resultResponse = *(builder.begin());
  return resultResponse.ExtractValue();
}

}  // namespace userverApp::handlers::user
