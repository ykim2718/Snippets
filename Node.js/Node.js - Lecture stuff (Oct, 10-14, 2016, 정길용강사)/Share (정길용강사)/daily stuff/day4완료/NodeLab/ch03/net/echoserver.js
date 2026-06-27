require('net').createServer(function(s){
	// error 이벤트를 등록하지 않으면 예외가 처리되지 않음
	s.on('error', function(){});
	s.pipe(s);
}).listen(8124);