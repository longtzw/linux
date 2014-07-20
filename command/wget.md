wget用英语定义就是the non-interactive network downloader，翻译过来就是非交互的网络下载器。

# wget支持的协议

- HTTP
- HTTPS
- FTP
- HTTP代理

# wget的特色

- wget是个非常遵守Robot Exclusion Standard（robots.txt）标准的工具。
- wget支持慢速网络下载和不稳定网络的下载。当因为网络不稳定而导致下载失败时，wget会重试直到把目标文件下载下来为止。
- wget支持断点续传功能，当你下载的很大的文件在中途失败时，这项功能会很有用处。

# 常用选项

## -r选项

递归下载，常用于下载远程的文件夹。需要注意的是，默认情况下会生成目录结构。

## -nd选项

即--no-directories。当我们下载远程的数据时，可以要求wget只下载文件，不下载文件夹，所有下载的文件都平铺在当前目录下。

## -x选项

即--force-directories。这个选项和--no-directories是完全相反的。该选项则要求处处都要有文件夹，
 
## -nH选项

即--no-host-directories。禁止在下载目录是自动创建已服务器名命名的根文件夹。

## --protocol-directories选项

它的作用是先创建一个以协议名为名称的文件夹。


