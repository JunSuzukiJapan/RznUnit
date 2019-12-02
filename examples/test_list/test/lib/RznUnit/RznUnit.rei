type test_fun = unit => unit;

type test = 
  | TestCase(test_fun)
  | TestList(list(test))
  | TestLabel(string, test)
;

let run_test : (~msg: string=?, test) => unit;

let (@>)   : string => test_fun => test;
let (@@>)  : string => list(test) => test;

let (>@>)  : string => test => unit;
let (>@@>) : string => list(test) => unit;

/*
 * MakeAssert
 */
module type Assertable = {
    type t;
    let format: t => string;
    let equal: t => t => bool;
};

module MakeAssert : (Item: Assertable) => {
    type t;
    let equal : t => t => unit;
    let equal_list : list(t) => list(t) => unit;
    let equal_array : array(t) => array(t) => unit;
};

/*
 * Assert
 */
module Assert : {
    let raises : exn => test_fun => unit;    
}

/*
 * BoolAssert
 */
module BoolAssert : {
    let is_true : bool => unit;
    let is_false : bool => unit;
    let equal : bool => bool => unit;
    let equal_list : list(bool) => list(bool) => unit;
    let equal_array : array(bool) => array(bool) => unit;    
}

/*
 * IntAssert
 */
module IntAssert : {
    let equal : int => int => unit;
    let equal_list : list(int) => list(int) => unit;
    let equal_array : array(int) => array(int) => unit;
};

/*
 * FloatAssert
 */
module FloatAssert : {
    let equal : float => float => unit;
    let equal_list : list(float) => list(float) => unit;
    let equal_array : array(float) => array(float) => unit;
};

/*
 * StringAssert
 */
module StringAssert : {
    let equal : string => string => unit;
    let equal_list : list(string) => list(string) => unit;
    let equal_array : array(string) => array(string) => unit;
};

/*
 * CharAssert
 */
module CharAssert : {
    let equal : char => char => unit;
    let equal_list : list(char) => list(char) => unit;
    let equal_array : array(char) => array(char) => unit;
};