mod common;
use common::*;

fn main() {
    let mut monkeys = read_input();
    println!("{}", res_after_n_rounds(&mut monkeys, 20, 3));
}
