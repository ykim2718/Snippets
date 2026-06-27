var assert = require('assert');

var a = 10;
assert(a == 10);  // True
assert(a == '10');  // True
assert.equal(a, 10);
assert(a++ == 10);
assert.equal(a, 11);

setTimeout(function(){
	assert(a == 12);
}, 1000);

console.log('test done');