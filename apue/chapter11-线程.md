# Section 1 线程标识

pthread_equal 函数用于对两个线程ID进行比较。
pthread_selt 函数用于线程获取自身的线程ID。

# Section 2 线程的创建

pthread_create 函数用于新线程的创建。
Linux使用clone系统调用来实现pthread_create, clone系统调用创建子进程，这个子进程可以共享父进程一定数量的执行环境(如文件描
述符和内存), 这个数量是可配置的。因此在Linux系统中，父子线程的进程ID是不相同的。

# Section 3 线程终止

如果进程中的任一线程调用了exit, _Exit或者_exit, 那么整个进程就会终止。

在不终止整个进程的情况下，单线程可以通过下列三种方式退出：

- 线程只是从启动例程(线程主函数)中返回，返回值是线程的退出码。
- 线程可以被同一进程中的其他线程取消。
- 线程调用pthread_exit。

其他线程可以通过调用pthread_join等待指定的线程终止，调用线程将一直阻塞，直到指定线程终止。通过调用pthread_join自动把线程
置于分离状态。这样线程退出时，资源就可以恢复。如果指定线程已处于分离状态，pthread_join调用就会失败，返回EINVAL。
