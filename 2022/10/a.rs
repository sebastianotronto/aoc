mod common;
use common::*;

fn main() {
    let mut x: i64 = 1;
    let mut cycles: usize = 0;
    let mut step: usize = 20;
    let mut score: i64 = 0;
    let mut line = String::new();
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        let oldx = x;
        match read_instruction(&line) {
            Instruction::Add(n) => { x += n; cycles += 2; },
            Instruction::Noop => { cycles += 1; }
        }
        if cycles >= step {
            score += oldx * (step as i64);
            step += 40;
        }
        line.clear();
    }
    println!("{score}");
}
