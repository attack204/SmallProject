var a = document.getElementsByClassName("password_icon")[0].children[0];
var input = a.parentElement.previousElementSibling;
a.addEventListener("click", () => {
    if (a.getAttribute("class").includes("fa fa-eye-slash") == true) {
        a.setAttribute("class", "fa fa-eye");
        input.setAttribute("type", "text");
    } else {
        a.setAttribute("class", "fa fa-eye-slash")
        input.setAttribute("type", "password");
    }
})
