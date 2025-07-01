use std::cmp::Ordering;
mod common;
use common::*;

fn driver(n: i64) -> Packet {
    Packet::List(vec![Packet::List(vec![Packet::Number(n)])])
}

fn find_driver(v: &Vec<Packet>, n: i64) -> usize {
    v.iter()
     .position(|p| compare(p, &driver(n)) == Ordering::Equal)
     .unwrap() + 1
}

fn main() {
    let mut v = vec![driver(2), driver(6)];
    let mut line = String::new();
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        if line.len() > 1 { v.push(parse(line.as_bytes())); }
        line.clear();
    }

    v.sort_by(compare);

    println!("{}", find_driver(&v, 2) * find_driver(&v, 6));
}
