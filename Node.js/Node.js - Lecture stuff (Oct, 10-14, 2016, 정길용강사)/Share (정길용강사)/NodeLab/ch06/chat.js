function chat(io){
	console.log('socket.io server start.');
	io.on('connection', function(s){
		console.log('클라이언트 접속', s.client.conn.remoteAddress);
		s.on('login', function(nickname){
			s.nickname = nickname;
			io.emit('chat', '시스템: ' + nickname + ' 님이 입장했습니다.');
		});
		s.on('chat', function(msg){
			if(msg.trim() === ''){
				s.emit('chat', '시스템: 메세지를 입력하세요.');
			}else{
				io.emit('chat', s.nickname + ': ' + msg);
			}
		});
		s.on('disconnect', function(){
			io.emit('chat', '시스템: ' + s.nickname + '님이 퇴장했습니다.');
		});
	});
}

module.exports = chat;