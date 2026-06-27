console.log(__filename, 'm2 로딩 전.');
var m2 = require('./m2');
console.log(__filename, 'm2 로딩 후.');

for(var name in require.cache){
	console.log('cache', name);
}

// m2 모듈 캐시에서 직접 삭제
delete require.cache[require.resolve('./m2')];
var m2 = require('./m2');







