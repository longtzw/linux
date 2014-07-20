###不生成core dump文件情况

1. 进程没有写core文件的权限(生成core文件的目标文件夹，在创建时被设置为不可写，或已存在一个同名的不可写的文件，如：目录或符号链接)
2. 存在已个同名的可写文件，单该文件有超过一个的硬链接
3. 文件系统空间不足
4. 生成core文件的目标文件夹不存在
5. core文件大写被限制为0(可通过ulimit -c unlimited 解决)

###命名core dump文件

默认情况下，core dump文件会被命名为core，通过/proc/sys/kernel/core_pattern 可以为core dump文件设置一个命名模板。

符号  |描述
------|-----------------------------------------------------------------------------
%%    |a single % character
%c    |core file size soft resource limit of crashing process (since Linux 2.6.24)
%d    |dump mode—same as value returned by prctl(2) PR_GET_DUMPABLE(since Linux 3.7)
%e    |executable filename (without path prefix)
%E    |pathname of executable, with slashes ('/') replaced by exclamation marks ('!') (since Linux 3.0).
%g    |(numeric) real GID of dumped process
%h    |hostname (same as nodename returned by uname(2))
%p    |PID of dumped process, as seen in the PID namespace in which the process resides
%P    |PID of dumped process, as seen in the initial PID namespace (since Linux 3.12)
%s    |number of signal causing dump
%t    |time of dump, expressed as seconds since the Epoch,1970-01-01 00:00:00 +0000 (UTC)
%u    |(numeric) real UID of dumped process

e.g. echo "/tmp/mmcblk0p1/core-%e-%p-%t" > /proc/sys/kernel/core_pattern

###参考

[core](http://man7.org/linux/man-pages/man5/core.5.html)

[signal](http://man7.org/linux/man-pages/man7/signal.7.html#top_of_page)