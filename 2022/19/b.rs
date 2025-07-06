use std::collections::HashMap;
mod common;
use common::*;

fn main() {
    const MINUTES: i32 = 32;
    let mut mem = HashMap::<(Status, i32), i64>::new();
    let mut prod = 1;
    let bp = read_blueprints_from_stdin();
    for i in 0..3 {
        let mg = most_geodes(&bp[i], &Status::new(), MINUTES, &mut mem);
        println!("{i}: {mg}");
        prod *= mg;
        mem.clear();
    }
    println!("{prod}");
}
