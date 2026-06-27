var path = require('path');
var ejs = require('ejs');

var router = function(req, res, next){
	var pathname = require('url').parse(req.url).pathname;
	switch(pathname){
	case '/login':
		login(req, res, next);
		break;
	case '/logout':
		logout(req, res, next);
		break;
	case '/chat':
		loginCheck(req, res, next);
		break;
	default :
		next();
	}
};

function login(req, res, next){
	var username = require('url').parse(req.url, true).query.username;
	req.session.nickname = username;
	res.writeHead(303, {'Location': '/chat'});
	res.end();
}
function logout(req, res, next){
	req.session.destroy();
	res.writeHead(303, {'Location': '/'});
	res.end();
}
function loginCheck(req, res, next){
	if(req.session.nickname){
		var filename = path.join(__dirname, '../', 'views', 'chat.ejs');
		ejs.renderFile(filename
				, {nickname: req.session.nickname, title: '채팅창'}
				, function(err, data){ console.log(data);res.end(data); });
	}else{
		res.writeHead(303, {'Location': '/'});
		res.end();
	}
}

module.exports = router;





