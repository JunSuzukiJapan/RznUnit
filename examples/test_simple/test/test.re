let () = {
    open RznUnit;

    "Simple Test" >@> "compare 1 with 1" @> () => IntAssert.equal(1, 1);
};