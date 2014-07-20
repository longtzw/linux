# 安装

```
sudo aptitude install wireshark
```

安装完毕，此时若已非root用户启动wireshark，会提示：No interface can be used for capturing in this system with the current configuration

解决方法如下：

1. 创建一个新组

```
sudo groupadd wireshark
```

2. 将当前用户加入到该组

```
sudo usermod -a -G wireshark your_user_name
```

3. 改变/usr/bin/dumpcap所属的用户组

```
sudo chgrp wireshark /usr/bin/dumpcap
```

4. 改变/usr/bin/dumpcap的执行权限，使其对用户组可执行

```
sudo chmod 750 /usr/bin/dumpcap
```

5. 赋予能力

```
sudo setcap cap_net_raw,cap_net_admin=eip /usr/bin/dumpcap
```

# 基本使用

**彩色标识**

Wireshark通过颜色让各种流量的报文一目了然。比如默认绿色是TCP报文，深蓝色是DNS，浅蓝是UDP，黑色标识出有问题的TCP报文——比如乱序报文。

参考：[一站式学习Wireshark](http://blog.jobbole.com/70907/)
