var net = require('net');
var fs = require('fs');

var base = require('path').join('c:', 'node', 'workspace', 'NodeLab', 'ch03', 'net');

var server = net.createServer(function(s){
	console.log('클라이언트 접속.');
	s.on('error', function(){});
	s.on('close', function(){
		console.log('클라이언트 접속 종료.');
	});
	s.on('data', function(msg){
		var url = msg.toString().split('\n')[0].split(' ')[1];
		console.log(require('path').join(base, url));
		fs.readFile(require('path').join(base, url), function(err, data){
			if(!err){
				s.write('HTTP/1.1 200 OK\n');
				s.write('Content-Type:text/plain;charset=utf-8\n');
				s.write('\n');
				s.write(data.toString());
			}			
			s.end();
		});		
		
	});
});

server.listen(8124);







