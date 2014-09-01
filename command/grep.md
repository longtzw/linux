# Section 1 Practical Grep Command Examples 

## 1.1 搜索时忽略大小写

```
grep -i "string" FILE
```

## 1.2 显示匹配行前后行的内容

### 1.2.1 显示匹配行后的 N 行

```
grep -A <N> "string" FILE
```

### 1.2.2 显示匹配行前的 N 行

```
grep -B <N> "string" FILE
```

### 1.2.3 显示匹配行前后各 N 行

```
grep -C <N> "string" FILE
```

## 1.3 匹配整个单词而非子字符串

```
grep -w "word" FILE
```

## 1.4 通过 'GREP_OPTIONS' 高亮匹配的字符串

```
export GREP_OPTIONS='--color=auto' GREP_COLOR='100;8'
```

## 1.5 反转匹配项

```
grep -v "string" FILE
```

## 1.6 显示不包含所有指定字符串的行

```
grep -v -e "pattren1" -e "pattren2" FILE
```

## 1.7 统计匹配行数

```
grep -c "string" FILE
```

## 1.8 显示包含匹配项的文件

```
grep -l "string" FILES
```

## 1.9 仅显示匹配项本身而非包含匹配项的行

```
grep -o "string" FILE
```

## 1.10 输出时显示行号

```
grep -n "string" FILE
```

