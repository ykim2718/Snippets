var assert = require('assert');

var a = 10;
assert(a == 10);
assert(a == '10');
assert.equal(a, 10);
assert(a++ == 10);
assert.equal(a, 11);



setTimeout(function(){
	assert(a == 12);
	console.log('테스트 통과.');
}, 1000);

setTimeout(function(){
	assert(a == 12);
	console.log('테스트 통과.');
}, 1000);


