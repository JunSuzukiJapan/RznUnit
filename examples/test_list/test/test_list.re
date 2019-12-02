let () = {
    open RznUnit;

    let empty_list = [];
    let list_a = [1, 2, 3];

    let test_list_length() = {
        IntAssert.equal(0, List.length(empty_list));
        IntAssert.equal(3, List.length(list_a));
    };

    let test_list_append() = {
        let list_b = List.append(empty_list, [1, 2, 3]);
        IntAssert.equal_list(list_a, list_b);
    };

    "Example Test List" >@@> [
        "test_list_length" @> test_list_length,
        "test_list_append" @> test_list_append,
    ];
};