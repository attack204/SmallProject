# 总结-line与height-line的区别


update in 2020.9.17

根据height与line-height的不同，可以很容易自定义下划线

## height与line-height的区别

直观理解一下，height是对于div标签而言的，它规定的是div标签的高度

而line-height是对于div标签内的元素而言的，它规定的是div标签内每个元素的高度

比如下面一段代码

```css
* {
    margin: 0px;
}
.test {
    background-color: #f00;
    line-height: 40px;
    /* height: 40px; 这句话 */
}
```

```html
<div class="test">
    <p>123</p>
    <p>123</p>
    <p>123</p>
    123
</div>
```

如果加上上面的那句话

![](http://cdn.attack204.com/20200803100735.png)

如果不加

![](http://cdn.attack204.com/20200803100908.png)

**注意**：如果只有单行的文字，仅设置line-height还可以起到垂直居中的效果

**补充**: line-height的定义

[这篇文章写的不错](https://blog.csdn.net/a2013126370/article/details/82786681)

我来整理一下精髓

首先，line-height的定义是：两行文字中，字母`x`下边缘之间的距离。注意两个"中"字下边缘之间的距离并不是line-height，因为"中"字个头比较大。这里的"个头大"，就是指的字体比较大(相对于`x`而言)。
    
![](http://cdn.attack204.com/20200803101351.png)

因此，当line-height比较小的时候，就可以打造出文字重叠的效果

![](http://cdn.attack204.com/20200803101847.png)

(这个效果就是通过把上面代码的line-height改为9px实现的)

