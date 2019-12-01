# RznUnit

UnitTest framework for ReasonML written in PURE Reason.

# Install

copy ```lib/RznUnit/RznUnit.rei``` and ```lib/RznUnit/RznUnit.re``` to your project.

# Example

test/test_example.re

```
let () = {
    open RznUnit;

    "Test Description" >@@> [
        // Bool
        "test true" >@ () => BoolAssert.is_true(true),
        "test false" >@ () => BoolAssert.is_false(false),
        "compare true with true" >@ () => BoolAssert.equal(true, true),
        "compare list(bool)" >@ () => BoolAssert.equal_list([true, false], [true, false]),
        "compare array(bool)" >@ () => BoolAssert.equal_array([| true, false |], [| true, false |]),

        // Int
        "compare 1 with 1" >@ () => IntAssert.equal(1, 1),
        "compare list(int)" >@ () => IntAssert.equal_list([1, 2, 3, 4, 5], [1, 2, 3, 4, 5]),
        "compare array(int)" >@ () => IntAssert.equal_array([| 1, 2, 3, 4, 5 |], [| 1, 2, 3, 4, 5 |]),

        // Float
        "compare 1.0 with 1.0" >@ () => FloatAssert.equal(1.0, 1.0),
        "compare list(float)" >@ () => FloatAssert.equal_list([1.0, 2.0, 3.0, 4.0, 5.0], [1.0, 2.0, 3.0, 4.0, 5.0]),
        "compare array(float)" >@ () => FloatAssert.equal_array([| 1.0, 2.0, 3.0, 4.0, 5.0 |], [| 1.0, 2.0, 3.0, 4.0, 5.0 |]),

        // Char
        "compare 'a' with 'a'" >@ () => CharAssert.equal('a', 'a'),
        "compare list(char)" >@ () => CharAssert.equal_list(['a', 'b', 'c'], ['a', 'b', 'c']),
        "compare array(char)" >@ () => CharAssert.equal_array([| 'a', 'b', 'c' |], [| 'a', 'b', 'c' |]),

        // String
        "compare 'hello' with 'hello'" >@ () => StringAssert.equal("hello", "hello"),
        "compare list(string)" >@ () => StringAssert.equal_list(["Hello", "World"], ["Hello", "World"]),
        "compare array(string)" >@ () => StringAssert.equal_array([| "Hello", "World" |], [| "Hello", "World" |]),
    ];
};
```
