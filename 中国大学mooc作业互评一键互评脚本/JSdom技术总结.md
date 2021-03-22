js dom总结

万物皆可百度，比较好用的手册地址如下

[菜鸟教程](https://www.runoob.com/jsref/jsref-tutorial.html)(重点关注里面的"HTML DOM 参考手册"部分)

1. 用document.getElementsByClassName获取到的是一个数组。而不是一个元素

2. 让非本地页面加载jq的方法 直接改head页面，里面加一句

<script src="https://apps.bdimg.com/libs/jquery/2.1.4/jquery.min.js"></script>

3. dom语句总结 childNodes可以获取节点列表，再通过列表的长度可以获得每一个元素

firstChild 可以获取第一个元素

lastChild 可以获取最后一个元素

但有件事需要注意以下

```javascript
<div class="s">
    <label class="d" for="j-select-2188799188701830-1601376657913">
        <input id="j-select-2188799188701830-1601376657913" type="radio" name="j-select-218879918870183-1601376657913" class="j-select" data-jid="218879918870183" value="0" checked="true">
        <span class="f-ib sc">0 分)</span>
    </label>
    <label class="d" for="j-select-2188799188701831-1601376657913">
        <input id="j-select-2188799188701831-1601376657913" type="radio" name="j-select-218879918870183-1601376657913" class="j-select" data-jid="218879918870183" value="1">
        <span class="f-ib sc">1 分)</span>
    </label>
</div>
```

对于这一段代码 假设a = getElementsByClassName("s").childNodes;获取元素 a的长度是5而不是2 因为div与label之间的部分也被当做一个标签处理 即5个子节点为 0 空 1 label1 2 空
3 label2 4 空
