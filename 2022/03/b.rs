mod common;
use common::*;

fn get_rep_val(e: &[String; 3]) -> i64 {
    let mut seen = [[false; 256]; 2];
    for i in 0..2 {
        for c in e[i].chars() {
            seen[i][c as usize] = true;
        }
    }
    for c in e[2].chars() {
        if seen[0][c as usize] && seen[1][c as usize] {
            return value(c);
        }
    }
    panic!("Could not find repeated char");
}

fn main() {
    let mut sum = 0;
    let mut lines: [String; 3] = Default::default();
    while std::io::stdin().read_line(&mut lines[0]).unwrap() > 0 {
        let _ = std::io::stdin().read_line(&mut lines[1]);
        let _ = std::io::stdin().read_line(&mut lines[2]);
        sum += get_rep_val(&lines);
        for l in &mut lines { l.clear(); }
    }
    println!("{sum}");
}
