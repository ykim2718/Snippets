var express = require('express');
var router = express.Router();
var board = require('../controllers/board');

/* GET home page. */
router.get('/', function(req, res, next) {
  res.redirect('/board/');
});

router.get('/board', function(req, res, next) {
  board.list(req, res);
});
router.get('/board/new', function(req, res, next) {
  board.form(req, res);
});
router.post('/board/new', function(req, res, next) {
  board.create(req, res);
});
router.get('/board/:no', function(req, res, next) {
  board.show(req, res);
});
router.delete('/board/:no', function(req, res, next) {
  board.remove(req, res);
});



module.exports = router;
