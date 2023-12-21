INSERT INTO auth_schema.tokens(token, scopes, name)
VALUES ('wrong-scopes-token', '{"just_wrong"}', 'Bad Man'),
       ('THE_USER_TOKEN', '{"read", "hello", "info"}', 'Dear User');

INSERT INTO logic.user(name, surname, email, password)
values ('some name', 'some surname', 'some@email.com', '30102003San');

