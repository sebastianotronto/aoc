mod common;
use common::*;

fn draw(cycles: usize, x: i64) {
    let c = cycles % 40;
    if cycles > 0 && c == 0 { println!(); }
    print!("{}", if (x - (c as i64)).abs() <= 1 { '#' } else { '.' });
}

fn main() {
    let mut x: i64 = 1;
    let mut cycles: usize = 0;
    let mut line = String::new();
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        match read_instruction(&line) {
            Instruction::Add(n) => {
                draw(cycles, x);
                draw(cycles+1, x);
                cycles += 2;
                x += n;
            },
            Instruction::Noop => {
                draw(cycles, x);
                cycles += 1;
            }
        }
        line.clear();
    }
}
