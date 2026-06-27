var EventEmitter = require('events');
var event = new EventEmitter();

// 이벤트 등록
event.on('timed', function(data){
	console.log('on timed 이벤트 발생.', data);
});
event.once('timed', function(data){
	console.log('once timed 이벤트 발생.', data);
});
event.addListener('timed', function(data){
	console.log('addListener timed 이벤트 발생.', data);
});

// 이벤트 발생
var count = 0;
event.emit('timed', ++count);
event.emit('timed', ++count);





