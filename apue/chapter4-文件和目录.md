DIR结构体类似于FILE，是一个内部结构,以下为DIR结构体的定义：

```
struct __dirstream   
{   
    void *__fd;    
    char *__data;    
    int __entry_data;    
    char *__ptr;    
    int __entry_ptr;    
    size_t __allocation;    
    size_t __size;    
    __libc_lock_define (, __lock)    
};   
  
typedef struct __dirstream DIR;  
```

打开一个目录

```
struct dirent *readdir(DIR *dp)
```

readdir会返回一个dirent结构体，该结构体不仅指向目录，还指向目录中的具体文件，定义如下：

```
struct dirent   
{   
    long d_ino; /* inode number 索引节点号 */  
    off_t d_off; /* offset to this dirent 在目录文件中的偏移 */  
    unsigned short d_reclen; /* length of this d_name 文件名长 */  
    unsigned char d_type; /* the type of d_name 文件类型 */  
    char d_name [NAME_MAX+1]; /* file name (null-terminated) 文件名，最长255字符 */  
} 
```

读取文件详细信息

```
int stat(const char *file_name, struct stat *buf)
```

其中参数file_name的值可以是结构体dirent中的d_name成员，文件的详细信息保存在结构体stat中，其定义如下：

```
struct stat {   
	mode_t     st_mode;       //文件类型及访问权限   
	ino_t      st_ino;        //索引节点号   
	dev_t      st_dev;        //文件使用的设备号   
	dev_t      st_rdev;       //设备文件的设备号   
	nlink_t    st_nlink;      //文件的硬连接数   
	uid_t      st_uid;        //所有者用户识别号   
	gid_t      st_gid;        //组识别号   
	off_t      st_size;       //以字节为单位的文件容量   
	time_t     st_atime;      //最后一次访问该文件的时间   
	time_t     st_mtime;      //最后一次修改该文件的时间   
	time_t     st_ctime;      //最后一次改变该文件状态的时间   
	blksize_t st_blksize;     //包含该文件的磁盘块的大小   
	blkcnt_t   st_blocks;     //该文件所占的磁盘块   
}  
```

总结一下，想要获取某目录下（比如a目下）b文件的详细信息，我们应该怎样做？

1. 我们使用opendir函数打开目录a，返回指向目录a的DIR结构体c。
2. 我们调用readdir(c)函数读取目录a下所有文件（包括目录），返回指向目录a下所有文件的dirent结构体d。
3. 我们遍历d，调用stat(d.name,stat e)来获取每个文件的详细信息，存储在stat结构体e中。

# Section 1 stat、fstat和lstat函数

stat通过给出的文件名获取文件相关信息，fstat通过给出的**文件描述符**获取文件相关信息，lstat类似于stat，但当命名的文件是一个符号链接时，lstat返回该符号链接的有关信息，而不是由该符号链接引用文件的信息。

# Section 2 文件类型

- 普通文件
- 目录文件
- 块特殊文件
- 字符特殊文件
- FIFO
- 套接字
- 符号链接

# Section 3 新文件和目录的所有权

新文件的**用户ID**为创建它的进程的**有效用户ID**。关于**组ID**，POSIX允许实现选择下列之一作为新文件的组ID：

- 新文件的组ID可以是进程的有效组ID
- 新文件的组ID可以是它所在目录的组ID

# Section 4 文件系统

我们可以把一个磁盘分成一个或多个分区。每个分区可以包含一个文件系统。

i节点包含了大多数与文件有关的信息：文件类型、文件访问权限位、文件长度和指向该文件所占用的数据块的指针等。stat结构中的大多数信息取自i节点。只有两项数据放在目录项中：文件名和i节点编号。

# Section 5 符号链接

符号链接时指向一个文件的间接指针，它与硬链接有所不同。硬链接直接指向文件的i节点。引入符号链接的原因是为了避开硬链接的一些限制：

- 硬链接通常要求链接和文件位于同一文件系统中。
- 只有超级用户才能创建指向目录的硬链接。

# Section 6 symlink和readlink函数

前者用于创建一个符号链接，后者用于打开符号链接本身。

# Section 7 utime函数

一个文件的访问和修改时间可以用utime函数更改。

# Section 8 mkdir和rmdir函数

前者用于创建目录，后者用于删除目录。

# Section 9 chdir、fchdir和getcwd函数

chdir 通过路径名改变进程的当前工作目录。
fchdir 通过文件描述符改变进程的当前工作目录。
getcwd 获取当前目录的绝对路径。

# Section 10 设备特殊文件

st_dev 字段表示文件系统的设备号。
st_rdev 字段表示字符特殊文件和块特殊文件本身实际的设备号。
