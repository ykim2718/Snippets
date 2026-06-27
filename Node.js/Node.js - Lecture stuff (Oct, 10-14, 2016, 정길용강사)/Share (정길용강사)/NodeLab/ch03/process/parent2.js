var childProcess = require('child_process');


//var child = childProcess.spawn('node', ['child1.js', 'child', 'process']);
// 노드 프로세스를 생성
var child = childProcess.fork('child2.js', ['child', 'process']);

child.on('message', function(msg){
	console.log(__filename, msg);
});
child.send('from parent');

//process.stdin.resume();