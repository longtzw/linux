# 概述

aptitude与apt-get一样，是Debian及其衍生系统中功能极其强大的包管理工具。与apt-get不同的是，aptitude在处理依赖问题上更佳一些。
举例来说，aptitude在删除一个包时，会删除本身所依赖的包。这样，系统中不会残留无用的包，整个系统更为干净。

# 安装源配置文件

/etc/apt/sources.list

# 查找软件包

```
aptitude search package-name
```
所列出的每个软件包前都有一个表示状态的字符：

- i 表示这个包已安装
- p 表示这个包在软件库中，但还没被安装
- c 表示这个包包已被删除，但保留了配置文件

# 安装软件

```
sudo aptitude install package-name
```

# 卸载软件

```
sudo aptitude remove package-name
```
只卸载软件，但保留数据和配置文件。

```
sudo aptitude purge package-name
```
卸载软件并删除相关数据和配置文件。

# 更新可用的包列表

```
aptitude update
```

# 升级可用的包

```
aptitude upgrade
```

# 将系统升级到新的发行版

```
aptitude dist-upgrade
```

# 显示包的详细信息

```
aptitude show pkgname
```

# 删除下载的包文件

```
aptitude clean
```

# 仅删除过期的文件

```
aptitude autoclean
```
