//
// RznUnit
//
// Copyright (C) 2019 Jun Suzuki.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software
// and associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom
// the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//


/*
 * Types
 */
type test_fun = unit => unit;

type test = 
  | TestCase(test_fun)
  | TestList(list(test))
  | TestLabel(string, test)
;

/*
 * Exceptions
 */
exception NotEqual(string, string);
exception UnmatchListLength;
exception NotEqualList(string, string, int);
exception UnmatchArrayLength;
exception NotEqualArray(string, string, int);
exception NotTrue;
exception NotFalse;

/*
 * Context
 */
type context = {
  mutable failure_count: int,
  mutable tested_count: int,
};

/*
 * run_test
 */
let rec run_test_main(~catch_exn: bool, test: test, ctxt: context) = {
  switch test {
  | TestCase(f) => {
      ctxt.tested_count = ctxt.tested_count + 1;

      if(catch_exn){
        try (f()) {
          | NotEqual(actual, expected) => {
              ctxt.failure_count = ctxt.failure_count + 1;
              Printf.printf("  Failure:\n");
              Printf.printf("    actual:   %s\n", actual);
              Printf.printf("    expected: %s\n", expected);
            }
          | NotEqualList(actual, expected, nth) => {
              ctxt.failure_count = ctxt.failure_count + 1;
              Printf.printf("  Failure: in list. index = %d\n", nth);
              Printf.printf("    actual:   %s\n", actual);
              Printf.printf("    expected: %s\n", expected);
            }
          | UnmatchListLength => {
              ctxt.failure_count = ctxt.failure_count + 1;
              print_endline("  Failure: unmatch list length.");
            }
          | NotEqualArray(actual, expected, nth) => {
              ctxt.failure_count = ctxt.failure_count + 1;
              Printf.printf("  Failure: in array. index = %d\n", nth);
              Printf.printf("    actual:   %s\n", actual);
              Printf.printf("    expected: %s\n", expected);
            }
          | UnmatchArrayLength => {
              ctxt.failure_count = ctxt.failure_count + 1;
              print_endline("  Failure: unmatch array length.");
            }
          | NotTrue => {
              ctxt.failure_count = ctxt.failure_count + 1;
              print_endline("  Failure: not true");
            }
          | NotFalse => {
              ctxt.failure_count = ctxt.failure_count + 1;
              print_endline("  Failure: not false");
            }
          | _ => {
              ctxt.failure_count = ctxt.failure_count + 1;
              print_endline("  Failure:");
              print_endline("    - exception raised.")
            }
        };
      }else{
        f();
      }

    }

  | TestList(test_list) => List.iter((test) => run_test_main(~catch_exn = true, test, ctxt), test_list)

  | TestLabel(msg, TestList(test_list)) => {
      Printf.printf("Tests: %s\n", msg);
      run_test_main(~catch_exn = true, TestList(test_list), ctxt);
      Printf.printf("done: %s\n", msg);
    }
  | TestLabel(msg, test) => try (run_test_main(~catch_exn = false, test, ctxt)) {
    | NotEqual(actual, expected) => {
        ctxt.failure_count = ctxt.failure_count + 1;
        Printf.printf("  Failure: %s\n", msg);
        Printf.printf("    actual:   %s\n", actual);
        Printf.printf("    expected: %s\n", expected);
      }
    | NotEqualList(actual, expected, nth) => {
        ctxt.failure_count = ctxt.failure_count + 1;
        Printf.printf("  Failure: %s. list index = %d\n", msg, nth);
        Printf.printf("    actual:   %s\n", actual);
        Printf.printf("    expected: %s\n", expected);
      }
    | UnmatchListLength => {
        ctxt.failure_count = ctxt.failure_count + 1;
        Printf.printf("  Failure: %s\n", msg);
        print_endline ("    unmatch list length.");
      }
    | NotEqualArray(actual, expected, nth) => {
        ctxt.failure_count = ctxt.failure_count + 1;
        Printf.printf("  Failure: %s. array index = %d\n", msg, nth);
        Printf.printf("    actual:   %s\n", actual);
        Printf.printf("    expected: %s\n", expected);
      }
    | UnmatchArrayLength => {
        ctxt.failure_count = ctxt.failure_count + 1;
        Printf.printf("  Failure: %s\n", msg);
        print_endline ("    unmatch array length.");
      }
    | NotTrue => {
        ctxt.failure_count = ctxt.failure_count + 1;
        Printf.printf("  Failure: %s\n", msg);
        print_endline("    not true");
      }
    | NotFalse => {
        ctxt.failure_count = ctxt.failure_count + 1;
        Printf.printf("  Failure: %s\n", msg);
        print_endline("    not false");
      }
    | _ => {
        ctxt.failure_count = ctxt.failure_count + 1;
        Printf.printf("  Failure: %s", msg);
        print_string( "    - exception raised.")
      }
    };
  };
};

