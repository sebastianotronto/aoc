use std::cmp::{min, max};
mod common;
use common::*;

fn size(elves: &Vec<(i64, i64)>) -> usize {
    let mut imax = i64::MIN;
    let mut jmax = i64::MIN;
    let mut imin = i64::MAX;
    let mut jmin = i64::MAX;
    for e in elves {
        imax = max(imax, e.0);
        jmax = max(jmax, e.1);
        imin = min(imin, e.0);
        jmin = min(jmin, e.1);
    }
    ((imax-imin+1) * (jmax-jmin+1)) as usize
}

fn main() {
    let (mut elves, mut lookup) = read_from_stdin();
    let _ = play(&mut elves, &mut lookup, 10);
    let result = size(&elves) - elves.len();
    println!("{result}");
}
