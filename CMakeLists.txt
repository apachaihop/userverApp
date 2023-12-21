cmake_minimum_required(VERSION 3.12)
project(userverApp CXX)

include(third_party/userver/cmake/SetupEnvironment.cmake)
include(GNUInstallDirs)
set(USERVER_FEATURE_PATCH_LIBPQ 0)
set(USERVER_FEATURE_REDIS 0)
SET(USERVER_FEATURE_GRPC 0)
set(USERVER_DOWNLOAD_PACKAGES 1)
set(USERVER_FEATURE_STACKTRACE 0)
set(USERVER_SANITIZE 0)
set(CPP_JWT_BUILD_TESTS OFF)
set(CPP_JWT_BUILD_EXAMPLES OFF)
add_subdirectory(third_party/userver)
CPMAddPackage("gh:arun11299/cpp-jwt#v1.4")
CPMAddPackage("gh:nlohmann/json#v3.11.3")

# Common sources
add_library(${PROJECT_NAME}_objs OBJECT
    src/hello.hpp
    src/hello.cpp
        src/user_component.cpp
        src/user_component.hpp
        src/user_info_cache.hxx
        src/auth/auth_bearer.cxx
        src/auth/auth_bearer.hxx
        src/DTO/user.hpp
        src/DTO/user.cpp
        src/DTO/worker.hpp
        src/DTO/organization.hpp
        src/utils/jwt.cpp
        src/utils/jwt.hpp
        src/handlers/user/user_login.hpp
        src/handlers/user/user_login.cpp
        src/handlers/user/user_register.hpp
        src/handlers/user/user_register.cpp
        src/handlers/user/user_update.hpp
        src/handlers/user/user_update.cpp
        src/handlers/user/user_delete.hpp
        src/handlers/user/user_delete.cpp
        src/handlers/organization/organization_delete.cpp
        src/handlers/organization/organization_delete.hpp
        src/handlers/organization/organization_update.cpp
        src/handlers/organization/organization_update.hpp
        src/handlers/organization/organization_get_workers.hpp
        src/handlers/organization/organization_get_workers.cpp
        src/db/sql.hpp
        src/DTO/worker.cpp
        src/DTO/organization.cpp
        src/DTO/workstation.cpp
        src/DTO/workstation.hpp
        src/DTO/trafic_usage.hpp
        src/DTO/trafic_usage.cpp
        src/DTO/services.cpp
        src/DTO/services.hpp
        src/handlers/worker/worker_get.hpp
        src/handlers/worker/worker_get.cpp
        src/handlers/worker/worker_delete.hpp
        src/handlers/worker/worker_insert.hpp
        src/handlers/worker/worker_insert.cpp
        src/handlers/worker/worker_update.cpp
        src/handlers/worker/worker_update.hpp
        src/handlers/worker/worker_get_workstations.cpp
        src/handlers/worker/worker_get_workstations.hpp
        src/handlers/worker/worker_get_traffic_usage.hpp
        src/handlers/worker/worker_get_traffic_usage.cpp
        src/handlers/worker/worker_get_service_traffic_usage.hpp
        src/handlers/worker/worker_get_service_traffic_usage.cpp
        src/handlers/worker/worker_delete.cpp
        src/handlers/workstation/workstation_get.cpp
        src/handlers/workstation/workstation_get.hpp
        src/handlers/workstation/workstation_delete.cpp
        src/handlers/workstation/workstation_delete.hpp
        src/handlers/workstation/workstation_update.cpp
        src/handlers/workstation/workstation_update.hpp
        src/handlers/workstation/workstation_insert.cpp
        src/handlers/workstation/workstation_insert.hpp
        src/DTO/worker_traffic.cpp
        src/DTO/worker_traffic.hpp
        src/handlers/services/service_delete.cpp
        src/handlers/services/service_delete.hpp
        src/handlers/services/service_insert.hpp
        src/handlers/services/service_insert.cpp
        src/handlers/services/service_update.cpp
        src/handlers/services/service_update.hpp
        src/handlers/services/service_get.cpp
        src/handlers/services/service_get.hpp
        src/handlers/trafic_usage/traffic_usage_get.cpp
        src/handlers/trafic_usage/traffic_usage_get.hpp
        src/handlers/trafic_usage/traffic_usage_delete.cpp
        src/handlers/trafic_usage/traffic_usage_delete.hpp
        src/handlers/trafic_usage/traffic_usage_insert.cpp
        src/handlers/trafic_usage/traffic_usage_insert.hpp
        src/handlers/trafic_usage/traffic_usage_update.cpp
        src/handlers/trafic_usage/traffic_usage_update.hpp


)
target_link_libraries(${PROJECT_NAME}_objs PUBLIC cpp-jwt::cpp-jwt userver-core userver-postgresql nlohmann_json::nlohmann_json)


# The Service
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs)


# Unit Tests
add_executable(${PROJECT_NAME}_unittest
    src/hello_test.cpp
)
target_link_libraries(${PROJECT_NAME}_unittest PRIVATE ${PROJECT_NAME}_objs userver-utest)
add_google_tests(${PROJECT_NAME}_unittest)


# Benchmarks
add_executable(${PROJECT_NAME}_benchmark
    src/hello_benchmark.cpp
)
target_link_libraries(${PROJECT_NAME}_benchmark PRIVATE ${PROJECT_NAME}_objs userver-ubench)
add_google_benchmark_tests(${PROJECT_NAME}_benchmark)


# Functional Tests
include(UserverTestsuite)

userver_testsuite_add_simple(
    REQUIREMENTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/requirements.txt"
)


# Install
if(DEFINED ENV{PREFIX})
  message(STATUS "Set install prefix: $ENV{PREFIX}")
  file(TO_CMAKE_PATH "$ENV{PREFIX}" PREFIX_PATH)
  set(CMAKE_INSTALL_PREFIX ${PREFIX_PATH})
endif()

file(GLOB CONFIGS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/configs/*.yaml ${CMAKE_CURRENT_SOURCE_DIR}/configs/*.json)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT ${PROJECT_NAME})
install(FILES ${CONFIGS_FILES} DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/${PROJECT_NAME} COMPONENT ${PROJECT_NAME})
