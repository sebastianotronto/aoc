mod common;
use common::*;

fn main() {
    let e = get_elves_from_stdin();
    let m: i64 = e.iter().map(|a| a.iter().sum()).max().unwrap();
    println!("{m}");
}
