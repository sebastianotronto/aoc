mod common;
use common::*;

fn main() {
    let map = Map::from_stdin();
    println!("{}", map.total_free_area());
}
