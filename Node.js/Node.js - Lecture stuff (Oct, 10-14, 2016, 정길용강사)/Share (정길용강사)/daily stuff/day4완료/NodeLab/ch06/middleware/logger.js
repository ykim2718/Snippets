var url = require('url');
var path = require('path');
var fs = require('fs');

function mylogger(filename){
	// 로깅 파일
	var logger = fs.createWriteStream(filename, {flags: 'a'});

	return function(req, res, next){
		var parseUrl = url.parse(req.url);
		var filepath = path.join(path.join(process.cwd(), 'public'), parseUrl.pathname);
		
		fs.stat(filepath, function(err, stats){
			var statusCode = 200;
			if(err){
				statusCode = 404;
			}else if(stats.isFile()){
				statusCode = 200;
			}else{
				statusCode = 403;
			}		
			//로깅(파일시스템에 기록)
			logger.write(Date() + ' ' + statusCode + ' ' + parseUrl.pathname + '\n');
			next();
		});
	};
}

module.exports = mylogger;