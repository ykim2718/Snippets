console.log('1. start');

var immediate = setImmediate(function(){
	console.log('5. setImmediate()');
});

var timer = setTimeout(function(){
	console.log('4. setTimeout()');
}, 0);

process.nextTick(function(){
	console.log('3. nextTick()');
});

var start = process.hrtime();
var interval = setInterval(function(){
	var gap = process.hrtime(start);
	console.log(gap);
	if(gap[0] >= 5){
		clearInterval(interval);
	}
	for(var i=0; i<100000000; i++){}
}, 1000);

console.log('2. finish');








