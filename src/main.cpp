#include <userver/clients/http/component.hpp>
#include <userver/components/fs_cache.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/http_handler_static.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/utils/daemon_run.hpp>

#include "./auth/auth_bearer.hxx"
#include "handlers/organization/organization_delete.hpp"
#include "handlers/organization/organization_get_workers.hpp"
#include "handlers/organization/organization_update.hpp"
#include "handlers/services/service_delete.hpp"
#include "handlers/services/service_get.hpp"
#include "handlers/services/service_insert.hpp"
#include "handlers/services/service_update.hpp"
#include "handlers/user/user_delete.hpp"
#include "handlers/user/user_login.hpp"
#include "handlers/user/user_register.hpp"
#include "handlers/user/user_update.hpp"
#include "handlers/worker/worker_delete.hpp"
#include "handlers/worker/worker_get.hpp"
#include "handlers/worker/worker_get_service_traffic_usage.hpp"
#include "handlers/worker/worker_get_traffic_usage.hpp"
#include "handlers/worker/worker_get_workstations.hpp"
#include "handlers/worker/worker_insert.hpp"
#include "handlers/worker/worker_update.hpp"
#include "handlers/workstation/workstation_delete.hpp"
#include "handlers/workstation/workstation_get.hpp"
#include "handlers/workstation/workstation_insert.hpp"
#include "handlers/workstation/workstation_update.hpp"
#include "hello.hpp"
#include "user_component.hpp"
#include "user_info_cache.hxx"

int main(int argc, char* argv[]) {
  server::handlers::auth::RegisterAuthCheckerFactory(
      "bearer", std::make_unique<samples::pg::CheckerFactory>());

  auto component_list = userver::components::MinimalServerComponentList()
                            .Append<userver::server::handlers::Ping>()
                            .Append<userver::components::TestsuiteSupport>()
                            .Append<userver::components::HttpClient>()
          .Append<userver::server::handlers::TestsControl>()
          .Append<server::handlers::HttpHandlerStatic>()
          .Append<components::FsCache>("fs-cache-main")
          .Append<samples::pg::AuthCache>()
          .Append<userverApp::handlers::users::user_component>()
          .Append<userverApp::handlers::user::user_login>()
          .Append<userverApp::handlers::user::user_register>()
          .Append<userverApp::handlers::user::user_update>()
          .Append<userverApp::handlers::user::user_delete>()
          .Append<userverApp::handlers::organization::organization_delete>()
          .Append<userverApp::handlers::organization::organization_update>()
          .Append<
              userverApp::handlers::organization::organization_get_workers>()
          .Append<userverApp::handlers::worker::worker_insert>()
          .Append<userverApp::handlers::worker::worker_update>()
          .Append<userverApp::handlers::worker::worker_get>()
          .Append<userverApp::handlers::worker::worker_delete>()
          .Append<userverApp::handlers::worker::worker_get_workstations>()
          .Append<userverApp::handlers::worker::worker_get_traffic_usage>()
          .Append<
              userverApp::handlers::worker::worker_get_service_traffic_usage>()
          .Append<userverApp::handlers::workstation::workstation_insert>()
          .Append<userverApp::handlers::workstation::workstation_get>()
          .Append<userverApp::handlers::workstation::workstation_update>()
          .Append<userverApp::handlers::workstation::workstation_delete>()
          .Append<userverApp::handlers::service::service_insert>()
          .Append<userverApp::handlers::service::service_get>()
          .Append<userverApp::handlers::service::service_delete>()
          .Append<userverApp::handlers::service::service_update>();

  userverApp::AppendHello(component_list);

  return userver::utils::DaemonMain(argc, argv, component_list);
}
