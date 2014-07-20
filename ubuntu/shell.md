###top

- 'M' 按内存使用情况排序，'O' 选则可以选择任意top输出列进行排序，'R'对当前排序进行反转。

###unzip

查看压缩文件内容

```
unzip -l file.zip 
```

解压文件

```
unzip file.zip -d dir-name
```

###rar

解压文件

```
rar x file.rar
```

###grep

显示匹配行后的N行

```
grep -A <N> "string" FILENAME
```

显示匹配行前的N行

```
grep -B <N> "string" FILENAME
```

显示匹配行附近的N行

```
grep -C <N> "string" FILENAME
```

高亮匹配的字符串

```
export GREP_OPTIONS='--color=auto' GREP_COLOR='100;8'
grep "string" FILENAME
```

忽略大小写
```
grep -i "string" FILE
```

只匹配整个单词，而不是字符串的一部分

```
grep -w pattern file
```

显示匹配pattern1或pattern2的行

```
grep -E 'pattern1|pattern2' file
```

显示既匹配pattern1又匹配pattern2的行

```
grep -E "pattern1.*pattern2" file
```

显示不匹配pattern的行

```
grep -v pattern file
grep -v -e pattern1 -e pattern2 file
```		

计算匹配次数

```
grep -c "pattern" filename
```

###sed

**sed编辑器可以基于输入输入到命令行的或是存储在命令文本文件中的命令来处理数据流中的数据。它每次从输入中读取一行，用提供的编辑器命令匹配数据，按命令中指定的方式修改流中的数据。**

**sed编辑器本身自身不会修改文本文件的数据。它只会将修改后的数据发送到STDOUT。**

#####在命令行上使用多个编辑器命令

```
sed -e 's/brown/green/; s/dog/cat/' data
```

**注意：命令之间必须用分号分隔，并且在命令的末尾和分号之间不能存在空格。**

在bash shell中，可以使用次级提示符(>)，而不是分号分隔命令。

若有大量地处理sed命令，可以将它们放在一个script文件中，同过'-f'选项指定script文件

```
sed -f script data
```

#####替换标记

```
s/pattern/replacement/flags
```

可用的替换标记有以下4种：

- 数字：表示替换各行中第n个匹配项
- g：表示替换全部实例
- p：打印发生替换的行(替换完毕的结果，常与'-n'选项<禁止输出>配合使用)
- w：将替换结果写入文件

#####替换字符

当需要替换的字符中包含'/'时，可以使用'!'作为字符串界定符，当然也可以通过'\'转义

```
sed !/bin/bash!/bin/csh!
```

#####数字式行寻址

仅替换第2~3行中匹配的字符串

```
sed '2,3s/dog/cat/'
```

#####使用文本模式筛选器

仅替换包含'rich'的行

```
sed '/rich/s/bash/csh/'
```

**如果要在单独一行上执行多个命令，请使用大括号将命令组合在一起。**

#####删除行

#####插入行

#####更改行

#####单行next命令

小写n命令告诉sed编辑器移动到匹配字符所在行的下一行执行相应的命令。

#####组合多行文本

```
[t01414@Compile243 script]$ cat sed_data 
The first meeting of the Linux System
Administrator's group will be held on Tuesday.
All System Administrator should attend this meeting.

[t01414@Compile243 script]$ sed '
> s/system Administrator/Desktop User/
> N
> s/System\nAdministrator/Desktop\nUser/
> ' sed_data
The first meeting of the Linux Desktop
User's group will be held on Tuesday.
All System Administrator should attend this meeting
```

查找短语的单行替换命令可以处理数据流的最后一行，并且多行替换命令涵盖了数据流中间的情况。

**模式空间** **保留空间**

######sed编辑器保留空间命令

命令   |描述
-------|------------------------------
h 	   |将模式空间复制到保留空间
H 	   |将模式空间追加到保留空间
g 	   |将保留空间复制到模式空间
G 	   |将保留空间追加到模式空间
x      |将保留空间和模式空间的内容互换

#####反转文本行

```
[t01414@Compile243 script]$ cat sed_data1
This is the header line.
This is the first data line.
This is the second data line.
This is the lase line.

[t01414@Compile243 script]$ sed -n '
> 1!G  # 第1行不执行追加
> h    
> $p   # 最后一行才打印
> ' sed_data1
This is the lase line.
This is the second data line.
This is the first data line.
This is the header line.
```
#####分支

```
[t01414@Compile243 script]$ sed '
> /first/b jump    "jump 为标签名，若标签名不存在则命令执行跳过匹配的那几行
> s/ is/ might be/
> s/line/test/
> :jump
> s/data/text/     "跳转到标签后执行的命令
> ' sed_data1
This might be the header test.
This is the first text line.
This might be the second text test.
This might be the lase test.
```

####模式替换

#####'&'与号

替换命令中的匹配模式

```
[t01414@Compile243 ~]$ echo "The cat sleeps in his hat." | sed 's/.at/"&"/g'
The "cat" sleeps in his "hat".
```

####创建sed工具

#####双倍行距

```
sed '$!G' data
```

#####对可能有空行的文件使用双倍行距

```
sed '/^$/d; $!G' data "先删除空行，再在所有行后面添加空行
```

###gawk

gawk将下面的变量分配给在文本行中检测到的每个数据字段：

- $0 表示整行
- $n 表示文本行中的第n(n > 0)个数据字段

各数据字段根据文本行中的**字段分割符**确定，默认的为任意空白字符，可以通过'-F'选项指定。

```
gawk -F: '{print $1}' /etc/passwd
```

#####在命令行中使用多个命令

```
echo "My name is Rich" | gawk '{$4="Dave"; print $0}'
```

#####通过sript文件运行

```
gawk -f script /etc/passwd
```

在script文件中可以用关键字 **BEGIN**, **END** 在执行命令前打印一些信息，变量 **FS** 可以在脚本中指定字段分隔符。

###正则表达式

需要转义的特殊字符：'.*[]^${}\+?|()' 实现这一功能的特殊字符'\'

#####删除文本中的空行

```
sed '/^$/d'
```

'.' 用于匹配除换行符外的任何单个字符

在某个字符后面加'*'表示该字符必须在匹配模式的文本中**不出现或出现多次**

在某个字符后面加'?'表示该字符必须在匹配模式的文本中**不出现或出现1次**

在某个字符后面加'+'表示该字符必须在匹配模式的文本中**出现1次或多次，但至少出现1次**

#####特殊字符类

类             |描述
---------------|------------------------------
[[:alpha:]]    |匹配任意字母字符，不区分大小写
[[:alnum:]]    |匹配任意字母或数字
[[:blank:]]    |匹配空格或字表符
[[:digit:]]    |匹配任意数字
[[:lower:]]    |匹配任意小写字母字符
[[:print:]]    |匹配任意可打印字符
[[:punct:]]    |匹配标点符号
[[:space:]]    |匹配任意空白字符
[[:upper:]]    |匹配任意大写字符

```
echo "bet" | gawk --re-interval '/be{1}t/{print $0}' # 该正则表达式正好出现1次
```

```
echo "bet" | gawk --re-interval '/be{1,2}t/{print $0}' # 该正则表达式至少出现1次，最多出现2次
```

