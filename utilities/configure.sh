#!/bin/bash

cd ~
HOME="$(pwd)"

git clone https://github.com/elanlb/cpp-web-server

sudo apt update
sudo apt install apache2

sudo a2enconf serve-cgi-bin
sudo a2enmod cgid

cd /etc/apache2
sudo sed -i "s/\/var\/www/${HOME}\/cpp-web-server\/web/" apache2.conf
sudo sed -i "s/\/var\/www/${HOME}\/cpp-web-server\/web/" sites-available/000-default.conf
sudo sed -i "s/\/usr\/lib\/cgi-bin/${HOME}\/cpp-web-server\/cgi-bin/g" conf-available/serve-cgi-bin.conf
systemctl reload apache2

sudo apt install postgresql-10
sudo apt install libpqxx-dev

cd ~/cpp-web-server/utilities
sudo -u postgres createdb cpp-web-server
sudo -u postgres psql -d cpp-web-server -f setup.sql

cd ~/cpp-web-server/cgi
c++ select.cpp -std=c++11 -pthread -lpqxx -Iinclude
cp a.out ../cgi-bin/select
c++ insert.cpp -std=c++11 -pthread -lpqxx -Iinclude
cp a.out ../cgi-bin/insert
c++ update.cpp -std=c++11 -pthread -lpqxx -Iinclude
cp a.out ../cgi-bin/update
c++ delete.cpp -std=c++11 -pthread -lpqxx -Iinclude
cp a.out ../cgi-bin/delete
rm a.out

cd ../cgi-bin
chmod o+x select
chmod o+x insert
chmod o+x update
chmod o+x delete