#! /usr/bin/python
# Copyright (C) 2014  Jun-Wei Lin <cs.castman [at] gmail [dot] com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

__version__ = '1.0'

import argparse, psycopg2, sys, hashlib


parser = argparse.ArgumentParser(formatter_class=argparse.RawDescriptionHelpFormatter, description='''
Insert a new WebApollo user into PostgreSQL DB and add read/write permissions of all tracks for the user.
Example Usage:
\tadduser.py -dbuser web_apollo_users_admin -dbname cercap_users -user abc123
\tadduser.py -dbuser web_apollo_users_admin -dbname cercap_users -user abc123 -pwd 123456 -host apollo.nal.usda.gov
\t(When connect to remote host, make sure the host accept remote connection by editing pg_hba.conf)
''')
parser.add_argument('-dbuser', help="Username used to connect database", required=True)
parser.add_argument('-dbname', help="Database name to be connected", required=True)
parser.add_argument('-host', help="Host name or IP of database server (Default: localhost)", required=False, default='localhost')
parser.add_argument('-user', help="Username to be added", required=True)
parser.add_argument('-pwd', help="Password of the new user (Default: the same as -user)", required=False)
parser.add_argument('-organism', help="Organism for which user to be added", required=True) 
#parser.add_argument('-perm', help="Permission of the new user (Default: 3)", required=False, default='3')
parser.add_argument('-v', '--version', action='version', version='%(prog)s ' + __version__)

args = parser.parse_args()

dbname = args.dbname
dbuser = args.dbuser
host = args.host
user = args.user
pwd = user
organism = args.organism
if args.pwd:
    pwd = args.pwd
#perm = args.perm # read=1, write=2, publish=4, admin=8; ex. read+write = 1+2 = 3; system admin = 1+2+4+8 = 15

# connect to apollo server with dbname 'cercap_users' and username 'postgres'
conn = psycopg2.connect('dbname=' + dbname + ' user=' + dbuser + ' host=' + host)
cur = conn.cursor()
print 'user \'%s\'' % (user, )
# If the user already exists then exit , get user_id
cur.execute("SELECT id FROM grails_user WHERE username=%s;", (user, ))
rows = cur.fetchall()
if rows:
  print 'User \'%s\' already exists and can not be inserted.' % (user)
  user_id = int(rows[0][0])
    # sys.exit(0)
else:
  # add new user
  cur.execute("SELECT max(id) FROM grails_user")
  rows = cur.fetchall();
  max_id = rows[0][0]+1;
  print 'max id \'%s\' ' % (max_id)
  hashedpwd = hashlib.sha256(pwd.encode('ascii')).hexdigest();
  print(hashedpwd)
  cur.execute("INSERT INTO grails_user (id,version, first_name, last_name,username, password_hash) VALUES (%s, %s, %s, %s, %s, %s)", (max_id,'1', user, user, user, hashedpwd, ))
  cur.execute("SELECT id FROM grails_user WHERE username=%s;", (user, ))
  rows = cur.fetchall()
  user_id = int(rows[0][0])
  print 'user_id lastrowid \'%s\' ' % (user_id, )
  print 'user \'%s\' added to the grails_user table ' % (user)

#Now add user to the group

user_group = organism+'_USER';
cur.execute("select id from user_group where name=%s;", (user_group, ));
rows = cur.fetchall();
group_id = rows[0][0];

#if group id exists then check user in user_group_users table if not insert it
if group_id:
   print 'group_id \'%s\' exists' % (group_id)
   cur.execute("select user_id from user_group_users where user_id=%s and user_group_id=%s;", (user_id, group_id, ))
   rows = cur.fetchall();
   if rows:
      # user is in group then update permission table.
      print 'user_id \'%s\' already exists for this group \'%s\'' % (user_id, group_id, )
   else:
      #Then insert the user_id n group_id in user_group_users table
      cur.execute("INSERT INTO user_group_users (user_id, user_group_id) VALUES(%s, %s)", (user_id, group_id, ));
      print  'user \'%s\' n group \'%s\' inserted into user_group_users table.' %(user, group_id)

# add permission for this user
genus = 'Amyelois'
species = 'transitella'
organism_id = '4016'
#cur.execute("INSERT INTO permission (id, version, organism_id, class, group_id, permissions, user_id) VALUES(%s, %s, %s, %s, %s, %s, %s)", (max_perm_id, '1', organism_id, 'org.bbop.apollo.UserOrganismPermission', group_id, permissions, user_id, ))


# commands to remove a user
#cur.execute("DELETE FROM permissions WHERE user_id=%s;", (str(user_id),))
#cur.execute("DELETE FROM users WHERE user_id=%s;", (str(user_id),))

conn.commit()
cur.close()
conn.close()
