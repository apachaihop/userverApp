//
// Created by andrey on 16.12.23.
//

#ifndef USERVERAPP_USER_UPDATE_HPP
#define USERVERAPP_USER_UPDATE_HPP

#include "userver/components/component.hpp"
#include "userver/formats/serialize/common_containers.hpp"
#include "userver/server/handlers/http_handler_json_base.hpp"
#include "userver/storages/postgres/cluster.hpp"
#include "userver/storages/postgres/component.hpp"
#include "userver/utest/using_namespace_userver.hpp"
#include "userver/utils/fixed_array.hpp"

namespace userverApp::handlers::user {
class user_update final
    : public userver::server::handlers::HttpHandlerJsonBase {
 public:
  static constexpr std::string_view kName = "handler-user-update";

  user_update(const userver::components::ComponentConfig& config,
              const userver::components::ComponentContext& context);

  formats::json::Value HandleRequestJsonThrow(
      const server::http::HttpRequest& request,
      const formats::json::Value& user,
      server::request::RequestContext&) const override;

 private:
  storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace userverApp::handlers::user

#endif  // USERVERAPP_USER_UPDATE_HPP
