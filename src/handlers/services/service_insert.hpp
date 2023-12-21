//
// Created by andrey on 19.12.23.
//

#ifndef USERVERAPP_SERVICE_INSERT_HPP
#define USERVERAPP_SERVICE_INSERT_HPP

#include "userver/components/component.hpp"
#include "userver/formats/serialize/common_containers.hpp"
#include "userver/server/handlers/http_handler_json_base.hpp"
#include "userver/storages/postgres/cluster.hpp"
#include "userver/storages/postgres/component.hpp"
#include "userver/utest/using_namespace_userver.hpp"

namespace userverApp::handlers::service {
class service_insert final
    : public userver::server::handlers::HttpHandlerJsonBase {
 public:
  static constexpr std::string_view kName = "handler-service-insert";

  service_insert(const userver::components::ComponentConfig& config,
                 const userver::components::ComponentContext& context);

  formats::json::Value HandleRequestJsonThrow(
      const server::http::HttpRequest& request,
      const formats::json::Value& service,
      server::request::RequestContext&) const override;

 private:
  storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace userverApp::handlers::service
#endif  // USERVERAPP_SERVICE_INSERT_HPP
