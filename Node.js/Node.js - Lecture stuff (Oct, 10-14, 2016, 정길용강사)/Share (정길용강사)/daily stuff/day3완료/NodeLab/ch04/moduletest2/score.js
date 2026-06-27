// 점수의 합계를 구하는 함수
// 생성자 함수(var kim = new Score(100, 90))
// kim.sum();
// kim.eng
function Score(kor, eng){
//	this = new Object();
	this.kor = kor;
	this.eng = eng;
//	return this;
}
Score.prototype.sum = function(){
	return this.kor + this.eng;
};

module.exports = Score;