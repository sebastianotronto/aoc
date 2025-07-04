mod common;
use common::*;

fn main() {
    let mut screen = Screen::new();
    let rocks = get_rocks();
    let mut line = String::new();
    let _ = std::io::stdin().read_line(&mut line);
    let line = &line[0..line.len()-1]; // remove newline

    let mut t = 0;
    for i in 0..2022 {
        screen.drop_rock(&rocks[i%5], &mut t, &line);
    }
    println!("{}", screen.top);
}
