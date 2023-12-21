//
// Created by andrey on 16.12.23.
//

#ifndef USERVERAPP_SQL_HPP
#define USERVERAPP_SQL_HPP
#include <string_view>
namespace userverApp::sql {
inline constexpr std::string_view kInsertUser = R"~(
INSERT INTO logic.users (name,surname,email,password) Values ($1,$2,$3,$4)
RETURNING org_id;
)~";
inline constexpr std::string_view kDeleteUser = R"~(
DELETE FROM logic.users WHERE user_id=$1;
)~";
inline constexpr std::string_view kSelectUserByEmail = R"~(
SELECT * FROM logic.users WHERE email=$1;
)~";
inline constexpr std::string_view kSelectUserById = R"~(
SELECT * FROM logic.users WHERE user_id=$1;
)~";
inline constexpr std::string_view kSelectUserByEmailAndPassword = R"~(
SELECT * FROM logic.users WHERE email=$1 AND password=$2;
)~";
inline constexpr std::string_view kUpdateUser = R"~(
UPDATE logic.users SET
name=COALESCE($1,name),
surname=COALESCE($2,surname),
email=COALESCE($3,email),
password=COALESCE($4,password)
WHERE user_id=$5;
)~";

inline constexpr std::string_view kSelectUserRegistrationTimeById = R"~(
SELECT registration_time,name,surname FROM logic.registration_time
 JOIN logic.users
 ON logic.users.user_id=logic.registration_time.user_id
 WHERE logic.users.user_id=$1;
)~";

inline constexpr std::string_view kSelectUsersRegistrationTime = R"~(
SELECT * FROM logic.registration_time
JOIN logic.users
ON logic.users.user_id=logic.registration_time.user_id;
)~";

inline constexpr std::string_view kInsertOrganization = R"~(
INSERT INTO logic.organizations (org_id,org_name) Values ($1,$2)
)~";
inline constexpr std::string_view kDeleteOrganization = R"~(
DELETE FROM logic.organizations WHERE org_id=$1;
)~";
inline constexpr std::string_view kSelectOrganizationById = R"~(
SELECT * FROM logic.organizations WHERE org_id=$1;
)~";
inline constexpr std::string_view kSelectOrganizationByName = R"~(
SELECT * FROM logic.organizations WHERE org_name=$1;
)~";
inline constexpr std::string_view kUpdateOrganization = R"~(
UPDATE logic.organizations SET
org_name=COALESCE($1,org_name)
WHERE org_id=$2;
)~";

inline constexpr std::string_view kInsertWorker = R"~(
INSERT INTO logic.workers (org_id,worker_name,worker_surname,working_time_start,working_time_end)
 Values ($1,$2,$3,$4::time,$5::time)
)~";
inline constexpr std::string_view kDeleteWorkerById = R"~(
DELETE FROM logic.workers WHERE worker_id=$1;
)~";
inline constexpr std::string_view kSelectWorkerById = R"~(
SELECT * FROM logic.workers WHERE worker_id=$1;
)~";
inline constexpr std::string_view kSelectWorkerTrafficUsageByIdAndWorkingTime =
    R"~(
SELECT *,sum(traffic_in_kb) FROM logic.workers
JOIN logic.workstations
ON logic.workstations.worker_id=logic.workers.worker_id
JOIN logic.traffic_usage
ON logic.traffic_usage.ip=logic.workstations.ip
WHERE logic.workers.worker_id=$1
AND logic.traffic_usage.time_stamp BETWEEN
 logic.workers.working_time_start AND logic.workers.working_time_end
GROUP BY logic.workers.worker_id;
)~";
inline constexpr std::string_view
    kSelectAllWorkersByTrafficUsageForEachService = R"~(
SELECT workers.worker_id,service_name,sum(traffic_in_kb) as traffic FROM logic.workers
JOIN logic.workstation
ON logic.workstations.worker_id=logic.workers.worker_id
JOIN logic.traffic_usage
ON logic.traffic_usage.ip=logic.workstations.ip
JOIN logic.service_traffic
ON logic.service_traffic.ip=logic.workstations.ip
JOIN logic.services
ON logic.services.service_id=logic.service_traffic.service_id
WHERE logic.traffic_usage.time_stamp BETWEEN
 logic.workers.working_time_start AND logic.workers.working_time_end
where logic.workers.org_id=$1
GROUP BY logic.workers.worker_id,logic.services.service_id;
)~";
inline constexpr std::string_view kSelectWorkerByTrafficUsageForEachService =
    R"~(
SELECT service_name,sum(traffic_in_kb) as traffic FROM logic.workers
JOIN logic.workstation
ON logic.workstations.worker_id=logic.workers.worker_id
JOIN logic.traffic_usage
ON logic.traffic_usage.ip=logic.workstations.ip
JOIN logic.service_traffic
ON logic.service_traffic.ip=logic.workstations.ip
JOIN logic.services
ON logic.services.service_id=logic.service_traffic.service_id
WHERE logic.traffic_usage.time_stamp BETWEEN
 logic.workers.working_time_start AND logic.workers.working_time_end
