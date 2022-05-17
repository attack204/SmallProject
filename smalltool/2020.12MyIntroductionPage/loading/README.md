## Project

抄袭自b站up主[阿阳爱前端](https://space.bilibili.com/478490349?from=search&seid=15637414196753996085)orz

优化了一些细节

## 实现思路

利用一个元素 + before + after伪元素来设置三个圆

然后加点动画就好了

其实在实际项目开发的时候需要过一段时间隐藏掉

可以在页面中加一个大div

然后用js的timeout函数，先把opacity设置为0

然后再display: none;

因为直接display: none的话不会有动画qwq(transition不能设置display但是可以设置opacity)

具体直接看代码吧

## demo

![](http://cdn.attack204.com/demo.gif)

