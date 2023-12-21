//
// Created by andrey on 12.11.23.
//

#ifndef USERVERAPP_USER_COMPONENT_HPP
#define USERVERAPP_USER_COMPONENT_HPP
#include <userver/components/component.hpp>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/server/handlers/http_handler_json_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utest/using_namespace_userver.hpp>
#include <userver/utils/fixed_array.hpp>

namespace userverApp::handlers::users {
class user_component final
    : public userver::server::handlers::HttpHandlerJsonBase {
 public:
  static constexpr std::string_view kName = "handler-user";

  user_component(const userver::components::ComponentConfig& config,
                 const userver::components::ComponentContext& context);

  formats::json::Value HandleRequestJsonThrow(
      const server::http::HttpRequest& request,
      const formats::json::Value& user,
      server::request::RequestContext& context) const override {
    GetRequestJson(context);
    switch (request.GetMethod()) {
      case userver::server::http::HttpMethod::kGet:
        return GetValue(request);
      case userver::server::http::HttpMethod::kPost:
        return PostValue(user, request);
      case userver::server::http::HttpMethod::kDelete:
        return DeleteValue(user);
      default:
        throw userver::server::handlers::ClientError(
            userver::server::handlers::ExternalBody{
                fmt::format("Unsupported method {}", request.GetMethod())});
    }
  }

 private:
  userver::formats::json::Value GetValue(
      const userver::server::http::HttpRequest& request) const;
  userver::formats::json::Value PostValue(
      const userver::formats::json::Value&,
      const userver::server::http::HttpRequest& request) const;
  userver::formats::json::Value DeleteValue(
      userver::formats::json::Value) const;

  storages::postgres::ClusterPtr pg_cluster_;
};
}  // namespace userverApp::handlers::users

#endif  // USERVERAPP_USER_COMPONENT_HPP
