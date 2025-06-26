mod common;
use common::*;

fn get_rep_val(rucksack: &[u8]) -> i64 {
    let mut seen = [false; 256];
    let mid = rucksack.len()/2;
    for i in 0..mid {
        seen[rucksack[i] as usize] = true;
    }
    for i in mid..rucksack.len() {
        if seen[rucksack[i] as usize] {
            return value(rucksack[i] as char);
        }
    }
    panic!("Could not find repeated char");
}

fn main() {
    let mut sum = 0;
    let mut line = String::new();
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        sum += get_rep_val(line.as_bytes());
        line.clear();
    }
    println!("{sum}");
}
