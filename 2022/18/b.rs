mod common;
use common::*;

fn main() {
    let mut map = Map::from_stdin();
    let total_free = map.total_free_area();
    map.fill_exterior();
    let interior_free = map.total_free_area() - 6*MAX_LEN*MAX_LEN;
    println!("{}", total_free - interior_free);
}
