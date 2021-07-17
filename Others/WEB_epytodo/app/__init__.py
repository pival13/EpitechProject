from flask import Flask
#import pymysql as sql

app = Flask(__name__)
app.config.from_object('config')
#mysql = sql.connect(host=app.config['DATABASE_HOST'], unix_socket=app.config['DATABASE_SOCK'], user=app.config['DATABASE_USER'], passwd=app.config['DATABASE_PASS'], db=app.config['DATABASE_NAME'])
user = {'name':'', 'id':-1}

from app import views