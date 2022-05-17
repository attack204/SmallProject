## 基本数据类型

### number数字

### string字符串

### list列表

1. 反转输出list

比较类似于不指定类型的数组

以下实例可以将字符串反转输出

第二个参数为空表示移动到序列首位暂停

```python
a = [1, 2, 3, 4, 7, 9, 11]
print(a[-1 : : -1])
```

2. 创建二维list

可以借助生成器来实现

```python
Max = 10
mp = [[0 for i in range(0, Max)] for j in range(0, Max)]
print(mp)
```

### tuple元组

就是个不能改的list

### set集合

set中的元素不能重复

以下为两种初始化set的方式

```python
a = set("csdabababaa")
print(a)
print(type(a))
b = {'A', 'A', 'B'}
```

set集合可以进行交并补等运算

### dictionary字典

跟c++里的map差不多

注意使用之前必须初始化
```python
mp = {}
mp['0'] = 1
mp['2'] = 2
print(mp['2'])
```

notice: 若查找的元素不在字典中，则会出现KeyError，解决方法也很简单，只需要判断一下是否定义过即可

```python
if(str in data):
    data[str] += 1
else:
    data[str] = 1
```


## 运算符

`/`表示除法，python会自动转化为小数进行运算

`//`表示舍弃小数部分

`*`，对于字符串而言可以输出字符串两次

`+`, 对于字符串而言表示连接运算符


## 文件输入输出

文件输入

```python
txt = open(r"data.txt", "r").read()
print(txt)
```

文件输出

```python
tar = open("data.txt", "w")
word = ["航母", "分秒", "淡忆", "小公主", "AK", "步篱", "#", "小那", "鱼跃"]
for i in range(0, 9):
    for j in range(0, 9 - i):
        print(word[i], end = " ", file = tar)
tar.close()
```