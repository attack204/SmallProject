# 经典问题-float塌陷问题
## 关于ul中的li浮动之后消失的问题

1. 问题复现：

考虑这样一段代码 
```css
ul {
    list-style-type: none;
    padding-left: 0px;
    background-color: #000;
}
ul li {
    float: left;
    margin-left: 20px;
    margin-top: 10px;
    margin-bottom: 10px;
    line-height: 30px;
}
a {
    color: #fff;
    text-decoration: none;
}
```

```html

<ul>
    <li><a href="https://www.baidu.com">百度</a></li>
    <li><a href="https://attack204.com">个人博客</a></li>
    <li><a href="https://www.js.org">js官网</a></li>
</ul>
```

运行效果令人大吃一惊：居然什么都没有

![123](http://cdn.attack204.com/20200801191240.png)


2. 原因

最终要的是`<li>`标签设置了浮动(`float: left`)。然后浮起来之后原来的位置的高度就没有了，这个可以打开控制台看，确实是没有的

![](http://cdn.attack204.com/20200801191738.png)

3. 解决方案

没有高度，这个好办，加一个div，撑起来

```html
<ul>
    <li><a href="https://www.baidu.com">百度</a></li>
    <li><a href="https://attack204.com">个人博客</a></li>
    <li><a href="https://www.js.org">js官网</a></li>
    <div style="clear: both; line-height: 0px;"></div><!--这里面不能写文字>
</ul>
```

## 浮动

这部分是之后学的，但是上面用到了浮动，就写到这里了

很关键的一件事是浮动的意义：浮动可以将许多块标签弄到同一行里，以增强排版效果

关键的一点是注意防止浮动之后div标签塌陷

解决方案是在div标签中加一行

```html
<div style="clear: both;"></div>
```

### 关于浮动更深入的理解：

1. 浮动之后会脱离文档流，而一个div标签一旦脱离文档流，那么他就会失去独占一行的特点

2. 浮动仅仅能相对于原来文档流的位置左右浮动。浮动和定位完全是两码事，定位给个坐标可以乱定位，而浮动只能基于原来文档流的位置浮动

### 清除浮动

clear: left;的意思不是把浮动效果清楚，而是使该元素浮动时左侧不能有元素

即
```html
float: left;
clear: left;
```

加上这两行和什么都不写效果是不同的。

第一个图中，绿色的块的左侧被指定不能有元素，因此会到下一行。

第二个图中，红色和蓝色都脱离了文档流，绿色会到左上角。

![](http://cdn.attack204.com/20200912224431.png)

![](http://cdn.attack204.com/20200912224615.png)
