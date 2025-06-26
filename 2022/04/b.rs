mod common;
use common::*;

fn main() {
    let overlap = |a: (i64, i64), b: (i64, i64)|
        (a.0 >= b.0 && a.0 <= b.1) || (b.0 >= a.0 && b.0 <= a.1);
    println!("{}", count(overlap));
}
