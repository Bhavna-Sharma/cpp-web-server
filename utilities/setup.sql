CREATE ROLE cgi WITH ENCRYPTED PASSWORD 'password';

CREATE TABLE employees (employeeid integer, fullname varchar(256), homeaddress varchar(256), emailaddress varchar(256), salary integer);
GRANT SELECT, INSERT, UPDATE, DELETE ON TABLE employees TO cgi;

INSERT INTO employees (employeeid, fullname, homeaddress, emailaddress, salary) VALUES
    (1, 'Robbie Nelson', '50 50th St', 'rnelson@example.com', 50000),
    (2, 'Cole Rosel', '60 55th St', 'crosel@example.com', 60000),
    (3, 'Deon Fabre', '70 60th St', 'dfabre@example.com', 70000),
    (4, 'Mariano Rosenberry', '80 65th St', 'mrosenberry@example.com', 80000),
    (5, 'Kyle Concannon', '90 70th St', 'kconcannon@example.com', 90000),
    (6, 'Basil Erickson', '100 75th St', 'berickson@example.com', 100000);