let run_test(~msg=?, test: test) = {
  switch msg {
  | Some(s) => Printf.printf("Testing: '%s'\n", s)
  | None => ()
  };

  let ctxt = {
    failure_count: 0,
    tested_count: 0,
  };

  let start_time = Sys.time();
  run_test_main(~catch_exn = true, test, ctxt);
  let end_time = Sys.time();
  let span = end_time -. start_time;

  switch msg {
  | Some(s) => Printf.printf("Finished: '%s' in %f seconds.\n", s, span)
  | None => Printf.printf("Finished in %f seconds.\n", span)
  };

  Printf.printf("%d examples, %d failures.\n\n", ctxt.tested_count, ctxt.failure_count);
};

let (>@) (s, f)   = TestLabel(s, TestCase(f))  // infix
let (>@@) (s, l)  = TestLabel(s, TestList(l))  // infix

let (>@>) (s, t)   = run_test(~msg = s, t)           // infix
let (>@@>) (s, l) = run_test(~msg = s, TestList(l))  // infix

/*
 * MakeAssert
 */
module type Assertable = {
  type t;
  let format: t => string;
  let equal: t => t => bool;
};

module MakeAssert = (Item: Assertable) => {
  type t = Item.t;

  let equal(x: t, y: t) = {
    if (Item.equal(x, y)){
      ();
    }else{
      let actual = Item.format(x);
      let expected = Item.format(y);
      raise(NotEqual(actual, expected));
    }
  };

  let rec equal_list_sub(left: list(t), right: list(t), nth: int) = {
    switch (left, right) {
    | ([], []) => ()
    | ([], [_, ..._]) => raise(UnmatchListLength)
    | ([_, ..._], []) => raise(UnmatchListLength)
    | ([x, ...xs], [y, ...ys]) => {
        try (equal(x, y)) {
        | NotEqual(l, r) => raise (NotEqualList(l, r, nth))
        | e => raise(e)
        };
        equal_list_sub(xs, ys, nth + 1);
      }
    };
  };

  let equal_list(left: list(t), right: list(t)) = {
    equal_list_sub(left, right, 0);
  };

  let equal_array(left: array(t), right: array(t)) = {
    let len = Array.length(left);
    if(len != Array.length(right)){
      raise(UnmatchArrayLength);
    }

    for(i in 0 to len - 1){
      try( equal(left[i], right[i])){
      | NotEqual(l, r) => raise(NotEqualArray(l, r, i))
      | e => raise(e)
      }
    }
  };
}

/*
 * BoolAssert
 */
module AssertableBool = {
  type t = bool;

  let format = (p) => switch p {
  | true => "true"
  | false => "false"
  };

  let equal(x, y) = x == y;
}

module BoolAssertSub = MakeAssert(AssertableBool);

module BoolAssert = {
  include BoolAssertSub;

  let is_true(p) = {
    switch p {
    | true => ()
    | false => raise(NotTrue)
    };
  };

  let is_false(p) = {
    switch p {
    | true => raise(NotFalse)
    | false => ()
    };
  };
}

/*
 * IntAssert
 */
module AssertableInt = {
  type t = int;
  let format = string_of_int;
  let equal(x, y) = x == y;
};

module IntAssert = MakeAssert(AssertableInt);

/*
 * FloatAssert
 */
module AssertableFloat = {
  type t = float;
  let format = string_of_float;
  let equal(x, y) = x == y;
};

module FloatAssert = MakeAssert(AssertableFloat);

/*
 * StringAssert
 */
module AssertableString = {
  type t = string;
  let format = (s) => "\"" ++ s ++ "\"";
  let equal(x, y) = x == y;
};

module StringAssert = MakeAssert(AssertableString);

/*
 * CharAssert
 */
module AssertableChar = {
  type t = char;
  let format(c) = "'" ++ Char.escaped(c) ++ "'";
  let equal(x, y) = x == y;
};

module CharAssert = MakeAssert(AssertableChar);
