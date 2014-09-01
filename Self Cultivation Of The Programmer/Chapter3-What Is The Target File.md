编译器编译源代码后生成的文件叫做**目标文件**，目标文件从结构上讲，它是已经编译后的可执行文件格式，只是还没有进过链接的过
程，其中可能有些符号或有些地址还没有被调整。其实它本身就是按可执行文件的格式存储的，只是跟可执行文件在结构上稍有不同。

#Section1 目标文件的格式

现在流行的可执行文件格式主要是Windows下的PE(Portable Executable)和Linux的ELF(Executable Linkable Formate)。

ELF文件标准里把系统中采用ELF格式的文件归为4类：

- 可重定位文件(Relocatable File)，如Linux的.o文件
- 可执行文件(Executable File)，如/bin/bash文件
- 共享目标文件(Share Object File)，如Linux的.so文件
- 核心存储文件(Core Dump File)

#Section2 目标文件是什么样的

目标文件中不仅包含了编译后的机器指令代码、数据，还包括了链接时所需要的一些信息，比如符号表、调试信息、字符串等。一般目标
文件将这些信息按不同的属性，已"节(Section)"的形式存储。

ELF文件的开头是一个"文件头", 它描述了整个文件的属性, 包括是否可执行、是静态链接还是动态链接及入口地址(如果是可执行文件)
、目标硬件、目标操作系统等信息，文件头还包含了一个**段表**用于描述文件中各个段在文件的偏移位置及段的属性等。

一般C语言的编译后执行语句都编译成机器代码，保存在.text段中；已初始化的全局变量和局部静态变量都保存在.date段；未初始化的
全局变量和局部静态变量一般放在一个叫.bss的段里。**.bss段只是为未初始化的全局变量和局部静态变量预留位置而已，它并没有内容
，所以在文件中不占据空间**。

将指令与数据分开的好处有：

- 当程序被装载后，数据和指令分别被映射到两个虚存区域，可以防止程序的指令被有意或无意的改写
- 可以提高CPU缓存的命中率
- 当系统中运行着多个该程序的副本时，它们的指令是一样的，所以只须保存一份该程序的指令部分

#Section3 挖掘SimpleSection.o

objdump可以查看各种目标文件的结构和内容，readelf是专门针对ELF文件格式的解析器。

```
objdump -h SimpleSection.o

SimpleSection.o:     file format elf32-i386

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         00000050  00000000  00000000  00000034  2**2
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000008  00000000  00000000  00000084  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000004  00000000  00000000  0000008c  2**2
                  ALLOC
  3 .rodata       00000004  00000000  00000000  0000008c  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .comment      0000002d  00000000  00000000  00000090  2**0
                  CONTENTS, READONLY
  5 .note.GNU-stack 00000000  00000000  00000000  000000bd  2**0
                  CONTENTS, READONLY
```

参数"-h"可以把ELF文件的各个段的基本信息打印出来。

只读数据段(.rodata), 注释信息段(.comment), 堆栈提示段(.note.GNU-stack)
每个段的第2行中的"CONTENTS", "ALLOC"等表示段的各种属性, "CONTENTS"表示该段在文件中存在.

有一个专门的命令叫做"size", 它可以用来查看ELF文件的代码段、数据段和BSS段的长度

```
size SimpleSection.o

text       data     bss     dec     hex filename
  84          8       4      96      60 SimpleSection.o
```

## 3.1 代码段

objdump的'-s'参数可以将所有段的内容以十六进制的方式打印出来, '-d'参数可以将所有包含指令的段反汇编。

