//
// Created by andrey on 17.12.23.
//

#include "worker_update.hpp"
#include "../../DTO/worker.hpp"
#include "../../db/sql.hpp"
#include "userver/formats/serialize/common_containers.hpp"
#include "userver/logging/log.hpp"
namespace userverApp::handlers::worker {
userverApp::handlers::worker::worker_update::worker_update(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerJsonBase(config, context),
      pg_cluster_(context.FindComponent<components::Postgres>("postgres-db-1")
                      .GetCluster()) {
  using storages::postgres::ClusterHostType;
}
formats::json::Value worker_update::HandleRequestJsonThrow(
    const server::http::HttpRequest& request,
    const formats::json::Value& worker,
    server::request::RequestContext&) const {
  const auto id = worker["id"].As<std::string>();
  const std::optional<std::string> name =
      worker["name"].As<std::optional<std::string>>();
  const std::optional<std::string> surname =
      worker["surname"].As<std::optional<std::string>>();
  const std::optional<std::string> working_time_start =
      worker["working_time_start"].As<std::optional<std::string>>();
  const std::optional<std::string> working_time_end =
      worker["working_time_end"].As<std::optional<std::string>>();

  auto worker_res =
      pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                           userverApp::sql::kUpdateWorker.data(), name, surname,
                           working_time_start, working_time_end, id);
  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
  worker_res =
      pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                           userverApp::sql::kSelectWorkerById.data(), id);
  auto response = worker_res.AsSingleRow<userverApp::entity::worker>(
      userver::storages::postgres::kRowTag);
  userver::formats::json::ValueBuilder builder;
  builder["worker"] = response;
  auto resultResponse = *(builder.begin());
  return resultResponse.ExtractValue();
}

}  // namespace userverApp::handlers::worker