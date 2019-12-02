let () = {
    open RznUnit;

    let setup() = {
        let s = Stack.create();
        Stack.push(1, s);
        Stack.push(2, s);
        Stack.push(3, s);
        s
    };

    let test_top(stack) = {
        IntAssert.equal(3, Stack.top(stack));
    };

    let test_clear(stack) = {
        Stack.clear(stack);
        Assert.raises(Stack.Empty, () => {
            let _ = Stack.pop(stack);
            ();
        });
    };

    let test_pop(stack) = {
        IntAssert.equal(3, Stack.pop(stack));
        IntAssert.equal(2, Stack.pop(stack));
        IntAssert.equal(1, Stack.pop(stack));
        Assert.raises(Stack.Empty, () => {
            let _ = Stack.pop(stack);
            ();
        });
    };

    "Test Stack" >@@> [
        "test_top" @> () => {
            let s = setup();
            test_top(s);
        },
        "test_clear" @> () => {
            let s = setup();
            test_clear(s);
        },
        "test_pop" @> () => {
            let s = setup();
            test_pop(s);
        },
    ];
};