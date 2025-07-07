mod common;
use common::*;

fn main() {
    let mut a = read_from_stdin(1);
    mix(&mut a);
    println!("{}", groove_sum(&a));
}
