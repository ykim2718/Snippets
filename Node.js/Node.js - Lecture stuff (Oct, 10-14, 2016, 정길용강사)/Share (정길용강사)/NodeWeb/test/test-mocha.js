var assert = require('assert');

// test suite
describe('#suite 동기 방식 테스트', function(){
	// unit test
	it('#1 hello == hello', function(){
		assert.equal('hello', 'hello');
	});
	it('#2 10 === "10"', function(){
		assert(10 === "10")
	});
	it('#3 10 == "10"', function(){
		assert(10 == "10")
	});
});
//describe('#suite 비동기 방식 테스트', function(){
describe.skip('#suite 비동기 방식 테스트', function(){
	it('#1 1==1', function(done){
		setTimeout(function(){
			assert(1 == 1);
			done();
		}, 1000);
	});
	it('#2 1==2', function(){
		assert(1 == 2);
	});
});

//describe.only('#suite 다른 suite 제외', function(){
describe('#suite 다른 suite 제외', function(){
	it('#1 1==1', function(){
		assert(1 == 1);
	});
});

describe('#suite timeout 지정, 300ms', function(){
	this.timeout(300);
	it('#1 100ms', function(done){
		this.timeout(50);
		setTimeout(done, 100);
	});
	it('#2 350ms', function(done){
		setTimeout(done, 350);
	});
	it('#3 100ms', function(done){
		setTimeout(done, 100);
	});
});








