var img_container = document.querySelector(".img_list_container");
let cur = -1600;
var larrow = document.querySelector(".left_arrow");
var rarrow = document.querySelector(".right_arrow");
larrow.addEventListener("click", () => {
    cur -= 400;
    img_container.style.left = cur + "px";
})
rarrow.addEventListener("click", () => {
    cur += 400;
    img_container.style.left = cur + "px";
})

var nav_item_list = document.querySelectorAll(".nav_item");//上方导航栏
// alert(nav_item_list.length);
var underline = document.querySelector(".nav_underline_container");
var nav_list_item = document.querySelectorAll(".nav_list_item");//下方展示元素
nav_list_item[0].style.left = "0";
for (let i = 1; i < nav_item_list.length; i++)
    nav_list_item[i].style.left = "100%";
for (let i = 0; i < nav_item_list.length; i++) {
    let item = nav_item_list[i];
    item.addEventListener("mouseenter", () => {
        underline.style.left = 10 * (i + 1) + "%";
        nav_list_item[i].style.left = "0";
        for (let j = 0; j < i; j++)
            nav_list_item[j].style.left = "-100%";
        for (let j = i + 1; j < nav_item_list.length; j++)
            nav_list_item[j].style.left = "100%";
    });
}

