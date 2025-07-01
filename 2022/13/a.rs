use std::cmp::Ordering;
mod common;
use common::*;

fn main() {
    let mut line = String::new();
    let mut sum = 0;
    let mut i = 0;
    loop {
        i += 1;
        let _ = std::io::stdin().read_line(&mut line).unwrap();
        let p = parse(line.as_bytes());
        line.clear();
        let _ = std::io::stdin().read_line(&mut line).unwrap();
        let q = parse(line.as_bytes());
        if compare(&p, &q) != Ordering::Greater { sum += i; }
        if std::io::stdin().read_line(&mut line).unwrap() == 0 { break; }
        line.clear();
    }
    println!("{sum}");
}
