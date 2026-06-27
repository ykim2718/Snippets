// http 코어모듈 로딩
var http = require('http');
// fs 코어모듈 로딩
var fs = require('fs');

// http 서버 생성
var server = http.createServer(function(req, res){
	// hellonode.js 파일을 읽어서 응답(비동기방식)
	fs.readFile('hellonode2.js', function(err, data){
		if(err && err.code == 'ENOENT'){
			console.error(err);
			// 응답 헤더 설정
			res.writeHead(404, {'Content-Type': 'text/html;charset=utf-8'});
			// 응답 메세지 전송
			res.write('<h1>지정한 파일을 찾을 수 없습니다.</h1>');
		}else{
			// 응답 헤더 설정
			res.writeHead(200, {'Content-Type': 'text/plain;charset=utf-8'});
			// 응답 메세지 전송
			res.write(data);
		}
		// 응답 완료 코드 전송
		res.end();
	});	
});

server.on('error', function(err){
	if(err.code == 'EADDRINUSE'){
		console.log(port, 'used.');
		server.listen(++port);
	}else{
		console.error(err);
	}
});



server.on('listening', function(){
	console.log('listening event');
	console.log('server running on http://localhost:' + port);
});

server.emit('listening');

// a || b -> a가 true이면 a, false이면 b를 취한다.
// 자바스크립트의 false 기준
// 	- boolean 타입의 false
// 	- number 타입의 0
//	- string 타입의 ''
// 	- object 타입의 null, undefined
var port = process.argv[2] || 8124;

//try{
	server.listen(port, function(){
		console.log('server running on http://localhost:' + port);
	});
//}catch(e){
//	console.error(e);
//}

/*
function listen(port, cb){
	if(cb){
		server.on('listening', cb);
	}	
	// port를 오픈한다....	
	
}
*/

	
	


