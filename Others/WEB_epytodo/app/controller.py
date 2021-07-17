#view send json to controller
#controller send html

from app import app, user
from app.models import User, Task
from flask import redirect, url_for, jsonify, render_template

class Controller:

    def main(self):
        return render_template("main_page.html", user=user)

    def register(self, form):
        User().create_user(form['login'], form['passwd'])
        user['name'] = form['login']
        user['id'] = User().get_id(form['login'])
        return redirect(url_for('main_route'))
    
    def login(self, form):
        if User().check_username(form['login']) and User().check_password(form['login'], form['passwd']):
            user['name'] = form['login']
            user['id'] = User().get_id(user['name'])
            if user['id'] == -1:
                user['name'] = ""
                print({"error":"internal error"})
            else:
                print({"result":"signin successful"})
        else:
            print({"error":"login or password does not match"})
        return redirect(url_for('main_route'))
    
    def logout(self):
        user['name'] = ""
        user['id'] = -1
        print({"result":"signout successful"})
        return redirect(url_for('main_route'))
    
    def user(self):
        if user['id'] == -1:
            print({"error":"you must be logged in"})
            return redirect(url_for('main_route'))
        else:
            print({"result" : {"username" : user["name"], "id" : user["id"]}})
        return render_template("user_page.html", user=user)
    
    def all_task(self):
        if user['id'] == - 1:
            print({"error":"you must be logged in"})
            return redirect(url_for('main_route'))
        tasks = Task().get_all_tasks()
        tasks_id = User().get_task(user['id'])
        task = []
        no_task = []
        for one_task in tasks:
            mybool = False
            for id in tasks_id:
                if one_task[0] == id[0]:
                    task.append(Task().get_task_with_id(one_task[0]))
                    mybool = True
            if mybool == False:
                no_task.append(Task().get_task_with_id(one_task[0]))       
        if task:
            print({"result":{"tasks": task}})
        else:
            print({"error":"internal error"})
        return render_template("task_page.html", user=user, tasks=task, no_tasks=no_task)
    
    def one_task(self, id):
        if user['id'] == - 1:
            print({"error":"you must be logged in"})
            return redirect(url_for('main_route'))
        if not Task().check_task(id):
            print({"error": "task id does not exist"})
            return redirect(url_for('tasks_route'))
        task = Task().get_task_with_id(id)
        users = Task().get_user(id)
        use = []
        for user_id in users:
            if User().check_user_id(user_id[0]):
                use.append(User().get_user_with_id(user_id[0]))
        if task:
            print({"result":task})
            return render_template("one_task_page.html", user=user, task=task, users=use)
        else:
            print({"error":"internal error"})
            return redirect(url_for('tasks_route'))

    def change_task(self, id, form):
        if user['id'] == - 1:
            print({"error":"you must be logged in"})
            return redirect(url_for('main_route'))
        if not Task().check_task(id):
            print({"error": "task id does not exist"})
            return redirect(url_for('tasks_route'))
        Task().edit_task(id, form['title'], form['status'], form['begin'], form['end'])
        print({"result": "update done"})
        return redirect(url_for('task_route', id=id))

    def add_task(self, form):
        if user['id'] == - 1:
            print({"error":"you must be logged in"})
            return redirect(url_for('main_route'))
        Task().create_task(form["title"], form['status'], form['begin'], form['end'])
        task = Task().get_last_task()
        Task().add_user_to_task(task[0], user['id'])
        print({"result":"new task added"})
        return redirect(url_for('tasks_route'))

    def del_task(self, id):
        if user['id'] == - 1:
            print({"error":"you must be logged in"})
            return redirect(url_for('main_route'))
        if not Task().check_task(id):
            print({"error":"task id does not exist"})
            return redirect(url_for('tasks_route'))
        Task().delete_task(id)
        print({"result":"task deleted"})
        return redirect(url_for('tasks_route'))

    def del_user_from_task(self, task_id, username):
        if user['id'] == - 1:
            print({"error":"you must be logged in"})
            return redirect(url_for('main_route'))
        if not Task().check_task(task_id):
            print({"error": "task id does not exist"})
            return redirect(url_for('task_route', id=task_id))
        if not User().check_username(username):
            print({"error": "user does not exist"})
            return redirect(url_for('task_route', id=task_id))
        user_id = User().get_id(username)
        if not User().has_task(user_id, task_id):
            print({"error": "user does not have this task"})
            return redirect(url_for('task_route', id=task_id))
        Task().remove_user_from_task(task_id, user_id)
        print({"result":"user removed"})
        return redirect(url_for('task_route', id=task_id))
        
    def add_user_to_task(self, task_id, form):
        username = form['new_user']
        if user['id'] == - 1:
            print({"error":"you must be logged in"})
            return redirect(url_for('main_route'))
        if not Task().check_task(task_id):
            print({"error": "task id does not exist"})
            return redirect(url_for('task_route', id=task_id))
        if not User().check_username(username):
            print({"error": "user does not exist"})
            return redirect(url_for('task_route', id=task_id))
        user_id = User().get_id(username)
        if User().has_task(user_id, task_id):
            print({"error": "user has already this task"})
            return redirect(url_for('task_route', id=task_id))
        Task().add_user_to_task(task_id, user_id)
        print({"result":"user has been add"})
        return redirect(url_for('task_route', id=task_id))
        
    def page_add_task(self):
        if user['id'] == - 1:
            print({"error":"you must be logged in"})
            return redirect(url_for('main_route'))
        return render_template('create_task_page.html', user=user)