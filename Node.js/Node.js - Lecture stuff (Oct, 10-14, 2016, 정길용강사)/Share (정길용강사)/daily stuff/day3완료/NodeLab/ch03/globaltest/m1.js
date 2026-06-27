a = 10;				// 전역변수
global.b = 20;// 전역변수
var c = 30;		// 모듈변수

function d(){
	var c = 100;// 지역변수
	console.log(a, b, c);
	console.log(global.a, global.b, global.c);
}
d();
