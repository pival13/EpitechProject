from app import app, user
from app.controller import Controller
from flask import request

@app.route('/', methods=['GET'])
def main_route():
    return Controller().main()

@app.route('/', methods=['POST'])
def test():
    print(request.get_data(), request.stream)
    return ""

@app.route('/register/', methods=['POST'])
def register_route(): 
    return Controller().register(request.form)

@app.route('/signin/', methods=['POST'])
def signin_route():
    return Controller().login(request.form)

@app.route('/signout/', methods=['POST'])
def signout_route():
    return Controller().logout()

@app.route('/user/', methods=['GET'])
def user_route():
    return Controller().user()

@app.route('/user/task/', methods=['GET'])
def tasks_route():
    return Controller().all_task()

@app.route('/user/task/<int:id>', methods=['GET'])
def task_route(id):
    return Controller().one_task(id)

@app.route('/user/task/<int:id>', methods=['POST'])
def change_task_route(id):
    return Controller().change_task(id, request.form)

@app.route('/user/task/<int:id_task>/del_user/<username>', methods=['POST'])
def delete_user_task_route(id_task, username):
    return Controller().del_user_from_task(id_task, username)

@app.route('/user/task/<int:id_task>/add_user/', methods=['POST'])
def add_user_task_route(id_task):
    return Controller().add_user_to_task(id_task, request.form)

@app.route('/user/task/add', methods=['POST'])
def add_task_route():
    return Controller().add_task(request.form)

@app.route('/user/task/add/', methods=['GET'])
def page_add_task_route():
    return Controller().page_add_task()

@app.route('/user/task/del/<int:id>', methods=['POST'])
def del_task_route(id):
    return Controller().del_task(id)
