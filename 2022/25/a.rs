mod common;
use common::*;

fn main() {
    let mut line = String::new();
    let mut sum = Snafu::zero();
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        let s = Snafu::from_str(&line[..line.len()-1]);
        sum += &s;
        line.clear();
    }
    println!("{sum}");
}
