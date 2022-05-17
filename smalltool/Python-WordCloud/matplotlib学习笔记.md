## 安装

```python
pip install matplotlib
```

## 语法

### plot([x], [y])

在平面直角坐标系中作图

第一个值是对应的横坐标，第二个值是横坐标对应的纵坐标

### figure()

![详细教程](https://blog.csdn.net/m0_37362454/article/details/81511427)

### hist([x])

生成直方图，只需要输入一个数组[x]，plt会自动统计每个元素的出现次数，然后输出一下




## 例子

### 绘制[-pi, pi]上的sin函数图像

```python
import matplotlib.pyplot as plt #导入matplotlib库
import numpy as np
x = np.linspace(-np.pi, np.pi, 10) #生成一个从[-pi, pi]之间，有100个点的直线
plt.plot(x, np.sin(x))
plt.show()
```

### 绘制多条曲线

```python
import matplotlib.pyplot as plt
import numpy as np
x = np.linspace(-2 * np.pi, np.pi, 100)
# plt.figure(1, dpi = 100)
# 这句话是设置窗口的大小
plt.plot(x, np.sin(x))
plt.plot(x, np.sin(x / 2))
plt.plot(x, np.sin(x) / 2)
plt.show()
```

### 绘制频数分布直方图

```python
import matplotlib.pyplot as plt
import numpy as np
data = [1, 2, 2, 3, 4, 5, 6]
plt.hist(data)
plt.show()
```

## 参考资料


![奇奇怪怪的中文文档](https://www.osgeo.cn/matplotlib/contents.html)

