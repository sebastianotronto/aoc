use std::cmp::max;
use std::collections::HashSet;
mod common;
use common::*;

fn main() {
    const Y: i64 = 2000000;
    let sensors = read_sensors_from_stdin();
    let mut ranges = sensors.iter()
        .map(|s| s.get_range(Y))
        .filter(|r| r.left <= r.right)
        .collect::<Vec<_>>();
    ranges.sort();
    let mut current = Range { left: i64::MIN, right: i64::MIN };
    let mut sum = 0;
    for r in ranges {
        current = Range {
            left: max(current.right+1, r.left),
            right: max(current.right, r.right)
        };
        sum += (current.right - current.left + 1) as usize;
    }
    sum -= sensors.iter()
        .map(|s| s.b)
        .collect::<HashSet<_>>() // Remove duplicates
        .iter()
        .filter(|b| b.y == Y)
        .count();
    println!("{sum}");
}
