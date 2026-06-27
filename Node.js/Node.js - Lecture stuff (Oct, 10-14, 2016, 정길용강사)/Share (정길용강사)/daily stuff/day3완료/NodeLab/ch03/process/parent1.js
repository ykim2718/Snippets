var childProcess = require('child_process');

// 지정한 프로세스를 실행
//childProcess.spawn('notepad');
//childProcess.spawn('calc');

var out = require('fs').openSync('./log.txt', 'a');

var child = childProcess.spawn('node', ['child1.js', 'child', 'process'], {
//	stdio: 'pipe'	// 자식 프로세스의 표준 입출력 장치를 부모와 pipe 연결(기본값)
//	stdio: 'inherit'	// 부모 프로세스의 표준 입출력 장치 사용
//	stdio: 'ignore'	// 자식 프로세스의 표준 입출력 장치를 사용안함
	stdio: ['inherit', out, 'ignore']
});

/*
child.stdout.on('data', function(msg){
	console.log(msg.toString());
});
*/

child.on('close', function(code){
	console.log('자식 프로세스 종료.', code);
});











