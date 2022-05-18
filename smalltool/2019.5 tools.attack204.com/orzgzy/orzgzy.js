var GZYBEIKANLE = 0.0;
function orzGZY() {

    document.getElementById("mainarea").innerHTML = "\
                                                    <p align=\"center\">\
                                                    <span style=\"font-size: 128px; color:rgb(66,133,244)\">O</span>\
                                                    <span style=\"font-size: 128px; color:rgb(234,7,53)\">r</span>\
                                                    <span style=\"font-size: 128px; color:rgb(251,188,5)\">z</span>\
                                                    <span style=\"font-size: 128px; color:rgb(66,133,244)\">G</span>\
                                                    <span style=\"font-size: 128px; color:rgb(52,168,83)\">Z</span>\
                                                    <span style=\"font-size: 128px; color:rgb(234,7,53)\">Y</span>\
                                                    </p>\
                                                    <p align=\"center\">\
                                                    <img src=\"/orzgzy/orz.jpg\" style=\"margin:30px;transform:scaleX(-1) scaleY(1);position:relative;top:60px\">\
                                                    <img src=\"/orzgzy/gzy2.jpg\" style=\"border-radius:30px;box-shadow:0px 0px 100px #ff0000;position:relative;top:30px width:400px;height:400px;\">\
                                                    <img src=\"/orzgzy/orz.jpg\" style=\"margin:30px;position:relative;top:60px\"></p><p align=\"center\" style=\"margin: 30px\">\
                                                    <span style=\"font-size: 48px;color: #FF0000\">GZY是我们的红太阳，没有他我们会死！</span>\
                                                    </p>\
                                                    <div id=\"orz\" align=\"center\"><p align=\"center\">\
                                                    <button  class=\" mdui-btn mdui-btn-raised mdui-ripple mdui-color-theme-accent\" style=\"font-size: 30px; color: #FF0000\" onclick=\"orzorz()\">\
                                                    点击膜拜\
                                                    </button>\
                                                    </div>\
                                                    ";
}
function orzorz() {
    if (Math.random() < GZYBEIKANLE) {
        document.getElementById("orz").innerHTML = "\
                                                    <p style=\"margin:10px\">\
                                                    <span style=\"font-size: 40px; color: #FF0000\">\
                                                    震惊！GZY被砍死了！\
                                                    <br>\
                                                    <img src=\"https://xzz-233.github.io/orzGZY/witcher5.png\" style=\"width:100%;height:auto;\">\
                                                    ";
        document.title = "震惊！";
        return;
    }
    document.getElementById("orz").innerHTML = 
    "\
    <p style=\"margin:10px\">\
    <span style=\"font-size: 40px; color: #FF0000\">\
    膜拜成功！\
    <br>\
    GZY又变强了！\
    </span>\
    </p>\
    <p style=\"margin:10px\">\
    <img src=\"/orzgzy/gzy1.jpg\" style=\"width:500px;height:800px;\">\
    </p>\
    </span>\
    <br>\
    <div class=\"mdui-container\">\
    <button class=\" mdui-btn mdui-btn-raised mdui-ripple mdui-color-theme-accent\" style=\"font-size: 24px\" onclick=\"ORZINF()\" id=\"ORZORZORZ\">继续膜拜1次</button>\
    ";


    document.title = "orz GZY!";
}
var cnt = 0, delta = 1;
function ORZINF() {
    cnt += delta;
    alert('OrzGZY!*' + cnt);
    if (cnt == 1) alert('GZY：诶又有一个来膜拜我的，来吧来吧继续膜');
    if (cnt == 2) alert('GZY：你们还是naive，我又AK了');
    if (cnt == 10) alert('GZY：虽然我是大佬，但是你这样一直膜我是会掉RP的');
    if (cnt == 20) alert('GZY：MDZZ你怎么还在膜信不信我把你从5楼扔下去');
    if (cnt == 50) alert('GZY：没错我就是这么强，让你好好膜');
    if (cnt == 50) delta = 5, document.getElementById("ORZORZORZ").innerHTML = "继续膜拜" + delta + "次";
    if (cnt == 1000) alert('GZY：你真棒，我感受到了我又变强了，让你一次多膜一点');
    if (cnt >= 1000) {
        delta = Math.floor(Math.random() * 100 + 5);
        document.getElementById("ORZORZORZ").innerHTML = "继续膜拜" + delta + "次";
    }
    if (cnt >= 10000) {
        alert('GZY：MMP你就要吸走我1%的RP了');
        alert('GZY：你再膜我就变弱了');
        alert('你被GZY秒了');
        alert('保持你的决心！');
        document.getElementById("mainarea").innerHTML = "<h1>被秒乃蒟蒻常事<br>请蒟蒻重新来过！</h1>";
    }
}