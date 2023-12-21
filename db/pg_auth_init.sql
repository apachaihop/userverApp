DROP SCHEMA IF EXISTS auth_schema CASCADE;

CREATE SCHEMA IF NOT EXISTS auth_schema;

CREATE TABLE IF NOT EXISTS auth_schema.tokens
(
    token   TEXT PRIMARY KEY NOT NULL,
    user_id INTEGER          NOT NULL,
    scopes  TEXT[]           NOT NULL,
    updated TIMESTAMPTZ      NOT NULL DEFAULT NOW()
);
ALTER TABLE auth_schema.tokens
    ADD COLUMN name TEXT NOT NULL;
INSERT INTO auth_schema.tokens(token, user_id, scopes, name)
VALUES ('wrong-scopes-token', 1, '{"just_wrong"}', 'Bad Man'),
       ('THE_USER_TOKEN', 2, '{"read", "hello", "info"}', 'Dear User');