function CalcC() {
    var N = document.getElementById("Cup").value, M = document.getElementById("Cdown").value;
    var up = 1, down = 1;
    for (var i = 1; i <= N; i++) up *= i;
    for (var i = 1; i <= M; i++) down *= i;
    for (var i = 1; i <= N - M; i++) down *= i;
    document.getElementById("Cres").value = up / down;
}
function ClearC() {
    document.getElementById("Cres").value = "";
    document.getElementById("Cup").value = "";
    var N = document.getElementById("Cdown");
    N.value = "";
}
function CalcA() {
    var N = document.getElementById("Aup").value, M = document.getElementById("Adown").value;
    var up = 1, down = 1;
    for (var i = 1; i <= N; i++) up *= i;
    for (var i = 1; i <= N - M; i++) down *= i;
    document.getElementById("Ares").value = up / down;
}
function ClearA() {
    document.getElementById("Ares").value = "";
    document.getElementById("Aup").value = "";
    var N = document.getElementById("Adown");
    N.value = "";
}
var x, y;
function exgcd(a, b) {
    if (b == 0) { x = 1; y = 0; return a; }
    var r = exgcd(b, a % b), tmp;
    tmp = x; 
    x = y; 
    y = parseInt(tmp - parseInt(parseInt((a / b)) * y));//woc js语言向下取个整怎么这么麻烦。。
    return r;
}
function gcd(a, b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}
function CalcInv() {
    x = 0; y = 0;
    var A = parseInt(document.getElementById("InvUp").value), P = parseInt(document.getElementById("InvDown").value);
    var g = gcd(A, P), pos = document.getElementById("InvRes");
    if (g != 1)
        pos.value = "attack太菜了找不到逆元呢qwq";
    else {
        var ans = exgcd(A, P, x, y);
        if (x < 0) x = x + P;
        pos.value = x;
    }
}
function ClearInv() {
    document.getElementById("InvRes").value = "";
    document.getElementById("InvUp").value = "";
    var N = document.getElementById("InvDown");
    N.value = "";
}
function NumberAnalysis() {
    var N = parseInt(document.getElementById("NumberInput").value);
    var ApproxPos = document.getElementById("NumberApprox"), PrimePos = document.getElementById("NumberPrime");
    var approx = new Array(), prime = new Array();
    for(var i = 1; i * i <= N; i++) {
        if(N % i == 0) {
            approx.push(i);
            if(N / i != i) approx.push(N / i);
        }
    }
    var P = N, mu = 1, phi = 1;
    for(var i = 2; i * i <= P; i++) {
        if(P % i == 0) {
            prime.push(i); var times = 1, now = i - 1; P /= i;
            while(P % i == 0) P /= i, times++, now *= i;
            if(times > 1) mu = 0;
            else mu = -mu;
            phi *= now;
        }
    }
    if(P != 1) prime.push(P), phi *= (P - 1), mu = -mu;
    prime.sort(function(a, b){return a - b});
    approx.sort(function(a, b){return a - b});

    ApproxPos.value = "";
    PrimePos.value = "";
    document.getElementById("NumberApproxNum").innerHTML = "约数有：";
    document.getElementById("NumberPrimeNum").innerHTML = "质因数有：";
    document.getElementById("NumberMu").innerHTML = "莫比乌斯函数为：";
    document.getElementById("NumberPhi").innerHTML = "欧拉函数为：";    

    document.getElementById("NumberApproxNum").innerHTML += approx.length + " 个";
    document.getElementById("NumberPrimeNum").innerHTML += prime.length + " 个";
    document.getElementById("NumberMu").innerHTML += " " + mu;
    document.getElementById("NumberPhi").innerHTML += " " + phi;
    ApproxPos.value = approx;
    PrimePos.value = prime;

}