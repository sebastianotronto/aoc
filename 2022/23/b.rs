mod common;
use common::*;

fn main() {
    const MAX_TURNS: usize = 1000;
    let (mut elves, mut lookup) = read_from_stdin();
    if let Some(n) = play(&mut elves, &mut lookup, MAX_TURNS) {
        println!("{}", n+1);
    } else {
        panic!("Not enough turns ({}), try increasing MAX_TURNS", MAX_TURNS);
    }
}
