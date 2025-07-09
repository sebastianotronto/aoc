mod common;
use common::*;

fn main() {
    let map = read_map_from_stdin();
    let result = map.shortest_path(Position::Start, Position::Finish, 0);
    println!("{result}");
}
