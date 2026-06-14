/*/////////////////////////////////////////////////////////////////////////////////////////////////

yJsStandard.js
y, 2019.5.23, 5.29

/////////////////////////////////////////////////////////////////////////////////////////////////*/

const version = '0.0.2019.5.29'

const check = require('check-types')

///////////////////////////////////////////////////////////////////////////////////////////////////

function type_of(x) {
    /*
    sunho, 2019.2.1
    y, 2019.5.23
    */
   if (typeof x == 'object') {
       if (check.object(x)) return 'object'
       else if (check.array(x)) return 'array'
       else if (check.date(x)) return 'date'
       else new Error(`Unknown type of ${x}`)
   } else {
       if (typeof x == 'number')
            if (check.integer(x)) return 'int'
            else return 'float'
       else
            return typeof x
   }
}

function instance_of(x, any_type) {
    /*
    y, 2019.5.23
    */
   return check.instance(x, any_type)
}

///////////////////////////////////////////////////////////////////////////////////////////////////

if (typeof module != 'undefined' && !module.parent) {
    console.log(type_of(3), type_of(3.0))  // number >> int
    console.log(type_of(3.1))  // number >> float
    console.log(type_of(NaN), type_of(Infinity))  // number >> float
    console.log(type_of(''))  // string
    console.log(type_of(true))  // boolean
    console.log(type_of(null))  // undefined
    console.log(type_of(undefined))  // undefined
    console.log(type_of([]))  // array
    console.log(type_of({}))  // object
    console.log(type_of(Symbol()))  // symbol
    console.log(type_of(function () {}))  // function
    console.log(type_of(class Glass {}))  // function
    console.log(type_of(new Date()))  // date
} else {
    module.exports = {
        version,
        type_of,
        instance_of
    }
}