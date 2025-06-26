pub fn value(c: char) -> i64 {
    match c {
        'a'..='z' => (c as i64) - ('a' as i64) + 1,
        'A'..='Z' => (c as i64) - ('A' as i64) + 27,
        _ => panic!("Error: unexpected character '{}'", c)
    }
}
