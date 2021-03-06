/*
** EPITECH PROJECT, 2020
** PSU_strace_2019 [WSL: Ubuntu]
** File description:
** strace
*/

#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <error.h>

void display_nb(size_t a, char *format, bool display);
void display_string(size_t pid, size_t a, bool display);
void display_pointer(size_t a, bool display);

void my_printf(char *s, ...);

enum syscall_type_s {
    INT,
    UNSIGNED,
    LONG,
    SIZE_T,
    STRING,
    POINTER
};

const void *syscall_x[] = {
    "read",
    (int *)LONG, (int []){INT, STRING, SIZE_T, -1},
    "write",
    (int *)LONG, (int []){INT, STRING, SIZE_T, -1},
    "open",
    (int *)INT, (int []){STRING, INT, -1},
    "close",
    (int *)INT, (int []){INT, -1},
    "stat",
    (int *)INT, (int []){STRING, POINTER, -1},
    "fstat",
    (int *)INT, (int []){INT, POINTER, -1},
    "lstat",
    (int *)INT, (int []){STRING, POINTER, -1},
    "poll",
    (int *)INT, (int []){POINTER, SIZE_T, INT, -1},
    "lseek",
    (int *)LONG, (int []){INT, LONG, INT, -1},
    "mmap",
    (int *)POINTER, (int []){POINTER, SIZE_T, INT, INT, INT, LONG, -1},
    "mprotect",
    (int *)INT, (int []){POINTER, SIZE_T, INT, -1},
    "munmap",
    (int *)INT, (int []){POINTER, SIZE_T, -1},
    "brk",
    (int *)POINTER, (int []){POINTER, -1},
    "rt_sigaction",
    (int *)INT, (int []){INT, POINTER, POINTER, -1},
    "rt_sigprocmask",
    (int *)INT, (int []){INT, POINTER, POINTER, SIZE_T, -1},
    "rt_sigreturn",
    (int *)INT, (int []){SIZE_T, -1},
    "ioctl",
    (int *)INT, (int []){INT, SIZE_T, POINTER, -1},
    "pread64",
    (int *)SIZE_T, (int []){INT, POINTER, SIZE_T, LONG, -1},
    "pwrite64",
    (int *)SIZE_T, (int []){INT, POINTER, SIZE_T, LONG, -1},
    "readv",
    (int *)LONG, (int []){INT, POINTER, INT, -1},
    "writev",
    (int *)LONG, (int []){INT, POINTER, INT, -1},
    "access",
    (int *)INT, (int []){STRING, INT, -1},
    "pipe",
    (int *)INT, (int []){POINTER, -1},
    "select",
    (int *)INT, (int []){INT, POINTER, POINTER, POINTER, POINTER, -1},
    "sched_yield",
    (int *)INT, (int []){-1},
    "mremap",
    (int *)POINTER, (int []){POINTER, SIZE_T, SIZE_T, INT, POINTER, -1},
    "msync",
    (int *)INT, (int []){POINTER, SIZE_T, INT, -1},
    "mincore",
    (int *)INT, (int []){POINTER, SIZE_T, STRING, -1},
    "madvise",
    (int *)INT, (int []){POINTER, SIZE_T, INT, -1},
    "shmget",
    (int *)INT, (int []){INT, SIZE_T, INT, -1},
    "shmat",
    (int *)POINTER, (int []){INT, POINTER, INT, -1},
    "shmctl",
    (int *)INT, (int []){INT, INT, POINTER, -1},
    "dup",
    (int *)INT, (int []){INT, -1},
    "dup2",
    (int *)INT, (int []){INT, INT, -1},
    "pause",
    (int *)INT, (int []){-1},
    "nanosleep",
    (int *)INT, (int []){POINTER, POINTER, -1},
    "getitimer",
    (int *)INT, (int []){INT, POINTER, -1},
    "alarm",
    (int *)INT, (int []){UNSIGNED, -1},
    "setitimer",
    (int *)INT, (int []){INT, POINTER, POINTER, -1},
    "getpid",
    (int *)INT, (int []){-1},
    "sendfile",
    (int *)LONG, (int []){INT, INT, POINTER, SIZE_T, -1},
    "socket",
    (int *)INT, (int []){INT, INT, INT, -1},
    "connect",
    (int *)INT, (int []){INT, POINTER, UNSIGNED, -1},
    "accept",
    (int *)INT, (int []){INT, POINTER, POINTER, -1},
    "sendto",
    (int *)LONG, (int []){INT, POINTER, SIZE_T, INT, POINTER, UNSIGNED, -1},
    "recvfrom",
    (int *)LONG, (int []){INT, POINTER, SIZE_T, INT, POINTER, POINTER, -1},
    "sendmsg",
    (int *)LONG, (int []){INT, POINTER, INT, -1},
    "recvmsg",
    (int *)LONG, (int []){INT, POINTER, INT, -1},
    "shutdown",
    (int *)INT, (int []){INT, INT, -1},
    "bind",
    (int *)INT, (int []){INT, POINTER, UNSIGNED, -1},
    "listen",
    (int *)INT, (int []){INT, INT, -1},
    "getsockname",
    (int *)INT, (int []){INT, POINTER, POINTER, -1},
    "getpeername",
    (int *)INT, (int []){INT, POINTER, POINTER, -1},
    "socketpair",
    (int *)INT, (int []){INT, INT, INT, POINTER, -1},
    "setsockopt",
    (int *)INT, (int []){INT, INT, INT, POINTER, UNSIGNED, -1},
    "getsockopt",
    (int *)INT, (int []){INT, INT, INT, POINTER, POINTER, -1},
    "clone",
    (int *)INT, (int []){POINTER, POINTER, INT, POINTER, -1},
    "fork",
    (int *)INT, (int []){-1},
    "vfork",
    (int *)INT, (int []){-1},
    "execve",
    (int *)INT, (int []){STRING, POINTER, POINTER, -1},
    "exit",
    (int *)-1, (int []){-1},
    "wait4",
    (int *)INT, (int []){INT, POINTER, INT, POINTER, -1},
    "kill",
    (int *)INT, (int []){INT, INT, -1},
    "uname",
    (int *)INT, (int []){POINTER, -1},
    "semget",
    (int *)INT, (int []){INT, INT, INT, -1},
    "semop",
    (int *)INT, (int []){INT, POINTER, SIZE_T, -1},
    "semctl",
    (int *)INT, (int []){INT, INT, INT, POINTER, -1},
    "shmdt",
    (int *)INT, (int []){POINTER, -1},
    "msgget",
    (int *)INT, (int []){INT, INT, -1},
    "msgsnd",
    (int *)INT, (int []){INT, POINTER, SIZE_T, INT, -1},
    "msgrcv",
    (int *)LONG, (int []){INT, POINTER, SIZE_T, LONG, INT, -1},
    "msgctl",
    (int *)INT, (int []){INT, INT, POINTER, -1},
    "fcntl",
    (int *)INT, (int []){INT, INT, POINTER, -1},
    "flock",
    (int *)INT, (int []){INT, INT, -1},
    "fsync",
    (int *)INT, (int []){INT, -1},
    "fdatasync",
    (int *)INT, (int []){INT, -1},
    "truncate",
    (int *)INT, (int []){STRING, LONG, -1},
    "ftruncate",
    (int *)INT, (int []){INT, LONG, -1},
    "getdents",
    (int *)INT, (int []){UNSIGNED, POINTER, UNSIGNED, -1},
    "getcwd",
    (int *)STRING, (int []){STRING, SIZE_T, -1},
    "chdir",
    (int *)INT, (int []){STRING, -1},
    "fchdir",
    (int *)INT, (int []){INT, -1},
    "rename",
    (int *)INT, (int []){STRING, STRING, -1},
    "mkdir",
    (int *)INT, (int []){STRING, UNSIGNED, -1},
    "rmdir",
    (int *)INT, (int []){STRING, -1},
    "creat",
    (int *)INT, (int []){STRING, UNSIGNED, -1},
    "link",
    (int *)INT, (int []){STRING, STRING, -1},
    "unlink",
    (int *)INT, (int []){STRING, -1},
    "symlink",
    (int *)INT, (int []){STRING, STRING, -1},
    "readlink",
    (int *)LONG, (int []){STRING, STRING, SIZE_T, -1},
    "chmod",
    (int *)INT, (int []){STRING, UNSIGNED, -1},
    "fchmod",
    (int *)INT, (int []){INT, UNSIGNED, -1},
    "chown",
    (int *)INT, (int []){STRING, UNSIGNED, UNSIGNED, -1},
    "fchown",
    (int *)INT, (int []){INT, UNSIGNED, UNSIGNED, -1},
    "lchown",
    (int *)INT, (int []){STRING, UNSIGNED, UNSIGNED, -1},
    "umask",
    (int *)UNSIGNED, (int []){UNSIGNED, -1},
    "gettimeofday",
    (int *)INT, (int []){POINTER, POINTER, -1},
    "getrlimit",
    (int *)INT, (int []){INT, POINTER, -1},
    "getrusage",
    (int *)INT, (int []){INT, POINTER, -1},
    "sysinfo",
    (int *)INT, (int []){POINTER, -1},
    "times",
    (int *)LONG, (int []){POINTER, -1},
    "ptrace",
    (int *)LONG, (int []){INT, INT, POINTER, POINTER, -1},
    "getuid",
    (int *)UNSIGNED, (int []){-1},
    "syslog",
    (int *)INT, (int []){INT, STRING, INT, -1},
    "getgid",
    (int *)UNSIGNED, (int []){-1},
    "setuid",
    (int *)INT, (int []){UNSIGNED, -1},
    "setgid",
    (int *)INT, (int []){UNSIGNED, -1},
    "geteuid",
    (int *)UNSIGNED, (int []){-1},
    "getegid",
    (int *)UNSIGNED, (int []){-1},
    "setpgid",
    (int *)INT, (int []){INT, INT, -1},
    "getppid",
    (int *)INT, (int []){-1},
    "getpgrp",
    (int *)INT, (int []){-1},
    "setsid",
    (int *)INT, (int []){-1},
    "setreuid",
    (int *)INT, (int []){UNSIGNED, UNSIGNED, -1},
    "setregid",
    (int *)INT, (int []){UNSIGNED, UNSIGNED, -1},
    "getgroups",
    (int *)INT, (int []){INT, POINTER, -1},
    "setgroups",
    (int *)INT, (int []){SIZE_T, POINTER, -1},
    "setresuid",
    (int *)INT, (int []){UNSIGNED, UNSIGNED, UNSIGNED, -1},
    "getresuid",
    (int *)INT, (int []){POINTER, POINTER, POINTER, -1},
    "setresgid",
    (int *)INT, (int []){UNSIGNED, UNSIGNED, UNSIGNED, -1},
    "getresgid",
    (int *)INT, (int []){POINTER, POINTER, POINTER, -1},
    "getpgid",
    (int *)INT, (int []){INT, -1},
    "setfsuid",
    (int *)INT, (int []){UNSIGNED, -1},
    "setfsgid",
    (int *)INT, (int []){UNSIGNED, -1},
    "getsid",
    (int *)INT, (int []){INT, -1},
    "capget",
    (int *)INT, (int []){POINTER, POINTER, -1},
    "capset",
    (int *)INT, (int []){POINTER, POINTER, -1},
    "rt_sigpending",
    (int *)-1, (int []){-1},
    "rt_sigtimedwait",
    (int *)-1, (int []){-1},
    "rt_sigqueueinfo",
    (int *)INT, (int []){INT, INT, POINTER, -1},
    "rt_sigsuspend",
    (int *)-1, (int []){-1},
    "sigaltstack",
    (int *)INT, (int []){POINTER, POINTER, -1},
    "utime",
    (int *)INT, (int []){STRING, POINTER, -1},
    "mknod",
    (int *)INT, (int []){STRING, UNSIGNED, SIZE_T, -1},
    "uselib",
    (int *)INT, (int []){STRING, -1},
    "personality",
    (int *)INT, (int []){SIZE_T, -1},
    "ustat",
    (int *)INT, (int []){SIZE_T, POINTER, -1},
    "statfs",
    (int *)INT, (int []){STRING, POINTER, -1},
    "fstatfs",
    (int *)INT, (int []){INT, POINTER, -1},
    "sysfs",
    (int *)INT, (int []){INT, STRING, -1},
    "getpriority",
    (int *)INT, (int []){INT, UNSIGNED, -1},
    "setpriority",
    (int *)INT, (int []){INT, UNSIGNED, INT, -1},
    "sched_setparam",
    (int *)INT, (int []){INT, POINTER, -1},
    "sched_getparam",
    (int *)INT, (int []){INT, POINTER, -1},
    "sched_setscheduler",
    (int *)INT, (int []){INT, INT, POINTER, -1},
    "sched_getscheduler",
    (int *)INT, (int []){INT, -1},
    "sched_get_priority_max",
    (int *)INT, (int []){INT, -1},
    "sched_get_priority_min",
    (int *)INT, (int []){INT, -1},
    "sched_rr_get_interval",
    (int *)INT, (int []){INT, POINTER, -1},
    "mlock",
    (int *)INT, (int []){POINTER, SIZE_T, -1},
    "munlock",
    (int *)INT, (int []){POINTER, SIZE_T, -1},
    "mlockall",
    (int *)INT, (int []){INT, -1},
    "munlockall",
    (int *)INT, (int []){-1},
    "vhangup",
    (int *)INT, (int []){-1},
    "modify_ldt",
    (int *)INT, (int []){INT, POINTER, SIZE_T, -1},
    "pivot_root",
    (int *)INT, (int []){STRING, STRING, -1},
    "_sysctl",
    (int *)INT, (int []){POINTER, -1},
    "prctl",
    (int *)INT, (int []){INT, SIZE_T, SIZE_T, SIZE_T, SIZE_T, -1},
    "arch_prctl",
    (int *)INT, (int []){INT, SIZE_T, -1},
    "adjtimex",
    (int *)INT, (int []){POINTER, -1},
    "setrlimit",
    (int *)INT, (int []){INT, POINTER, -1},
    "chroot",
    (int *)INT, (int []){STRING, -1},
    "sync",
    (int *)-1,    (int []){-1},
    "acct",
    (int *)INT, (int []){STRING, -1},
    "settimeofday",
    (int *)INT, (int []){POINTER, POINTER, -1},
    "mount",
    (int *)INT, (int []){STRING, STRING, STRING, SIZE_T, POINTER, -1},
    "umount2",
    (int *)INT, (int []){STRING, INT, -1},
    "swapon",
    (int *)INT, (int []){STRING, INT, -1},
    "swapoff",
    (int *)INT, (int []){STRING, -1},
    "reboot",
    (int *)INT, (int []){INT, INT, INT, POINTER, -1},
    "sethostname",
    (int *)INT, (int []){STRING, SIZE_T, -1},
    "setdomainname",
    (int *)INT, (int []){STRING, SIZE_T, -1},
    "iopl",
    (int *)INT, (int []){INT, -1},
    "ioperm",
    (int *)INT, (int []){SIZE_T, SIZE_T, INT, -1},
    "create_module",
    (int *)STRING, (int []){STRING, SIZE_T, -1},
    "init_module",
    (int *)INT, (int []){POINTER, SIZE_T, STRING, -1},
    "delete_module",
    (int *)INT, (int []){STRING, INT, -1},
    "get_kernel_syms",
    (int *)INT, (int []){POINTER, -1},
    "query_module",
    (int *)INT, (int []){STRING, INT, POINTER, SIZE_T, POINTER, -1},
    "quotactl",
    (int *)INT, (int []){INT, STRING, INT, STRING, -1},
    "nfsservctl",
    (int *)LONG, (int []){INT, POINTER, POINTER, -1},
    "getpmsg",
    (int *)-1, (int []){-1},
    "putpmsg",
    (int *)-1, (int []){-1},
    "afs_syscall",
    (int *)-1, (int []){-1},
    "tuxcall",
    (int *)-1, (int []){-1},
    "security",
    (int *)-1, (int []){-1},
    "gettid",
    (int *)INT, (int []){-1},
    "readahead",
    (int *)LONG, (int []){INT, INT, SIZE_T, -1},
    "setxattr",
    (int *)-1, (int []){-1},
    "lsetxattr",
    (int *)-1, (int []){-1},
    "fsetxattr",
    (int *)-1, (int []){-1},
    "getxattr",
    (int *)-1, (int []){-1},
    "lgetxattr",
    (int *)-1, (int []){-1},
    "fgetxattr",
    (int *)-1, (int []){-1},
    "listxattr",
    (int *)-1, (int []){-1},
    "llistxattr",
    (int *)-1, (int []){-1},
    "flistxattr",
    (int *)-1, (int []){-1},
    "removexattr",
    (int *)-1, (int []){-1},
    "lremovexattr",
    (int *)-1, (int []){-1},
    "fremovexattr",
    (int *)-1, (int []){-1},
    "tkill",
    (int *)INT, (int []){INT, INT, -1},
    "time",
    (int *)LONG, (int []){POINTER, -1},
    "futex",
    (int *)INT, (int []){POINTER, INT, INT, POINTER, POINTER, INT, -1},
    "sched_setaffinity",
    (int *)INT, (int []){INT, SIZE_T, POINTER, -1},
    "sched_getaffinity",
    (int *)INT, (int []){INT, SIZE_T, POINTER, -1},
    "set_thread_area",
    (int *)INT, (int []){POINTER, -1},
    "io_setup",
    (int *)INT, (int []){UNSIGNED, POINTER, -1},
    "io_destroy",
    (int *)INT, (int []){POINTER, -1},
    "io_getevents",
    (int *)INT, (int []){POINTER, LONG, LONG, POINTER, POINTER, -1},
    "io_submit",
    (int *)INT, (int []){POINTER, LONG, POINTER, -1},
    "io_cancel",
    (int *)INT, (int []){POINTER, POINTER, POINTER, -1},
    "get_thread_area",
    (int *)INT, (int []){POINTER, -1},
    "lookup_dcookie",
    (int *)INT, (int []){SIZE_T, STRING, SIZE_T, -1},
    "epoll_create",
    (int *)INT, (int []){INT, -1},
    "epoll_ctl_old",
    (int *)-1, (int []){-1},
    "epoll_wait_old",
    (int *)-1, (int []){-1},
    "remap_file_pages",
    (int *)INT, (int []){POINTER, SIZE_T, INT, SIZE_T, INT, -1},
    "getdents64",
    (int *)INT, (int []){UNSIGNED, POINTER, UNSIGNED, -1},
    "set_tid_address",
    (int *)LONG, (int []){POINTER, -1},
    "restart_syscall",
    (int *)INT, (int []){-1},
    "semtimedop",
    (int *)INT, (int []){INT, POINTER, SIZE_T, POINTER, -1},
    "fadvise64",
    (int *)-1, (int []){-1},
    "timer_create",
    (int *)INT, (int []){INT, POINTER, POINTER, -1},
    "timer_settime",
    (int *)INT, (int []){POINTER, INT, POINTER, POINTER, -1},
    "timer_gettime",
    (int *)INT, (int []){POINTER, POINTER, -1},
    "timer_getoverrun",
    (int *)INT, (int []){POINTER, -1},
    "timer_delete",
    (int *)INT, (int []){POINTER, -1},
    "clock_settime",
    (int *)INT, (int []){INT, POINTER, -1},
    "clock_gettime",
    (int *)INT, (int []){INT, POINTER, -1},
    "clock_getres",
    (int *)INT, (int []){INT, POINTER, -1},
    "clock_nanosleep",
    (int *)INT, (int []){INT, INT, POINTER, POINTER, -1},
    "exit_group",
    (int *)-1,    (int []){INT, -1},
    "epoll_wait",
    (int *)INT, (int []){INT, POINTER, INT, INT, -1},
    "epoll_ctl",
    (int *)INT, (int []){INT, INT, INT, POINTER, -1},
    "tgkill",
    (int *)INT, (int []){INT, INT, INT, -1},
    "utimes",
    (int *)INT, (int []){STRING, POINTER, -1},
    "vserver",
    (int *)-1, (int []){-1},
    "mbind",
    (int *)LONG, (int []){POINTER, SIZE_T, INT, POINTER, SIZE_T, UNSIGNED, -1},
    "set_mempolicy",
    (int *)LONG, (int []){INT, POINTER, SIZE_T, -1},
    "get_mempolicy",
    (int *)LONG, (int []){POINTER, POINTER, SIZE_T, POINTER, SIZE_T, -1},
    "mq_open",
    (int *)INT, (int []){STRING, INT, -1},
    "mq_unlink",
    (int *)INT, (int []){STRING, -1},
    "mq_timedsend",
    (int *)INT, (int []){INT, STRING, SIZE_T, UNSIGNED, POINTER, -1},
    "mq_timedreceive",
    (int *)LONG, (int []){INT, STRING, SIZE_T, POINTER, POINTER, -1},
    "mq_notify",
    (int *)INT, (int []){INT, POINTER, -1},
    "mq_getsetattr",
    (int *)INT, (int []){INT, POINTER, POINTER, -1},
    "kexec_load",
    (int *)LONG, (int []){SIZE_T, SIZE_T, POINTER, SIZE_T, -1},
    "waitid",
    (int *)INT, (int []){INT, UNSIGNED, POINTER, INT, -1},
    "add_key",
    (int *)POINTER, (int []){STRING, STRING, POINTER, SIZE_T, POINTER, -1},
    "request_key",
    (int *)POINTER, (int []){STRING, STRING, STRING, POINTER, -1},
    "keyctl",
    (int *)-1, (int []){-1},
    "ioprio_set",
    (int *)INT, (int []){INT, INT, INT, -1},
    "ioprio_get",
    (int *)INT, (int []){INT, INT, -1},
    "inotify_init",
    (int *)INT, (int []){-1},
    "inotify_add_watch",
    (int *)INT, (int []){INT, STRING, UNSIGNED, -1},
    "inotify_rm_watch",
    (int *)INT, (int []){INT, INT, -1},
    "migrate_pages",
    (int *)LONG, (int []){INT, SIZE_T, POINTER, POINTER, -1},
    "openat",
    (int *)INT, (int []){INT, STRING, INT, -1},
    "mkdirat",
    (int *)INT, (int []){INT, STRING, UNSIGNED, -1},
    "mknodat",
    (int *)INT, (int []){INT, STRING, UNSIGNED, SIZE_T, -1},
    "fchownat",
    (int *)INT, (int []){INT, STRING, UNSIGNED, UNSIGNED, INT, -1},
    "futimesat",
    (int *)INT, (int []){INT, STRING, POINTER, -1},
    "newfstatat",
    (int *)-1, (int []){-1},
    "unlinkat",
    (int *)INT, (int []){INT, STRING, INT, -1},
    "renameat",
    (int *)INT, (int []){INT, STRING, INT, STRING, -1},
    "linkat",
    (int *)INT, (int []){INT, STRING, INT, STRING, INT, -1},
    "symlinkat",
    (int *)INT, (int []){STRING, INT, STRING, -1},
    "readlinkat",
    (int *)LONG, (int []){INT, STRING, STRING, SIZE_T, -1},
    "fchmodat",
    (int *)INT, (int []){INT, STRING, UNSIGNED, INT, -1},
    "faccessat",
    (int *)INT, (int []){INT, STRING, INT, INT, -1},
    "pselect6",
    (int *)-1, (int []){-1},
    "ppoll",
    (int *)INT, (int []){POINTER, SIZE_T, POINTER, POINTER, -1},
    "unshare",
    (int *)INT, (int []){INT, -1},
    "set_robust_list",
    (int *)LONG, (int []){POINTER, SIZE_T, -1},
    "get_robust_list",
    (int *)LONG, (int []){INT, POINTER, POINTER, -1},
    "splice",
    (int *)LONG, (int []){INT, POINTER, INT, POINTER, SIZE_T, UNSIGNED, -1},
    "tee",
    (int *)LONG, (int []){INT, INT, SIZE_T, UNSIGNED, -1},
    "sync_file_range",
    (int *)INT, (int []){INT, LONG, LONG, UNSIGNED, -1},
    "vmsplice",
    (int *)LONG, (int []){INT, POINTER, SIZE_T, UNSIGNED, -1},
    "move_pages",
    (int *)LONG, (int []){INT, SIZE_T, POINTER, POINTER, POINTER, INT, -1},
    "utimensat",
    (int *)INT, (int []){INT, STRING, POINTER, INT, -1},
    "epoll_pwait",
    (int *)INT, (int []){INT, POINTER, INT, INT, POINTER, -1},
    "signalfd",
    (int *)INT, (int []){INT, POINTER, INT, -1},
    "timerfd_create",
    (int *)INT, (int []){INT, INT, -1},
    "eventfd",
    (int *)INT, (int []){UNSIGNED, INT, -1},
    "fallocate",
    (int *)INT, (int []){INT, INT, LONG, LONG, -1},
    "timerfd_settime",
    (int *)INT, (int []){INT, INT, POINTER, POINTER, -1},
    "timerfd_gettime",
    (int *)INT, (int []){INT, POINTER, -1},
    "accept4",
    (int *)INT, (int []){INT, POINTER, POINTER, INT, -1},
    "signalfd4",
    (int *)-1, (int []){-1},
    "eventfd2",
    (int *)-1, (int []){-1},
    "epoll_create1",
    (int *)INT, (int []){INT, -1},
    "dup3",
    (int *)INT, (int []){INT, INT, INT, -1},
    "pipe2",
    (int *)INT, (int []){POINTER, INT, -1},
    "inotify_init1",
    (int *)INT, (int []){INT, -1},
    "preadv",
    (int *)LONG, (int []){INT, POINTER, INT, LONG, -1},
    "pwritev",
    (int *)LONG, (int []){INT, POINTER, INT, LONG, -1},
    "rt_tgsigqueueinfo",
    (int *)INT, (int []){INT, INT, INT, POINTER, -1},
    "perf_event_open",
    (int *)INT, (int []){POINTER, INT, INT, INT, SIZE_T, -1},
    "recvmmsg",
    (int *)INT, (int []){INT, POINTER, UNSIGNED, INT, POINTER, -1},
    "fanotify_init",
    (int *)INT, (int []){UNSIGNED, UNSIGNED, -1},
    "fanotify_mark",
    (int *)INT, (int []){INT, UNSIGNED, SIZE_T, INT, STRING, -1},
    "prlimit64",
    (int *)INT, (int []){INT, INT, POINTER, POINTER, -1},
    "name_to_handle_at",
    (int *)INT, (int []){INT, STRING, POINTER, POINTER, INT, -1},
    "open_by_handle_at",
    (int *)INT, (int []){INT, POINTER, INT, -1},
    "clock_adjtime",
    (int *)-1, (int []){-1},
    "syncfs",
    (int *)INT, (int []){INT, -1},
    "sendmmsg",
    (int *)INT, (int []){INT, POINTER, UNSIGNED, INT, -1},
    "setns",
    (int *)INT, (int []){INT, INT, -1},
    "getcpu",
    (int *)INT, (int []){POINTER, POINTER, POINTER, -1},
    "process_vm_readv",
    (int *)LONG, (int []){INT, POINTER, SIZE_T, POINTER, SIZE_T, SIZE_T, -1},
    "process_vm_writev",
    (int *)LONG, (int []){INT, POINTER, SIZE_T, POINTER, SIZE_T, SIZE_T, -1},
    "kcmp",
    (int *)INT, (int []){INT, INT, INT, SIZE_T, SIZE_T, -1},
    "finit_module",
    (int *)INT, (int []){INT, STRING, INT, -1},
    "sched_setattr",
    (int *)INT, (int []){INT, POINTER, UNSIGNED, -1},
    "sched_getattr",
    (int *)INT, (int []){INT, POINTER, UNSIGNED, UNSIGNED, -1},
    "renameat2",
    (int *)INT, (int []){INT, STRING, INT, STRING, UNSIGNED, -1},
    "seccomp",
    (int *)INT, (int []){UNSIGNED, UNSIGNED, POINTER, -1},
    "getrandom",
    (int *)LONG, (int []){POINTER, SIZE_T, UNSIGNED, -1},
    "memfd_create",
    (int *)INT, (int []){STRING, UNSIGNED, -1},
    "kexec_file_load",
    (int *)LONG, (int []){INT, INT, SIZE_T, STRING, SIZE_T, -1},
    "bpf",
    (int *)INT, (int []){INT, POINTER, UNSIGNED, -1},
    "execveat",
    (int *)INT, (int []){INT, STRING, POINTER, POINTER, INT, -1},
    "userfaultfd",
    (int *)INT, (int []){INT, -1},
    "membarrier",
    (int *)INT, (int []){INT, INT, -1},
    "mlock2",
    (int *)INT, (int []){POINTER, SIZE_T, INT, -1},
    "copy_file_range",
    (int *)LONG, (int []){INT, POINTER, INT, POINTER, SIZE_T, UNSIGNED, -1},
    "preadv2",
    (int *)LONG, (int []){INT, POINTER, INT, LONG, INT, -1},
    "pwritev2",
    (int *)LONG, (int []){INT, POINTER, INT, LONG, INT, -1},
    "pkey_mprotect",
    (int *)INT, (int []){POINTER, SIZE_T, INT, INT, -1},
    "pkey_alloc",
    (int *)INT, (int []){SIZE_T, SIZE_T, -1},
    "pkey_free",
    (int *)INT, (int []){INT, -1},
    "statx",
    (int *)INT, (int []){INT, STRING, INT, UNSIGNED, POINTER, -1},
    (int *)-1
};