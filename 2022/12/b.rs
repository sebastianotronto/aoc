mod common;
use common::*;

fn main() {
    let mut map = read_input();
    let end = |c: &Cell| c.h == 0;
    println!("{}", shortest_path_back(&mut map, end));
}
