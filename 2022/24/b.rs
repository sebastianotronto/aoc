mod common;
use common::*;

fn main() {
    // The approach is greedy: once we reach the start / finish cell,
    // we can wait there as long as we want, so it is always better
    // to reach the partial destinations as soon as possible.

    let map = read_map_from_stdin();
    let a = map.shortest_path(Position::Start, Position::Finish, 0);
    let b = map.shortest_path(Position::Finish, Position::Start, a);
    let c = map.shortest_path(Position::Start, Position::Finish, b);
    println!("{c}");
}