```
Contents of section .text:
 0000 5589e583 ec188b45 08894424 04c70424  U......E..D$...$
 0010 00000000 e8fcffff ffc9c355 89e583e4  ...........U....
 0020 f083ec20 c7442418 01000000 8b150400  ... .D$.........
 0030 0000a100 0000008d 04020344 24180344  ...........D$..D
 0040 241c8904 24e8fcff ffff8b44 2418c9c3  $...$......D$...

Disassembly of section .text:

00000000 <func1>:
   0:   55                      push   %ebp
   1:   89 e5                   mov    %esp,%ebp
   3:   83 ec 18                sub    $0x18,%esp
   6:   8b 45 08                mov    0x8(%ebp),%eax
   9:   89 44 24 04             mov    %eax,0x4(%esp)
   d:   c7 04 24 00 00 00 00    movl   $0x0,(%esp)
  14:   e8 fc ff ff ff          call   15 <func1+0x15>
  19:   c9                      leave  
  1a:   c3                      ret    

0000001b <main>:
  1b:   55                      push   %ebp
  1c:   89 e5                   mov    %esp,%ebp
  1e:   83 e4 f0                and    $0xfffffff0,%esp
  21:   83 ec 20                sub    $0x20,%esp
  24:   c7 44 24 18 01 00 00    movl   $0x1,0x18(%esp)
  2b:   00 
  2c:   8b 15 04 00 00 00       mov    0x4,%edx
  32:   a1 00 00 00 00          mov    0x0,%eax
  37:   8d 04 02                lea    (%edx,%eax,1),%eax
  3a:   03 44 24 18             add    0x18(%esp),%eax
  3e:   03 44 24 1c             add    0x1c(%esp),%eax
  42:   89 04 24                mov    %eax,(%esp)
  45:   e8 fc ff ff ff          call   46 <main+0x2b>
  4a:   8b 44 24 18             mov    0x18(%esp),%eax
  4e:   c9                      leave  
  4f:   c3                      ret    
```
"Contents of section .text"就是.text的数据以十六进制方式打印出来的内容, 最左边一列是偏移量, 中间4列是十六进制内容, 最右
边一列是.text段的ASCII码形式。

## 3.2 自定义段

GCC提供了一个扩展机制, 使程序员可以指定变量所在的段:

```
__attribute__((section("FOO"))) int global = 42;
__attribute__((section(""BAR))) void foo()
{
}
```

此时变量global就将被放在"FOO"作为段名的段中。

#Sections4 ELF文件结构描述

## 4.1 文件头

我们可以通过readelf命令来详细查看ELF文件

```
readelf -h SimpleSection.o

Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (Relocatable file)
  Machine:                           Intel 80386
  Version:                           0x1
  Entry point address:               0x0
  Start of program headers:          0 (bytes into file)
  Start of section headers:          272 (bytes into file)
  Flags:                             0x0
  Size of this header:               52 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           40 (bytes)
  Number of section headers:         11
  Section header string table index: 8
```

## 4.2 段表

ELF文件的段结构就是由段表决定的, 编译器、链接器和装载器都是依靠段表来定位和访问各个段的属性的。

查看完整的段表结构:

```
readelf -S SimpleSection.o

There are 11 section headers, starting at offset 0x110:

Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .text             PROGBITS        00000000 000034 000050 00  AX  0   0  4
  [ 2] .rel.text         REL             00000000 000434 000028 08      9   1  4
  [ 3] .data             PROGBITS        00000000 000084 000008 00  WA  0   0  4
  [ 4] .bss              NOBITS          00000000 00008c 000004 00  WA  0   0  4
  [ 5] .rodata           PROGBITS        00000000 00008c 000004 00   A  0   0  1
  [ 6] .comment          PROGBITS        00000000 000090 00002d 01  MS  0   0  1
  [ 7] .note.GNU-stack   PROGBITS        00000000 0000bd 000000 00      0   0  1
  [ 8] .shstrtab         STRTAB          00000000 0000bd 000051 00      0   0  1
  [ 9] .symtab           SYMTAB          00000000 0002c8 000100 10     10  10  4
  [10] .strtab           STRTAB          00000000 0003c8 00006b 00      0   0  1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings)
  I (info), L (link order), G (group), x (unknown)
  O (extra OS processing required) o (OS specific), p (processor specific)
```

**段的类型**

常量          |值  |含义
--------------|----|------------------------------------------------------
SHT_NULL      |0   |无效段
SHT_PROGBITS  |1   |程序段、代码段、数据段都是这种类型
SHT_SYMTAB    |2   |表示该段的内容为符号表
SHT_STRTAB    |3   |表示该段的内容为字符串表
SHT_RELA      |4   |重定位表，该段包含了重定位信息
SHT_HASH      |5   |符号表的哈希表
SHT_DYNAMIC   |6   |动态链接信息
SHT_NOTE      |7   |提示信息
SHT_NOBITS    |8   |该段在文件中没有内容，比如.bss段
SHT_REL       |9   |该段包含了重定位信息
SHT_SHLIB     |10  |保留
SHT_DNYSYM    |11  |动态链接的符号表

**段的标志位**

段的标志位表示该段在进程虚拟空间中的属性, 比如是否可写、是否可执行等

常量          |值|含义
--------------|--|-----------------------------
SHF_WRITE     |1 |表示该段在进程空间中可写
SHF_ALLOC     |2 |表示该段在进程空间中须分配空间
SHF_EXECINSTR |3 |表示该段在进程空间中可以被执行


