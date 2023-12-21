create schema logic;
CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

create table logic.user
(
    user_id  uuid PRIMARY KEY            DEFAULT uuid_generate_v4(),
    name     varchar(20)        not null,
    surname  varchar(20)        not null,
    email    varchar(20) unique not null,
    password varchar(36)        not null,
    org_id   uuid unique        not null default uuid_generate_v4()
);
create table logic.organization
(
    org_name          varchar(20) unique not null,
    number_of_workers int                         default (0),
    org_id            uuid               not null default uuid_generate_v4(),
    PRIMARY KEY (org_id),
    CONSTRAINT fk_organisation
        foreign key (org_id) references logic.user (org_id) ON DELETE CASCADE
);
create table logic.services
(
    service_id   uuid PRIMARY KEY default uuid_generate_v4(),
    service_name varchar(20) unique not null

);
create table logic.trafic_usage
(
    ip           varchar(12) PRIMARY KEY,
    trafic_in_kb int  not null,
    time_stamp   time not null
);

create table logic.worker
(
    worker_id      uuid PRIMARY KEY default uuid_generate_v4(),
    worker_name    varchar(20) not null,
    worker_surname varchar(20) not null,
    working_time   time        not null,
    org_id         uuid             default uuid_generate_v4(),
    constraint fk_org
        foreign key (org_id) references logic.organization (org_id)
);
create table logic.workstation
(
    ip        varchar(12) primary key,
    worker_id uuid default uuid_generate_v4(),
    constraint fk_worker
        foreign key (worker_id) references logic.worker (worker_id)

);
create table logic.service_trafic
(
    ip         varchar(12),
    service_id uuid default uuid_generate_v4(),
    primary key (service_id, ip),
    constraint fk_service
        foreign key (service_id) references logic.services (service_id) ON DELETE CASCADE,
    constraint fk_trafic
        foreign key (ip) references logic.trafic_usage (ip) ON DELETE CASCADE,
    constraint fk_ip
        foreign key (ip) references logic.workstation (ip)
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


INSERT INTO logic.user(name, surname, email, password)
values ('some name', 'some surname', 'some@email.m', '30102003San')
returning org_id;
