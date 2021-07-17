from app import user, app

class User:
    def check_username(self, username):
        #cursor = mysql.cursor()
        cursor.execute("SELECT username FROM user;")
        users = cursor.fetchall()
        cursor.close()
        for use in users:
            if use[0] == username:
                return True
        return False

    def check_password(self, username, password):
        #cursor = mysql.cursor()
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
        #cursor = mysql.cursor()
        cursor.execute("INSERT INTO user SET username = '" + username + "', password = '" + password + "';")
        #mysql.commit()
        cursor.close()

    def get_id(self, username):
        #cursor = mysql.cursor()
        cursor.execute("select user_id FROM user WHERE username = '" + username + "';")
        use = cursor.fetchall()[0][0]
        cursor.close()
        if use:
            return use
        else:
            return -1

    def check_user_id(self, id):
        #cursor = mysql.cursor()
        cursor.execute("SELECT user_id FROM user;")
        users = cursor.fetchall()
        cursor.close()
        for use in users:
            if use[0] == id:
                return True
        return False

    def get_user_with_id(self, id):
        #cursor = mysql.cursor()
        cursor.execute("select username FROM user WHERE user_id = " + str(id) + ";")
        use = cursor.fetchall()[0][0]
        cursor.close()
        if use:
            return use
        else:
            return -1

    def has_task(self, user_id, task_id):
        #cursor = mysql.cursor()
        cursor.execute("select * from user_has_task where fk_task_id = " + str(task_id) + " and fk_user_id = " +str(user_id) + ";")
        if cursor.fetchall():
            return True
        else:
            return False

    def get_task(self, user_id):
        #cursor = mysql.cursor()
        cursor.execute("select fk_task_id from user_has_task where fk_user_id = " + str(user_id) + ";")
        tasks_id = cursor.fetchall()
        cursor.close()
        return tasks_id

class Task:
    def get_all_tasks(self):
        #cursor = mysql.cursor()
        cursor.execute("SELECT * FROM task;")
        tasks = cursor.fetchall()
        cursor.close()
        return tasks

    def create_task(self, Title, Status, Begin, End):
        #cursor = mysql.cursor()
        if not Title:
            return False
        if Status:
            Status = "'" + Status + "'"
        else:
            Status = "default"
        if Begin:
            Begin = "'" + Begin + "'"
        else:
            Begin = "default"
        if End:
            End = "'" + End + "'"
        else:
            End = "default"
        Title = "'" + Title + "'"
        cursor.execute("INSERT INTO task VALUES (default, " + Title + ", " + Begin + ", " + End + ", " + Status + ");")
        #mysql.commit()
        cursor.close()
        return True

    def check_task(self, title):
        #cursor = mysql.cursor()
        cursor.execute("SELECT task_id FROM task;")
        tasks = cursor.fetchall()
        cursor.close()
        for use in tasks:
            if use[0] == title:
                return True
        return False

    def edit_task(self, id, Title, Status, Begin, End):
        #cursor = mysql.cursor()
        if Title:
            cursor.execute("UPDATE task SET title='" + Title + "' WHERE task_id = " + str(id) + ";")
        if Status:
            cursor.execute("UPDATE task SET status='" + Status + "' WHERE task_id = " + str(id) + ";")
        if Begin:
            cursor.execute("UPDATE task SET begin='" + Begin + "' WHERE task_id = " + str(id) + ";")
        if End:
            cursor.execute("UPDATE task SET end='" + End + "' WHERE task_id = " + str(id) + ";")
        #mysql.commit()
        cursor.close()

    def delete_task(self, id):
        #cursor = mysql.cursor()
        cursor.execute("DELETE FROM task WHERE task_id = " + str(id) + ";")
        #mysql.commit()
        cursor.close()
        
    def get_task_with_id(self, id):
        #cursor = mysql.cursor()
        cursor.execute("SELECT * FROM task WHERE task_id = " + str(id) + ";")
        tasks = cursor.fetchall()[0]
        cursor.close()
        return tasks

    def get_user(self, task_id):
        #cursor = mysql.cursor()
        cursor.execute("select fk_user_id from user_has_task where fk_task_id = " + str(task_id) + ";")
        users_id = cursor.fetchall()
        cursor.close()
        return users_id

    def add_user_to_task(self, task_id, user_id):
        #cursor = mysql.cursor()
        cursor.execute("insert into user_has_task values (" + str(user_id) + ", " + str(task_id) + ");")
        #mysql.commit()
        cursor.close()

    def remove_user_from_task(self, task_id, user_id):
        #cursor = mysql.cursor()
        cursor.execute("delete from user_has_task where fk_task_id = " + str(task_id) + " and fk_user_id = " + str(user_id) + ";")
        #mysql.commit()
        cursor.close()
    
    def get_last_task(self):
        #cursor = mysql.cursor()
        cursor.execute("select * from task;")
        tasks = cursor.fetchall()
        if tasks:
            task = tasks[0]
        else:
            return False
        for each_task in tasks:
            task = each_task
        cursor.close()
        return task