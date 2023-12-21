
#include "user_component.hpp"
#include <userver/formats/parse/common_containers.hpp>
#include <userver/formats/serialize/common_containers.hpp>
#include "DTO/user.hpp"
#include "userver/crypto/hash.hpp"

namespace userverApp::handlers::users {
/// [Postgres service sample - component constructor]
user_component ::user_component(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      pg_cluster_(context.FindComponent<components::Postgres>("postgres-db-1")
                      .GetCluster()) {
  using storages::postgres::ClusterHostType;
}
/// [Postgres service sample - component constructor]

/// [Postgres service sample - HandleRequestThrow]

/// [Postgres service sample - HandleRequestThrow]

/// [Postgres service sample - GetValue]
const storages::postgres::Query kSelectUser{
    "SELECT * FROM logic.users",
    storages::postgres::Query::Name{"sample_select_value"},
};

userver::formats::json::Value user_component::GetValue(
    const userver::server::http::HttpRequest& request) const {
  auto res = pg_cluster_->Execute(storages::postgres::ClusterHostType::kSlave,
                                  kSelectUser);
  if (res.IsEmpty()) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kNotFound);
    return {};
  }
  std::vector<userverApp::entity::user> users;
  users.reserve(res.Size());
  std::string name;
  std::string surname;
  std::string email;
  std::string id;
  for (auto&& row : res) {
    name = row["name"].As<std::string>();
    surname = row["surname"].As<std::string>();
    email = row["email"].As<std::string>();
    id = row["user_id"].As<std::string>();
    users.push_back({
        id,
        name,
        surname,
        email,
    });
  }
  const auto res_json = formats::json::ValueBuilder{users}.ExtractValue();
  return formats::json::ValueBuilder{users}.ExtractValue();
}
/// [Postgres service sample - GetValue]

/// [Postgres service sample - PostValue]
const storages::postgres::Query kInsertUser{
    "INSERT INTO logic.user(name, surname, email, password) values "
    "($1,$2,$3,$4) returning org_id",
    storages::postgres::Query::Name{"insert_user"},
};
const storages::postgres::Query kInsertOrg{
    "INSERT INTO logic.organization(org_id,org_name, number_of_workers) values "
    "($1,$2,$3)",
    storages::postgres::Query::Name{"insert_org"},
};

userver::formats::json::Value user_component::PostValue(
    const userver::formats::json::Value& user,
    const userver::server::http::HttpRequest& request) const {
  storages::postgres::Transaction transaction =
      pg_cluster_->Begin("sample_transaction_insert_key_value",
                         storages::postgres::ClusterHostType::kMaster, {});
  auto name = user["name"].As<std::string>();
  auto surname = user["surname"].As<std::string>();
  auto email = user["email"].As<std::string>();
  auto password = user["password"].As<std::string>();
  auto org_name = user["organization"]["org_name"].As<std::string>();
  auto number_of_workers = user["organization"]["number_of_workers"].As<int>();

  auto password_hash = userver::crypto::hash::Sha256(password);
  auto res_user =
      transaction.Execute(kInsertUser, name, surname, email, password_hash);
  auto res = res_user[0].As<std::string>();

  auto res_org =
      transaction.Execute(kInsertOrg, res, org_name, number_of_workers);
  if (res_user.RowsAffected() && res_org.RowsAffected()) {
    transaction.Commit();
    request.SetResponseStatus(userver::server::http::HttpStatus::kCreated);
    return {};
  }
  //
  //  res = transaction.Execute(kSelectUser, user);
  //  transaction.Rollback();
  //
  //  auto result = res.AsSingleRow<std::string>();
  //  if (result != value) {
  //    request.SetResponseStatus(server::http::HttpStatus::kConflict);
  //  }

  return {};
}
/// [Postgres service sample - PostValue]

/// [Postgres service sample - DeleteValue]
userver::formats::json::Value user_component::DeleteValue(
    userver::formats::json::Value user) const {
  auto name = user["name"].As<std::string>();
  auto res = pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                                  "DELETE FROM logic.user WHERE name=$1", name);

  return {};
}
/// [Postgres service sample - DeleteValue]

}  // namespace userverApp::handlers::users
