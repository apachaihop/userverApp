//
// Created by andrey on 17.12.23.
//

#ifndef USERVERAPP_ORGANIZATION_GET_WORKERS_HPP
#define USERVERAPP_ORGANIZATION_GET_WORKERS_HPP

#include "userver/components/component.hpp"
#include "userver/formats/serialize/common_containers.hpp"
#include "userver/server/handlers/http_handler_json_base.hpp"
#include "userver/storages/postgres/cluster.hpp"
#include "userver/storages/postgres/component.hpp"
#include "userver/utest/using_namespace_userver.hpp"

namespace userverApp::handlers::organization {
class organization_get_workers final
    : public userver::server::handlers::HttpHandlerJsonBase {
 public:
  static constexpr std::string_view kName = "handler-organization-workers";

  organization_get_workers(
      const userver::components::ComponentConfig& config,
      const userver::components::ComponentContext& context);

  formats::json::Value HandleRequestJsonThrow(
      const server::http::HttpRequest& request, const formats::json::Value& org,
      server::request::RequestContext&) const override;

 private:
  storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace userverApp::handlers::organization
#endif  // USERVERAPP_ORGANIZATION_GET_WORKERS_HPP
