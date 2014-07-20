![TCP头格式](http://coolshell.cn//wp-content/uploads/2014/05/TCP-Header-01.jpg)

几个注意点：

- TCP的包是没有IP地址的，那是IP层上的事。但是有源端口和目标端口。
- 一个TCP连接需要四个元组来表示是同一个连接（src_ip, src_port, dst_ip, dst_port）准确说是五元组，还有一个是协议。但因为这里只是说TCP协议，所以，这里我只说四元组。
- 注意上图中的四个非常重要的东西：
	+ Sequence Number是包的序号，用来解决网络包乱序（reordering）问题。
	+ Acknowledgement Number就是ACK——用于确认收到，用来解决不丢包的问题。
	+ Window又叫Advertised-Window，也就是著名的滑动窗口（Sliding Window），用于解决流控的。
	+ TCP Flag ，也就是包的类型，主要是用于操控TCP的状态机的。

关于其它的东西，可以参看下面的图示

![其他](http://coolshell.cn//wp-content/uploads/2014/05/TCP-Header-02.jpg)

![TCP建链接、断链接、传数据](http://coolshell.cn//wp-content/uploads/2014/05/tcp_open_close.jpg)

**对于建链接的3次握手**，主要是要初始化Sequence Number 的初始值。

通信的双方要互相通知对方自己的初始化的Sequence Number（缩写为ISN：Inital Sequence Number）

这一过程叫SYN，全称Synchronize Sequence Numbers（TCP会用这个序号来拼接数据）。

![双方同时断连接的示意图](http://coolshell.cn//wp-content/uploads/2014/05/tcpclosesimul.png)

有几个事情需要注意一下：

- **关于建连接时SYN超时** 试想一下，如果server端接到了clien发的SYN后回了SYN-ACK后client掉线了，server端没有收到client回来的ACK，那么，这个连接处于一个中间状态，即没成功，也没失败。于是，server端如果在一定时间内没有收到的TCP会重发SYN-ACK。在Linux下，默认重试次数为5次，重试的间隔时间从1s开始每次都翻售，5次的重试时间间隔为1s, 2s, 4s, 8s, 16s，总共31s，第5次发出后还要等32s都知道第5次也超时了，所以，总共需要 1s + 2s + 4s+ 8s+ 16s + 32s = 2^6 -1 = 63s，TCP才会把断开这个连接。
- **关于SYN Flood攻击** 一些恶意的人就为此制造了SYN Flood攻击——给服务器发了一个SYN后，就下线了，于是服务器需要默认等63s才会断开连接，这样，攻击者就可以把服务器的syn连接的队列耗尽，让正常的连接请求不能处理。于是，Linux下给了一个叫tcp_syncookies的参数来应对这个事——当SYN队列满了后，TCP会通过源地址端口、目标地址端口和时间戳打造出一个特别的Sequence Number发回去（又叫cookie），如果是攻击者则不会有响应，如果是正常连接，则会把这个 SYN Cookie发回来，然后服务端可以通过cookie建连接（即使你不在SYN队列中）。**请注意，请先千万别用tcp_syncookies来处理正常的大负载的连接的情况**。因为，synccookies是妥协版的TCP协议，并不严谨。对于正常的请求，你应该调整三个TCP参数可供你选择，第一个是：tcp_synack_retries 可以用他来减少重试次数；第二个是：tcp_max_syn_backlog，可以增大SYN连接数；第三个是：tcp_abort_on_overflow 处理不过来干脆就直接拒绝连接了。