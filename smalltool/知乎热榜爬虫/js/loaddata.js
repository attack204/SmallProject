function load(name) {
    let xhr = new XMLHttpRequest(),
        okStatus = document.location.protocol === "file:" ? 0 : 200;
    xhr.open('GET', name, false);
    xhr.overrideMimeType("text/html;charset=utf-8");//默认为utf-8
    xhr.send(null);
    return xhr.status === okStatus ? xhr.responseText : null;
}

var text = load("data.txt");//搜索文件
var list = text.split('\n');
let AppearTimes = [].fill(0); //(key, value)记录了每个字符串的出现次数
// AppearTimes[1] =1; 
console.log(AppearTimes[1]);
let AppearSet = new Set();//维护所有字符串出现的集合
let Xlist = [], Ylist = [];
for (var i = 0; i < text.length; i++) {
    if (text[i] != '如' && text[i + 1] != '如' &&
        text[i] != '会' && text[i + 1] != '会' &&
        text[i] != '何' && text[i + 1] != '何' &&
        text[i] != '评' && text[i + 1] != '评' &&
        text[i] != '哪' && text[i + 1] != '哪' &&
        text[i] != '么' && text[i + 1] != '么' &&
        '\u4e00' <= text[i] && text[i] <= '\u9fff' && '\u4e00' <= text[i + 1] && text[i + 1] <= '\u9fff') {
        var ch = text[i] + text[i + 1];
        if (AppearTimes[ch] == undefined)
            AppearTimes[ch] = 1;
        else
            AppearTimes[ch] += 1;
        AppearSet.add(ch);
    }
}

console.log(AppearTimes["穷人"]);
AppearSet.forEach((item) => {
    if (item == "怎么" || item == "如何" || item == "哪些" || item == "什么" || item == "看待" || item == "可以" || item == "何看")
        var a = 1;
    else if (AppearTimes[item] > 2)
        Xlist.push(item),
            Ylist.push(AppearTimes[item]);
})
console.log(Xlist);
console.log(Ylist);