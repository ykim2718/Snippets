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
var fs = require('fs');
var connect = require('connect');

//var logger = require('./middleware/logger');
//var static = require('./middleware/static');

var logger = require('morgan');
var static = require('serve-static');
var favicon = require('serve-favicon');
var cookieParser = require('cookie-parser');
var session = require('express-session');
var ejs = require('ejs');
var routes = require('./routes/index');


var app = connect();

// favocon
app.use(favicon(path.join(__dirname, 'public', 'img', 'favicon.ico')));

// 로깅 미들웨어
//app.use(logger(path.join(__dirname, 'mylog.log')));
app.use(logger('dev'));

// 쿠키 파싱
app.use(cookieParser());

// 세션 파싱
app.use(session({
	cookie: {maxAge: 1000*60*30},	// 세션 ID를 저장할 쿠키 정보 지정
	secret: 'keyboard cat',	// 세션 ID를 만드는 키값
	rolling: true	// 모든 요청에 대해 세션 ID를 가지는 쿠키를 갱신한다.
}));



// 미들웨어 등록(요청헤더 정보 출력)
app.use(function(req, res, next){
//	console.log(req.headers);
//	console.log(req.cookies);
//	console.log(req.session);
	next();
});

// 정적인 자원 처리하는 미들웨어
app.use(static(path.join(__dirname, 'public')));

// 동적인 자원 처리하는 미들웨어
app.use('/', routes);

//app.use('/login', login);
//app.use('/logout', logout);
//app.use('/chat', loginCheck);

// 에러 처리하는 미들웨어(404)
app.use(function(req, res, next){
	var err = new Error(req.url + ' Not Found!');
	err.status = 404;
	next(err);
//	res.writeHead(404);
//	res.end(err.toString());
});

// 404 이외의 에러 처리
app.use(function(err, req, res, next){
	res.status = err.status = err.status || 500;
	ejs.renderFile(path.join(__dirname, 'views', 'error.ejs'), {
		message: err.message,
		error: err
	}, function(err, data){
		res.end(data);
	});
});

module.exports = app;

/* www로 이동
var server = http.createServer(app);
server.listen(80, function(){
	console.log('서버 구동. http://localhost');
});
*/

/* router로 이동
function login(req, res, next){
	// url.parse(url, queryString 파싱여부)
	var username = require('url').parse(req.url, true).query.username;
	console.log(username, '로그인 함.');
	
	// 세션에 대화명을 저장한다.
	req.session.nickname = username;
	
	// redirect
	res.writeHead(303, {'Location': '/chat'});
	res.end();
}
function logout(req, res, next){
	// 세션을 삭제한다.
	req.session.destroy();
	res.writeHead(303, {'Location': '/'});
	res.end();
}
function loginCheck(req, res, next){
	if(req.session.nickname){
		var filename = path.join(__dirname, 'public', 'chat.ejs');
		
//		fs.readFile(filename, function(err, data){
//			res.writeHead(200, {'Content-Type': 'text/html;charset=utf-8'});
//			res.end(data);
//		});
		
		// ejs 사용
		ejs.renderFile(filename
				, {nickname: req.session.nickname, title: '채팅창'}
				, function(err, data){ console.log(data);res.end(data); });
		
	}else{
		res.writeHead(303, {'Location': '/'});
		res.end();
	}
}
*/














