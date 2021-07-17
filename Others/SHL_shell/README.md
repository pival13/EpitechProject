# SHL_shell

Create in collaboration with [bardomania](https://github.com/bardomania).

Bonus are available from the main function (bdsh):
* **where**: ./bdsh -f file.json select user firstname,id where lastname=SMITH
* **update**: ./bdsh -f file.json update user firstname=Marry where firstname=John
* **delete**: ./bdsh -f file.json delete user where lastname=SMITH

Unit test are available from the test folder:
```
cd test
./test.bash
```