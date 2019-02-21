CREATE DATABASE "cpp-web-server";
CREATE ROLE cgi WITH ENCRYPTED PASSWORD 'password';

CREATE TABLE employees (employeeid integer, fullname varchar(256), homeaddress varchar(256), emailaddress varchar(256), salary integer);
GRANT SELECT, INSERT, UPDATE, DELETE ON TABLE employees TO cgi;