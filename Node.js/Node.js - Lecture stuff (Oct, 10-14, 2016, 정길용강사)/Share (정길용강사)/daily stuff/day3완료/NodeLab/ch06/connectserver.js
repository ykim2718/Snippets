// 웹 서버 개발시 해야할 작업들...
// 1. 로깅
// 2. DB 핸들링
// 3. 보안(사용자 인증)
// 4. URL 인코딩
// 5. 쿠키 처리
// 6. 세션 처리(로그인 상태 유지)
// 7. 파일 업로드
// 8. 정적인 자원과 동적인 자원 분리
// 9. POST 방식의 바디 파싱
// 10. favicon 처리
// ......

/*
 * http 모듈은 위의 기능을 제공하지 않음.
 * 개발자가 위의 기능들을 직접 다 구현해야 함.
 * 확장 모듈을 이용하자!!!
 * connect@2가 위의 작업을 대신 해주는 미들웨어
 * connect@3는 미들웨어는 포함하지 않고 미들웨어를 중계해주는 역할의 
 * 미들웨어 프레임워크로 바뀜
*/

var http = require('http');
var path = require('path');
var connect = require('connect');
var logger = require('./middleware/logger');
var static = require('./middleware/static');

var app = connect();

// 미들웨어 등록(요청헤더 정보 출력)
app.use(function(req, res, next){
	console.log(req.headers);
	console.log(req.cookies);
	console.log(req.session);
	next();
});

// 로깅 미들웨어
app.use(logger(path.join(__dirname, 'mylog.log')));

// 정적인 자원 처리하는 미들웨어
app.use(static(path.join(__dirname, 'public')));

// 동적인 자원 처리하는 미들웨어


// 에러 처리하는 미들웨어
app.use(function(req, res, next){
	var err = new Error(req.url + ' Not Found!');
	err.status = 404;
	res.writeHead(404);
	res.end(err.toString());
});

var server = http.createServer(app);
server.listen(80, function(){
	console.log('서버 구동. http://localhost');
});



















