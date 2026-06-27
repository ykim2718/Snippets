var Browser = require('zombie');
var assert = require('assert');

Browser.localhost('localhost', 80);

describe('메인 페이지 접속', function(){
	var browser = new Browser();
	before(function(){
		return browser.visit('/');
	});
	it('메인 페이지 접속 성공', function(){
		// ststus 코드가 2XX, 3XX 인가?
		browser.assert.success();
	});
});
describe('등록', function(){
	var browser = new Browser();
	before(function(done){
		return browser.visit('/board/new', done);
	});
	it('등록 화면 요청', function(){
		assert.equal(browser.location.pathname, '/board/new');
	});
	it('등록', function(done){
		browser.fill('title', '좀비로 등록함.').fill('writer', '좀비');
		browser.pressButton('submit', done);
	});
});







