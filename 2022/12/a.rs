mod common;
use common::*;

fn main() {
    let mut map = read_input();
    let end = |c: &Cell| c.is_start;
    println!("{}", shortest_path_back(&mut map, end));
}
