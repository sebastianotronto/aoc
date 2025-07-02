use std::cmp::max;
mod common;
use common::*;

#[allow(non_snake_case)]
fn get_pos(sensors: &Vec<Sensor>, N: i64) -> Pos {
    for i in 0..=N {
        let mut ranges = sensors.iter()
            .map(|s| s.get_range(i))
            .filter(|r| r.left <= r.right)
            .collect::<Vec<_>>();
        ranges.sort();
        let mut lastr = ranges[0].right;
        for j in 1..ranges.len() {
            if lastr + 1 < ranges[j].left {
                return Pos { x: lastr+1, y: i };
            }
            lastr = max(lastr, ranges[j].right);
        }
        if lastr < N {
            return Pos { x: N, y: i };
        }
    }
    panic!("Position not found");
}

fn main() {
    const N: i64 = 4000000;
    const M: i64 = 4000000;
    let sensors = read_sensors_from_stdin();
    let p = get_pos(&sensors, N);
    println!("x = {}, y = {} -> {}", p.x, p.y, p.x * M + p.y);
}
