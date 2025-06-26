mod common;
use common::*;

fn main() {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    let i = first_index_n_distinct(line.as_bytes(), 14) + 1;
    println!("{i}");
}