where logic.workers.worker_id=$1
GROUP BY logic.workers.worker_id,logic.services.service_id;
)~";

inline constexpr std::string_view kSelectWorkerByName = R"~(
SELECT * FROM logic.workers WHERE worker_name=$1;
)~";
inline constexpr std::string_view kUpdateWorker = R"~(
UPDATE logic.workers SET
worker_name=COALESCE($1,worker_name),
worker_surname=COALESCE($2,worker_surname),
working_time_start=COALESCE($3,working_time_start)
working_time_end=COALESCE($4,working_time_end)
WHERE worker_id=$5;
)~";

inline constexpr std::string_view kSelectWorkersByOrgId = R"~(
SELECT * FROM logic.workers WHERE org_id=$1;
)~";

inline constexpr std::string_view kInsertWorkstation = R"~(
INSERT INTO logic.workstations (worker_id,ip) Values ($1,$2)
)~";
inline constexpr std::string_view kDeleteWorkstation = R"~(
DELETE FROM logic.workstations WHERE workstation_id=$1;
)~";
inline constexpr std::string_view kSelectWorkstationByIp = R"~(
SELECT * FROM logic.workstations WHERE ip=$1;
)~";
inline constexpr std::string_view kUpdateWorkstation = R"~(
UPDATE logic.workstations SET
ip=COALESCE($1,ip),
worker_id=COALESCE($2,worker_id)
WHERE workstation_id=$3;
)~";

inline constexpr std::string_view kSelectWorkstationsByWorkerId = R"~(
SELECT * FROM logic.workstations WHERE worker_id=$1;
)~";

inline constexpr std::string_view kInsertService = R"~(
INSERT INTO logic.services (service_name) Values ($1);
)~";
inline constexpr std::string_view kDeleteService = R"~(
DELETE FROM logic.services WHERE service_id=$1;
)~";
inline constexpr std::string_view kSelectServiceById = R"~(
SELECT * FROM logic.services WHERE service_id=$1;
)~";
inline constexpr std::string_view kSelectServiceByName = R"~(
SELECT * FROM logic.services WHERE service_name=$1;
)~";
inline constexpr std::string_view kUpdateService = R"~(
UPDATE logic.services SET
service_name=COALESCE($1,service_name)
WHERE service_id=$2;
)~";

inline constexpr std::string_view kInsertTrafficUsage = R"~(
INSERT INTO logic.traffic_usage (ip,traffic_in_kb,time_stamp) Values ($1,$2,now());
)~";
inline constexpr std::string_view kDeleteTrafficUsage = R"~(
DELETE FROM logic.traffic_usage WHERE ip=$1;
)~";
inline constexpr std::string_view kSelectTrafficUsageByIp = R"~(
SELECT traffic_in_kb,time_stamp FROM logic.traffic_usage WHERE ip=$1;
)~";
inline constexpr std::string_view kUpdateTrafficUsage = R"~(
UPDATE logic.traffic_usage SET
traffic_in_kb=COALESCE($1,traffic_in_kb),
time_stamp=COALESCE($2,time_stamp)
WHERE ip=$3;
)~";

inline constexpr std::string_view kSelectTrafficUsageByWorkerId = R"~(
SELECT ip,traffic_in_kb,time_stamp FROM logic.traffic_usage
JOIN logic.workstations
ON logic.workstations.ip=logic.traffic_usage.ip
WHERE logic.workstations.worker_id=$1;
)~";

inline constexpr std::string_view kInsertServiceTraffic = R"~(
INSERT INTO logic.service_traffic (service_id,ip) Values ($1,$2);
)~";

inline constexpr std::string_view kDeleteServiceTraffic = R"~(
DELETE FROM logic.service_traffic WHERE service_id=$1;
)~";

inline constexpr std::string_view kSelectServiceTrafficUsageByServiceName = R"~(
SELECT * FROM logic.service_traffic
JOIN logic.services
ON logic.services.service_id=logic.service_traffic.service_id
JOIN logic.traffic_usage
ON logic.traffic_usage.ip=logic.service_traffic.ip
WHERE logic.services.service_name=$1;
)~";

inline constexpr std::string_view kSelectServicesByWorkerId = R"~(
SELECT * FROM logic.service_traffic
JOIN logic.services
ON logic.services.service_id=logic.service_traffic.service_id
JOIN logic.workstations
ON logic.workstations.ip=logic.service_traffic.ip
WHERE logic.workstations.worker_id=$1;
)~";

inline constexpr std::string_view kUpdateServiceTraffic = R"~(
UPDATE logic.service_traffic SET
service_id=COALESCE($1,service_id),
ip=COALESCE($2,ip)
WHERE service_id=$3;
)~";

}  // namespace userverApp::sql
#endif  // USERVERAPP_SQL_HPP
