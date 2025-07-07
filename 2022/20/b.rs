mod common;
use common::*;

fn main() {
    let mut a = read_from_stdin(811589153);
    for _ in 0..10 { mix(&mut a); }
    println!("{}", groove_sum(&a));
}
