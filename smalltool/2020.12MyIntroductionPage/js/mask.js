function DisplayMask1() {
  document.getElementsByClassName("loading_container")[0].style.opacity = "0";
  // var mask = document.getElementsByClassName("loading_container")[0].style.display = "none";
}
function DisplayMask2() {
  document.getElementsByClassName("loading_container")[0].style.display =
    "none";
}
setTimeout("DisplayMask1()", 1000);
setTimeout("DisplayMask2()", 1500);
