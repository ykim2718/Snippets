var board = require('../models/board');
//var board = require('../models/board_mysql');

// 게시물 목록 조회
module.exports.list = function(req, res){
	board.list(function(result){
		res.render('board/list', {title: '게시물 목록', list: result});
	});
};

// 게시물 상세 조회
module.exports.show = function(req, res){
	var no = req.params.no;
	console.log(no);
	board.show(no, function(result){
		res.render('board/view', {title: '내용 조회', board: result});
	});
};

// 게시물 등록 폼 출력
module.exports.form = function(req, res){
	res.render('board/write', {title: '글쓰기'});
};

// 게시물 등록
module.exports.create = function(req, res){
	var data = req.body;
	console.log(data);
	board.create(data, function(result){
		res.render('board/result', {title: '작성 결과', no: result});
	});	
};

// 게시물 삭제
module.exports.remove = function(req, res){
	var no = req.params.no;
	console.log(no);
	board.remove(no, function(){
		res.redirect('/board/');
	});	
};











