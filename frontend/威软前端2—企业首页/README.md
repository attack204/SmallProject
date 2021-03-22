## exp

- flex和position不可同时应用，可以在外层套一个div来解决

- hover尽量要设置在最外层元素上，设置在内层元素上无法更改外层元素
    * css3的选择器还不支持选择父元素

- 使用了display: flex; 设置了space-around后依旧可以用margin/padding来调整元素样式

- 估算div大小
    * 全屏是2000 * (4/5)px = 1600px
    * 半屏是800px;
    * 1/4屏是400px
    * 1/8屏是200px
    * 50px大概和拇指一样大。。

- 选中第i个孩子:
    * 用p:nth-child(2)可以选中每个是其父亲的第二个孩子的p(suggest:用class选择器来避免重复选择的situation)

- 制作动画时尽量不要使用display:none来做动画切换，比如这个项目中竖线消失可以用height: 0px;

- 关于每个元素块下方的线虽鼠标移动的制作方法
    * 将此元素绝对定位，然后每次的left加上块的大小的数值

- hover与mouseenter、mouseleave的区别
    * hover是css选择器，而mouseenter是鼠标事件
    * hover=mouseenter+mouseleave?..感觉有点神奇

- 导航栏的underline线不要用border，直接把height调成线高，再用定位
    * 因为div的高度如果比较高的话，会挡住导航栏中的元素

- width: x%;默认是父元素的百分比，如果想要继承父亲的父亲的宽度的话可以手动算一下

- 鼠标悬停时轮播动画，需要保证左侧元素是-100%，右侧元素是100%

- 外层div宽高无法改变，但是又需要加padding, margin等修饰
    * 可以在这个div下面再加一个div，但是需要更改一些css元素，比如flex，
    * 或者改变一下box的计算方法也行

- js无法计算css的具体值，比如a.style.width -= "10px";，什么都不会发生
    * 因为开始时获取到的width是0

- 两种轮播图的制作方法

- 当一个元素设置了absolute之后，即便其父元素有overflow:hidden，此元素也不会被裁剪
    * [但是当其父亲设置了relative之后此元素会被裁剪](https://www.cnblogs.com/yier0705/p/9182262.html)

## 优化

- 导航栏制作可以把div换成li，让文档更清晰一些
- 轮播图不会无限循环

## 技术总结

### 第一个轮播图

由于仅仅涉及到向左/向右，因此无需关心页面呈现出来的是哪几个元素.

这样的话可以弄一个大的div来容纳所有元素，然后移动这个大的div即可

### 第二个轮播图

由于涉及到当前哪个元素在最前面，因此把最前面元素的left设置为0，

除此之外左边的元素left设置为-100%，右边的元素设置为100%即可

## unknown

- ()中的this
