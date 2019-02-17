clone repo
`$ git clone https://github.com`

install apache
`$ sudo apt-get update`
`$ sudo apt-get install apache2`

enable cgi
`$ sudo a2enconf serve-cgi-bin`
`$ sudo a2enmod cgid`

make links
`$ cd /var/www`
`$ sudo rm -r html`
`$ sudo ln -s ~/project-manager/web/html/ html`
`$ sudo ln -s ~/project-manager/web/js/ js`
`$ sudo ln -s ~/project-manager/web/css/ css`
`$ sudo ln -s ~/project-manager/core/ core`

configure apache
`$ cd /etc/apache2/conf-enabled`
`$ sudo nano serve-cgi-bin.conf`
instructions to link to the folder

install database
`$ sudo apt-get install postgresql-10`