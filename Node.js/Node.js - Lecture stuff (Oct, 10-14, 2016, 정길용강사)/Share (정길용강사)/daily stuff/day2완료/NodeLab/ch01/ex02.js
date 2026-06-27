// http 코어모듈 로딩
var http = require('http');
// fs 코어모듈 로딩
var fs = require('fs');

// http 서버 생성
http.createServer(function(req, res){
	/*
	// hellonode.js 파일을 읽어서 응답(동기방식)
	var data = fs.readFileSync('hellonode.js');	
	// 응답 헤더 설정
	res.writeHead(200, {'Content-Type': 'text/html;charset=utf-8'});
	// 응답 메세지 전송
	res.write(data);
	// 응답 완료 코드 전송
	res.end();
	*/
	
	// hellonode.js 파일을 읽어서 응답(비동기방식)
	fs.readFile('hellonode.js', function(err, data){
		if(err){
			console.error(err);
		}else{
			// 응답 헤더 설정
			res.writeHead(200, {'Content-Type': 'text/plain;charset=utf-8'});
			// 응답 메세지 전송
			res.write(data);
		}
		// 응답 완료 코드 전송
		res.end();
	});	
}).listen(8124, function(err, result){
	if(err){
		console.error(err);
	}else{
		console.log('Server running on http://localhost:8124');
	}
});


