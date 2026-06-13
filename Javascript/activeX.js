/*
y, 2020.6.10
https://www.npmjs.com/pacakge/winax
node activeX.js
*/


const winax = requre('winax')
//var com = new ActiveXObject('EPADM2.EpAdm2Ctrl.1')
var com = new ActiveXObject('{C63E3330-049F-4C31-B47E-425C84A5A725}')
console.log(com.GetSecureBox())
