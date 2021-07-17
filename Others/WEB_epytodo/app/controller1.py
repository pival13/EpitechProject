#view send json to controller
#controller send html

from app import app, sql, user
from app.models import User, Task
from flask import redirect, url_for, jsonify

class Controller:

    def register(self, form):
        User().create_user(form['login'], form['passwd'])
        user['name'] = form['login']
        user['id'] = User().get_id(form['login'])
        jsonify({"result":"account created"})
        return redirect(url_for('main_route'))
    
    def login(self, form):
        if not form['login'] or not form['passwd']:
            return jsonify({"error":"internl error"})
        if User().check_username(form['login']) and User().check_password(form['login'], form['passwd']):
            user['name'] = form['login']
            user['id'] = User().get_id(user['name'])
            if user['id'] == -1:
                user['name'] = ""
                return jsonify({"error":"internal error"})
            else:
                return jsonify({"result":"signin successful"})
        else:
            return jsonify({"error":"login or password does not match"})
    
    def logout(self):
        user['name'] = ""
        user['id'] = -1
        return jsonify({"result":"signout successful"})
    
    def user(self):
        if user['id'] == -1:
            return jsonify({"error":"you must be logged in"})
        return jsonify({"result" : {"username" : user["name"], "id" : user["id"]}})
    
    def all_task(self):
        if user['id'] == - 1:
            return jsonify({"error":"you must be logged in"})
        tasks = User().get_task(user[id])
        if tasks:
            return jsonify({"result":{"tasks": tasks}})
        else:
            return jsonify({"error":"internal error"})
    
    def one_task(self, id):
        if user['id'] == - 1:
            return jsonify({"error":"you must be logged in"})
        if not Task().check_task(id):
            return jsonify({"error": "task id does not exist"})
        task = Task().get_task_with_id(id)
        if task:
            return jsonify({"result":task})
        else:
            return jsonify({"error":"internal error"})

    def change_task(self, id, form):
        if user['id'] == - 1:
            return jsonify({"error":"you must be logged in"})
        if not Task().check_task(id):
            return jsonify({"error": "task id does not exist"})
        Task().edit_task(id, form['title'], form['status'], form['begin'], form['end'], User().get_id(form['username']))
        return jsonify({"result": "update done"})

    def add_task(self, form):
        if user['id'] == - 1:
            return jsonify({"error":"you must be logged in"})
        Task().create_task(form["title"], form['status'], form['begin'], form['end'], user['id'])
        return jsonify({"result":"new task added"})

    def del_task(self, id):
        Task().delete_task(id)
        if user['id'] == - 1:
            return jsonify({"error":"you must be logged in"})
        if not Task().check_task(id):
            return jsonify({"error":"task id does not exist"})
        Task().delete_task(id)
        return jsonify({"result":"task deleted"})
