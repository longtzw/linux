触发oom-killer，在2.6内核的表现是，杀掉占用内存最高的进程。

top命令通过解析/proc/pid/statm统计VIRT和RES和SHR字段值。

- VIRT：进程总的虚拟内存使用量，包括物理内存使用量、交换分区中的内存使用量，通过各种途径映射到虚拟内存空间的内存使用量（如通过TI的CMEM工具分配的ARM与DSP间通信连续的内存）。在32位系统中，每个进程都用有3G独立的虚拟内存空间。
- RES：进程由操作系统管理的物理内存使用量。
- SHR：RES中”映射至文件”的物理内存总和。包括：
	+ 程序的代码段。
	+ 动态库的代码段。
	+ 通过mmap做的文件映射。
	+ 通过mmap做的匿名映射，但指明了MAP_SHARED属性。
	+ 通过shmget申请的共享内存。
