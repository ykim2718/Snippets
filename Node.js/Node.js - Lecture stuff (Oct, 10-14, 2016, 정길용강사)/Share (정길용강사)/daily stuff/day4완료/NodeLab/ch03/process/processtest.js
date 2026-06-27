// node.exe --harmony processtest.js hello node
console.log(process.argv);
console.log(process.execArgv);

process.on('exit', function(code){
	setTimeout(function(){
		console.log('프로세스 종료 이벤트에서 비동기 함수는 호출되지 않는다.', code);
	}, 1000);
	console.log('프로세스 종료 이벤트에서 출력.', code);
});

try{
	a();
}catch(e){
	console.error(e);
}

console.log('프로세스 종료 전.');
//process.exit(1);
console.log('프로세스 종료 후.');

//프로세스를 종료되지 않도록 한다.
//process.stdin.resume();





