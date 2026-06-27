var tcp = require('net');

var s = new tcp.Socket();

s.connect('8124', '70.12.113.190', function(){
	console.log('클라이언트 로그: 서버에 접속함.');
//s.write('hello');
	
	s.on('data', function(msg){
		console.log(msg.toString());
	});
	
	// 표준 입력장치의 입력 스트림을 재개한다.
	process.stdin.resume();
	process.stdin.on('data', function(msg){
		if(msg.toString().trim() == 'exit') process.exit();
		s.write(msg);
	});
});