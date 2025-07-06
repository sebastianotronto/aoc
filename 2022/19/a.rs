use std::collections::HashMap;
mod common;
use common::*;

fn main() {
    const MINUTES: i32 = 24;
    let mut mem = HashMap::<(Status, i32), i64>::new();
    let mut i = 1;
    let mut sum = 0;
    for bp in read_blueprints_from_stdin() {
        let mg = most_geodes(&bp, &Status::new(), MINUTES, &mut mem);
        println!("{i}: {mg}");
        sum += i * mg;
        mem.clear();
        i += 1;
    }
    println!("{sum}");
}
