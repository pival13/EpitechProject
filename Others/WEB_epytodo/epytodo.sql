CREATE DATABASE IF NOT EXISTS epytodo;
USE epytodo;
CREATE TABLE IF NOT EXISTS user (
    user_id INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(15) NOT NULL,
    password VARCHAR(20) NOT NULL
)
engine=innodb;
CREATE TABLE IF NOT EXISTS task (
    task_id INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
    title VARCHAR(255) NOT NULL,
    begin DATETIME NOT NULL DEFAULT NOW(),
    end DATETIME DEFAULT NULL,
    status enum('not started', 'in progress', 'done') NOT NULL DEFAULT 'not started'
)
engine=innodb;
CREATE TABLE IF NOT EXISTS user_has_task (
    fk_user_id int unsigned NOT NULL,
    fk_task_id int unsigned NOT NULL
)
engine=innodb;

alter table user_has_task add constraint fk_user foreign key (fk_user_id) references user(user_id) on delete cascade;
alter table user_has_task add constraint fk_task foreign key (fk_task_id) references task(task_id) on delete cascade;
