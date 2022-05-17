前言：组织最近发布了一项任务，大概就是让搞过算法的同学去做一个词云类似的图像处理内容，刚开始时找到了wordcloud，但是感觉太没有技术含量了，所以来学一学pillow，好歹还能加点自己的idea

## pillow库函数简单介绍

### 字体设置
```python
from PIL import ImageFont
font = ImageFont.truetype('msyh.ttc', 10)
# font = ImageFont.truetype("字体名称", 字体大小)
```

### 图像处理

在pillow中，每一个图像文件都可以用一个对象表示

```python
from PIL import Image
# 首先导入图像库
```

-  打开图像与图像对象

```python
im = Image.open('文件地址')
```

- 图像大小

```python
im.size 
# 返回一个tuple(参数1, 参数2)
# 参数1表示宽，参数2表示高
```

- 建立新的图像

```python
# newImg = Image.new(mode, (width, height), 背景色)
# newImg = Image.new("RGBA", (width, height), (20, 20, 20))
# mode常用RGB或RGBA
```

- 获取像素点的颜色

```python
a, b, c = im.getpixel((j, i)) #获取指定位置的像素
# 第一个参数表示列，第二个参数表示行
```

- 在新图像上绘制文字

```python
draw = ImageDraw.Draw(newImg)
draw.text((j, i), txt[x], fill=(a, b, c), font=font)
del draw
```

## 实现一些好玩的project

### 生成文字像素画

```python
# coding=utf-8
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
import random
txt = '自为风月马前卒'  # 设置图片中文字的构成
fontsize = 7
# 这个参数如果太小，会使字太小，不够清晰，但整体视觉效果好
# 如果这个参数太大，会使字太大，影响视觉效果
font = ImageFont.truetype('simsun.ttc', fontsize)  # 9为字体大小
im = Image.open('img.jpeg')  # im为待操作的对象
width, height = im.size
newImg = Image.new("RGBA", (width, height), (10, 10, 10))
# 生成待输出的文件
# RGBA用来生成背景色
x = 0
for i in range(0, height, fontsize):  # 需要与字体大小一致
    for j in range(0, width, fontsize):  # 需要与字体大小一致
        a, b, c = im.getpixel((j, i)) #获取指定位置的像素
        draw = ImageDraw.Draw(newImg)
        draw.text((j, i), txt[x], fill=(a, b, c), font=font)
        x += 1
        x %= 7
        del draw
newImg.save('result.png', 'PNG')
```

原图：

![](http://cdn.attack204.com/img.jpeg)

生成的图片(感觉好掉价)....

![](http://cdn.attack204.com/result.png)

## 参考资料

[pillow中文文档](https://www.osgeo.cn/pillow/index.html)

[使用Pillow（PIL）库实现中文字符画](https://www.cnblogs.com/kagari/p/10286247.html)

[Python的Pillow库进行图像文件处理（配图详解）](https://blog.csdn.net/wfy2695766757/article/details/81193370)