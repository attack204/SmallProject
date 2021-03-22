/*
version1:
可以实现自动点击第二个按钮
*/

var a = document.getElementsByClassName("s");
for (var i = 0; i < a.length; i++) {
    var b = a[i].childNodes;
    var c = b[3].childNodes;
    var d = c[1];
    d.click();
}
var txt = document.getElementsByClassName("j-textarea inputtxt");
lyrics = new Array();
lyrics[1] = "向前跑";/* */
lyrics[2] = "向前跑";
lyrics[3] = "迎着冷眼和嘲笑";
lyrics[4] = "生命的广阔不历经磨难怎能感到";
lyrics[5] = "命运它无法让我们跪地求饶";
lyrics[6] = "就算鲜血洒满了怀抱";
for (var i = 0; i < txt.length; i++) {
    txt[i].value = lyrics[i % 6 + 1];
}


/*
version2:
可以自动点击最后一个按钮
*/

var a = document.getElementsByClassName("s");
for (var i = 0; i < a.length; i++) {
    var b = a[i].childNodes;
    var c = b[a[i].childNodes.length - 2].childNodes;
    var d = c[1];
    d.click();
}
var txt = document.getElementsByClassName("j-textarea inputtxt");
lyrics = new Array();
lyrics[1] = "向前跑";/* */
lyrics[2] = "向前跑";
lyrics[3] = "迎着冷眼和嘲笑";
lyrics[4] = "生命的广阔不历经磨难怎能感到";
lyrics[5] = "命运它无法让我们跪地求饶";
lyrics[6] = "就算鲜血洒满了怀抱";
for (var i = 0; i < txt.length; i++) {
    txt[i].value = lyrics[i % 6 + 1];
}


/*
version3:
随机在后两个按钮中点击一个
并保证每十个按钮中得满分的期望个数为9
*/

var a = document.getElementsByClassName("s");
for (var i = 0; i < a.length; i++) {
    var b = a[i].childNodes;
    var rnd = Math.floor(Math.random() * 10), add = 2; /*rnd = [0, 9] */
    if (rnd > 8) add = 4;
    var c = b[a[i].childNodes.length - add].childNodes;
    var d = c[1];
    d.click();
}
var txt = document.getElementsByClassName("j-textarea inputtxt");
lyrics = new Array();
lyrics[1] = "向前跑";/* */
lyrics[2] = "向前跑";
lyrics[3] = "迎着冷眼和嘲笑";
lyrics[4] = "生命的广阔不历经磨难怎能感到";
lyrics[5] = "命运它无法让我们跪地求饶";
lyrics[6] = "就算鲜血洒满了怀抱";
for (var i = 0; i < txt.length; i++) {
    txt[i].value = lyrics[i % 6 + 1];
}