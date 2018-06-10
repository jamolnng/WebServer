var num = 0;
var x = setInterval(function() {
	num += 1;
	document.getElementById("num").innerHTML = "Hello, World! " + num;
}, 1000);