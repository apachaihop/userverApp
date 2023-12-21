create schema logic;
CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

create table logic.users
(
    user_id   TEXT PRIMARY KEY            DEFAULT uuid_generate_v4(),
    name      varchar(20)        not null,
    surname   varchar(20)        not null,
    email     varchar(20) unique not null,
    password  varchar(256)       not null,
    role_name varchar(15)                 default 'USER',
    org_id    TEXT unique        not null default uuid_generate_v4()


);
create table logic.registration_time
(
    user_id           TEXT PRIMARY KEY default uuid_generate_v4(),
    registration_date DATE not null,
    registration_time TIME not null,
    constraint fk_user
        foreign key (user_id) references logic.users (user_id) ON DELETE CASCADE
);
create function logic.registration_time()
    returns trigger as
$$
begin
    insert into logic.registration_time(user_id, registration_date, registration_time)
    values (new.user_id, now(), now());
    return null;
end;
$$ language plpgsql;

create trigger registration_time_trigger
    after insert
    on logic.users
    for each row
execute procedure logic.registration_time();

create table logic.organizations
(
    org_name varchar(20) unique not null,
    org_id   TEXT               not null default uuid_generate_v4(),
    PRIMARY KEY (org_id),
    CONSTRAINT fk_organisation
        foreign key (org_id) references logic.users (org_id) ON DELETE CASCADE
);
create table logic.services
(
    service_id   TEXT PRIMARY KEY default uuid_generate_v4(),
    service_name varchar(20) unique not null

);
create table logic.traffic_usage
(
    ip            varchar(12) PRIMARY KEY,
    traffic_in_kb int  not null,
    time_stamp    time not null
);

create table logic.workers
(
    worker_id          TEXT PRIMARY KEY default uuid_generate_v4(),
    worker_name        varchar(20) not null,
    worker_surname     varchar(20) not null,
    working_time_start time        not null,
    working_time_end   time        not null,
    org_id             TEXT             default uuid_generate_v4(),
    constraint fk_org
        foreign key (org_id) references logic.organizations (org_id)
);
create table logic.workstations
(
    ip        varchar(12) primary key,
    worker_id TEXT default uuid_generate_v4(),
    constraint fk_worker
        foreign key (worker_id) references logic.workers (worker_id)

);
create table logic.service_traffic
(
    ip         varchar(12),
    service_id TEXT default uuid_generate_v4(),
    primary key (service_id, ip),
    constraint fk_service
        foreign key (service_id) references logic.services (service_id),
    constraint fk_traffic
        foreign key (ip) references logic.traffic_usage (ip),
    constraint fk_ip
        foreign key (ip) references logic.workstations (ip)
);


CREATE SCHEMA IF NOT EXISTS auth_schema;

CREATE TABLE IF NOT EXISTS auth_schema.tokens
(
    token   TEXT PRIMARY KEY NOT NULL,
    user_id uuid             NOT NULL DEFAULT uuid_generate_v4(),
    scopes  TEXT[]           NOT NULL,
    updated TIMESTAMPTZ      NOT NULL DEFAULT NOW(),
    name    TEXT             not null
);
INSERT INTO auth_schema.tokens(token, scopes, name)
VALUES ('wrong-scopes-token', '{"just_wrong"}', 'Bad Man'),
       ('THE_USER_TOKEN', '{"read", "hello", "info"}', 'Dear User');


INSERT INTO logic.users(name, surname, email, password)
values ('some name', 'some surname', 'some@email.m', '30102003San')
returning org_id;
