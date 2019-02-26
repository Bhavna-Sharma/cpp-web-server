## Requirements
- Ubuntu 18.04.2 or similar
- Internet connection

## Steps
Follow the steps in order and your installation should work. You might consider the install script, located at `utilities/configure.sh`.

### Add project
Clone repo
- `$ git clone https://github.com/elanlb/cpp-web-server`

### Webserver setup
Install Apache
- `$ sudo apt update`
- `$ sudo apt install apache2`

Enable CGI
- `$ sudo a2enconf serve-cgi-bin`
- `$ sudo a2enmod cgid`

Set up directories
- `$ cd /etc/apache2`
- `$ sudo nano apache2.conf`
  - change `<Directory /var/www>` to `<Directory /home/username/cpp-web-server/web>`
- `$ sudo nano sites-available/000-default.conf`
  - change `DocumentRoot /var/www` to `DocumentRoot /home/username/cpp-web-server/web`
- `$ sudo nano conf-available/serve-cgi-bin.conf`
  - change `ScriptAlias /cgi-bin/ /usr/lib/cgi-bin/` to `ScriptAlias /cgi-bin /home/username/cpp-web-server/cgi-bin`
  - change `<Directory "...` to `<Directory "/home/username/cpp-web-server/cgi-bin">`

Reload Apache
- `$ systemctl reload apache2` and enter password

### Database setup
Install database
- `$ sudo apt install postgresql-10`

Install libpqxx
- `$ sudo apt install libpqxx-dev`

Set up database
- `$ cd ~/cpp-web-server/utilities`
- `$ sudo -u postgres createdb cpp-web-server`
- `$ sudo -u postgres psql -d cpp-web-server -f setup.sql`

### Build
Create binaries
- `$ cd ~/cpp-web-server/cgi`
- `$ c++ select.cpp -std=c++11 -lpqxx -o ../cgi-bin/select`
- `$ c++ insert.cpp -std=c++11 -lpqxx -o ../cgi-bin/insert`
- `$ c++ update.cpp -std=c++11 -lpqxx -o ../cgi-bin/update`
- `$ c++ delete.cpp -std=c++11 -lpqxx -o ../cgi-bin/delete`

Set up permissions
- `$ cd ../cgi-bin`
- `$ chmod o+x select`
- `$ chmod o+x insert`
- `$ chmod o+x update`
- `$ chmod o+x delete`