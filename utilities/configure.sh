#!/bin/bash

if [ $(id -u) != 0 ]
    then
    echo "Please run as root"
    exit
fi

git clone https://github.com/elanlb/cpp-web-server

apt update
apt install apache2

a2enconf serve-cgi-bin
a2enmod cgid

cd /etc/apache2
sed -i "s|/var/www|${HOME}/cpp-web-server/web|" apache2.conf
sed -i "s|/var/www|${HOME}/cpp-web-server/web|" sites-available/000-default.conf
sed -i "s|/usr/lib/cgi-bin|${HOME}/cpp-web-server/cgi-bin|g" conf-available/serve-cgi-bin.conf
systemctl reload apache2

apt install postgresql-10
apt install libpqxx-dev

cd ~/cpp-web-server/utilities
sudo -u postgres createdb cpp-web-server
sudo -u postgres psql -d cpp-web-server -f setup.sql

cd ~/cpp-web-server/cgi
c++ select.cpp -std=c++11 -lpqxx -o ../cgi-bin/select
c++ insert.cpp -std=c++11 -lpqxx -o ../cgi-bin/insert
c++ update.cpp -std=c++11 -lpqxx -o ../cgi-bin/update
c++ delete.cpp -std=c++11 -lpqxx -o ../cgi-bin/delete

cd ../cgi-bin
chmod o+x select
chmod o+x insert
chmod o+x update
chmod o+x delete