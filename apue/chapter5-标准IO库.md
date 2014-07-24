**文件指针**(FILE*)所指向的结构体，包括：用于实际I/O的文件描述符、指向用于该流缓冲区的指针、缓冲区的长度、当前在缓冲区中的字符数以及出错标志等。

标准I/O提供的三种类型缓冲：

- 全缓冲 - 在填满标准I/O缓冲区后才进行实际I/O操作。
- 行缓冲 - 在输入或输出进行实际I/O操作。
- 不带缓冲 

惯例：

标准出错不带缓冲，打开至终端设备的流是行缓冲的，其他所有流则是全缓冲的。

设置缓冲类型
```
void setbuf(FILE *stream, char *buf)
```

强制冲洗一个流
```
int fflush(FILE *stream)
```

打开一个指定的文件
```
FILE *fopen(const char *path, const char *mode)
```

在一个指定的流上打开一个指定的文件
```
FILE *freopen(const char *path, const char *mode, FILE *stream)
```

在一个现有的文件描述符上打开一个流
```
FILE *fdopen(int fd, const char *mode)
```

关闭一个打开的流
```
int fclose(FILE *fp)
```

**输入、输出都是相对于内存而言的，将数据读到内存为输入，将内存中的数据写到文件或终端为输出**

#每次一个字符的I/O

##输入

```
int fgetc(FILE *stream)
int getc(FILE *stream)
int getchar(void)
```

不管出错还是达到文件尾端，这三个函数都返回同样的值，可以调用如下函数用于区分：

```
int feof(FILE *stream)
int ferror(FILE *stream)
```

清除出错标志&文件结束标志

```
void clearerr(FILE *stream)
```

##输出

```
int fputc(int c, FILE *stream)
int putc(int c, FILE *stream)
int putchar(int c)
```

#每次一行的I/O

##输入

```
char *fgets(char *s, int size, FILE *stream)
```

此函数一直读到下一个换行符为止，但不超过n-1个字符，读入的字符被送入缓冲区，缓冲区以null字符结尾。若该行(包括换行符)的字符数超过n-1，则返回一个不完整的行，但缓冲区总是以null字符结尾。对fgets的下次调用会继续读该行

```
char *gets(char *s)
```

不推荐，因为无法指定缓冲区长度，易导致缓冲区溢出。与fgets的不同还在于，其不将换行符存入缓冲区。

##输出

```
int fputs(const char *s, FILE *stream)
```

将一个以null字符终止的字符串写到指定的流，null字符不会被写出。
**注意：并不一定是每次输出一行，因为它并不要求在null字符之前一定是换行符。**

```
int puts(const char *s)
```
避免使用，已免需要记住它在最后添加了一个换行符。

# Section 5 二进制I/O

```
size_t fread(void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);

size_t fwrite(const void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
```

*size*为读写操作单个对象的长度，*nobj*为读写操作的对象个数。

*fread*和*fwrite*返回实际读取或写入的对象数。对于读，如果出错或到达文件尾端，则此数字可以少于*nobj*。在这种情况下，应调用*ferror*或*feof*以判断究竟属于哪一种情况。对于写，如果返回值少于*nobj*，则出错。

# Section 6 定位流

有三种方法定位标准I/O流：

- *ftell*和*fseek*函数。
- *ftello*和*fseeko*函数，除了偏移量的类型为off_t而非long外，与前两个函数作用相同。
- *fgetpos*和*fsetpos*函数，若程序需要移至到非unix系统上运行，则应当是使用这两个函数。 

# Section 7 格式化I/O

## 7.1 格式化输出

*printf*将格式化数据写到标准输出；*fprintf*写到指定的流；*sprintf*将格式化的字符写入某个数组buf中，它还会在该数组的尾端自动加一个null字节，但该字节不包含在返回值中。

**注意：*sprintf*可能会造成由buf指向的缓冲区溢出，为了解决该问题引入了*snprintf*函数。**

## 7.2 格式化输入

*scanf*, *fscanf*, *sscanf*

# Section 8 实现细节

可以对一个流调用*fileno*函数获取其文件描述符。

```
int fileno(FILE *fp);
```

# Section 9 临时文件

ISO C标准I/O库提供了两个函数以帮助创建临时文件。

```
char *tmpnam(char *ptr);
FILE *tmpfile(void);
```

Single UNIX Specification为处理临时文件定义了另外两个函数，它们是XSI的扩展部分。

```
char tempnam(const char *directory, const char *prefix);
int mkstemp(char *template);
```

