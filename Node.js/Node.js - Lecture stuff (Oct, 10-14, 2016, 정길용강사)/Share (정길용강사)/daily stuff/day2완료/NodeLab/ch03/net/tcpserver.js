var tcp = require('net');

var server = tcp.createServer(function(s){
	console.log('서버로그: 클라이언트 접속.', s.remoteAddress, s.remotePort);
	s.on('error', function(err){
		console.error(err);
	});
	s.on('close', function(){
		console.log('서버로그: 클라이언트 접속 종료.');
	});
	s.on('data', function(msg){
//		console.log(msg.toString());
		s.write(msg);
	});
});

// 포트가 정상적으로 오픈될 경우
server.on('listening', function(){
	console.log('listening on port 8124');
});

// 포트 오픈에 실패할 경우
server.on('error', function(e){
	console.error(e);
});

server.listen(8124);