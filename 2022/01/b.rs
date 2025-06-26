mod common;
use common::*;

fn main() {
    let e = get_elves_from_stdin();
    let mut w = e.iter().map(|a| a.iter().sum()).collect::<Vec<i64>>();
    w.sort_by(|a, b| b.cmp(a));
    println!("{}", w[0] + w[1] + w[2]);
}
