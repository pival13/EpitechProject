from app import mysql, user, app

class User:
    def check_username(self, username):
        cursor = mysql.cursor()
        cursor.execute("SELECT username FROM user;")
        users = cursor.fetchall()
        cursor.close()
        for use in users:
            if use[0] == username:
                return True
        return False

    def check_password(self, username, password):
        cursor = mysql.cursor()
        cursor.execute("SELECT username, password FROM user;")
        users = cursor.fetchall()
        cursor.close()
        for use in users:
            if use[0] == username and use[1] == password:
                return True
            elif use[0] == username:
                return False
        return False

    def create_user(self, username, password):
        cursor = mysql.cursor()
        cursor.execute("INSERT INTO user SET username = '" + username + "', password = '" + password + "';")
        mysql.commit()
        cursor.close()

    def get_id(self, username):
        cursor = mysql.cursor()
        cursor.execute("select user_id FROM user WHERE username = '" + username + "';")
        use = cursor.fetchall()[0][0]
        cursor.close()
        if use:
            return use
        else:
            return -1

    def has_task(self, user_id, task_id):
        cursor = mysql.cursor()
        cursor.execute("select * from user_has_task where fk_task_id = " + str(task_id) + " and fk_user_id = " +str(user_id) + ";")
        if cursor.fetchall():
            return True
        else:
            return False

    def get_task(self, user_id):
        cursor = mysql.cursor()
        cursor.execute("select fk_task_id from user_has_task where fk_user_id = " + str(user_id) + ";")
        tasks_id = cursor.fetchall()
        cursor.close()
        return tasks_id

class Task:
    def create_task(self, Title, Status, Begin, End):
        cursor = mysql.cursor()
        if Title:
            cursor.execute("INSERT INTO task SET title = '" + Title + "';")
        else:
            return False
        if Begin:
            cursor.execute("UPDATE task SET begin = '" + Begin + "' WHERE title=Title ;")
        if End:
            cursor.execute("UPDATE task SET end = '" + End + "' WHERE title=Title ;")
        if Status:
            cursor.execute("UPDATE task SET status = '" + Status + "' WHERE title=Title ;")
        mysql.commit()
        cursor.close()
        return True

    def check_task(self, title):
        cursor = mysql.cursor()
        cursor.execute("SELECT task_id FROM task;")
        tasks = cursor.fetchall()
        cursor.close()
        for use in tasks:
            if use[0] == title:
                return True
        return False

    def edit_task(self, id, Title, Status, Begin, End):
        cursor = mysql.cursor()
        if Title:
            cursor.execute("UPDATE task SET title='" + Title + "' WHERE task_id = " + id + ";")
        if Status:
            cursor.execute("UPDATE task SET status='" + Status + "' WHERE task_id = " + id + ";")
        if Begin:
            cursor.execute("UPDATE task SET begin='" + Begin + "' WHERE task_id = " + id + ";")
        if End:
            cursor.execute("UPDATE task SET end='" + End + "' WHERE task_id = " + id + ";")
        mysql.commit()
        cursor.close()

    def delete_task(self, id):
        cursor = mysql.cursor()
        cursor.execute("DELETE FROM task WHERE task_id = " + str(id) + ";")
        mysql.commit()
        cursor.close()
        
    def get_task_with_id(self, id):
        cursor = mysql.cursor()
        cursor.execute("SELECT * FROM task WHERE task_id = " + str(id) + ";")
        tasks = cursor.fetchall()[0]
        cursor.close()
        return tasks

    def add_user_to_task(self, task_id, user_id):
        cursor = mysql.cursor()
        cursor.execute("insert into user_has_task values (" + user_id + ", " + task_id + ");")
        mysql.commit()
        cursor.close()

    def remove_user_from_task(self, task_id, user_id):
        cursor = mysql.cursor()
        cursor.execute("delete from user_has_task where fk_task_id = " + task_id + " and fk_user_id = " + user_id + ";")
        mysql.commit()
        cursor.close()