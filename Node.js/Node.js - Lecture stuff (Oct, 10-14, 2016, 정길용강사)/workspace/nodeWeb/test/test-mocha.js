var assert = require('assert');

// test suite
describe('# suite test sync-way', function(){ 
	// unit test
	it('#1 hello == hello', function(){
		assert.equal('hello', 'hello');
	});
	it('#2 10 === "10"', function(){
		assert(10 === '10');
	});
	it('#3 10 == "10"', function(){
		assert(10 == '10');
	});
});

//describe('# suite test async-way', function(){
describe.skip('# suite test async-way', function(){
	it('# 1 == 1', function(done){
		setTimeout(function(){
			assert(1==1);
			done();  // call next 
		}, 1000);
	});
	it('# 1 == 2', function(done){
		assert(1==2);
	});
});

//describe.only('# sute 다른 suite 제외하고 나만 test 할 때'), function(){
describe('# sute 다른 suite 제외하고 나만 test 할 때', function(){
	it('#1 1==1', function(){
		assert(1==1);
	});
});

describe('#suite timeout limited, 300ms', function(){
	this.timeout(300);
	it('#1 100ms', function(done){
		this.timeout(50);
		setTimeout(done, 100);
	});
	it('#2 150ms', function(done){
		setTimeout(done, 150);
	});
	it('#3 350ms', function(done){
		setTimeout(done, 350);
	});
})




