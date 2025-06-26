mod common;
use common::*;

fn main() {
    let contained = |a: (i64, i64), b: (i64, i64)| a.0 >= b.0 && a.1 <= b.1;
    println!("{}", count(|a, b| contained(a, b) || contained(b, a)));
}
