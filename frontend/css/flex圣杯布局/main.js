"use strict";
var a = document.getElementsByClassName("nav_cell");
for (let j = 0; j < a.length; j++) {
    let cur = a[j];
    for (let k = 0; k < cur.children.length; k++) {
        cur.children[k].onmouseover = function () {
            for (let i = 1; i < cur.children.length; i++) {
                var ch = cur.children[i];
                ch.style.display = "block";
            }
        };
        cur.children[k].onmouseout = function () {
            for (let i = 1; i < cur.children.length; i++) {
                var ch = cur.children[i];
                ch.style.display = "block";
            }
        };
    }
}
