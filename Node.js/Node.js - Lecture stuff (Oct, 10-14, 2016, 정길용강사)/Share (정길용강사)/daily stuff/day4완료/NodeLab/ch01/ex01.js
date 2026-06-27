// http 코어모듈 로딩
var http = require('http');

// http 서버 생성
http.createServer(function(req, res){
	// 응답 헤더 설정
	res.writeHead(200, {'Content-Type': 'text/html;charset=utf-8'});
	// 응답 메세지 전송
	res.write('<h1>Hello Node WebServer2</h1>');
	res.write('<p>첫번째 웹서버 예제입니다.</p>');
	// 응답 완료 코드 전송
	res.end();
}).listen(8124, function(err, result){
	if(err){
		console.error(err);
	}else{
		console.log('Server running on http://localhost:8124');
	}
});