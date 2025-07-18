mod common;
use common::*;

fn drop(map: &mut Map, i: (usize, usize)) -> bool {
    let (x, y) = i;
    if y > map.ymax { return false; }

    for j in vec![(x, y+1), (x-1, y+1), (x+1, y+1)].into_iter() {
        if !map.at(j) { return drop(map, j); }
    }

    map[i] = true;
    true
}

fn main() {
    let mut map = read_map_from_stdin();
    let mut i = 0;
    while drop(&mut map, (500, 0)) { i+= 1; }
    //map.print();
    println!("{i}");
}
