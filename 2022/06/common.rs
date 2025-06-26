fn all_distinct<T: PartialEq>(a: &[T]) -> bool {
    for i in 0..a.len() {
        for j in i+1..a.len() {
            if a[i] == a[j] {
                return false;
            }
        }
    }
    return true;
}

pub fn first_index_n_distinct(a: &[u8], n: usize) -> usize {
    assert!(n > 0, "{} must be greater than 0", n);
    for i in 0..a.len()-n+1 {
        if all_distinct(&a[i..i+n]) {
            return i+n-1;
        }
    }
    panic!("Cannot find {} distinct in a row", n);
}
