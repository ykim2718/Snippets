// 게시물 목록 조회
module.exports.list = function(req, res){
	res.render('board/list', {title: '게시물 목록'});
};

// 게시물 상세 조회
module.exports.show = function(req, res){
	var no = req.params.no;
	console.log(no);
	res.render('board/view', {title: '내용 조회'});
};

// 게시물 등록 폼 출력
module.exports.form = function(req, res){
	res.render('board/write', {title: '글쓰기'});
};

// 게시물 등록
module.exports.create = function(req, res){
	var data = req.body;
	console.log(data);
	res.render('board/result', {title: '작성 결과'});
};

// 게시물 삭제
module.exports.remove = function(req, res){
	var no = req.params.no;
	console.log(no);
	res.redirect('/board/');
};











