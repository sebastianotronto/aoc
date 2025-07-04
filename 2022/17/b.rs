// Wow this is was terrible. Clearly you have to find out at which
// exact frequency the shape repeats, but I could not find a good
// way to estimate this apart from computing the first few (10^5)
// rows and then manually checking.

mod common;
use common::*;

fn line_to_u8(line: &[bool]) -> u8 {
    let mut r = 0;
    for i in 0..SCREEN_WIDTH {
        if line[i] { r |= 1 << i as u8; }
    }
    r
}

fn write_lines(screen: &Screen, v: &mut [u8]) {
    for i in 0..SCREEN_HEIGHT {
        v[i] = line_to_u8(&screen.cell[i]);
    }
}

fn isperiod(v: &[u8], l: usize) -> bool {
    const PERIOD_GUESS: usize = 10;
    const TIMES_MATCH: usize = 10;

    for i in 0..PERIOD_GUESS {
        for j in 1..TIMES_MATCH {
            if v[i] != v[i+j*l] { return false; }
        }
    }
    true
}

fn find_period(v: &[u8]) -> (usize, usize) {
    const PREP: usize = 1000;
    const PMAX: usize = 10000;

    for start in 0..PREP {
        for plen in 10..PMAX {
            if isperiod(&v[start..], plen) { return (start+1, plen); }
        }
    }
    panic!("No period of length < {} found with preperiod < {}",
        PMAX, PREP);
}

fn main() {
    const N: usize = 1000000000000;

    let mut screen = Screen::new();
    let rocks = get_rocks();
    let mut line = String::new();
    let _ = std::io::stdin().read_line(&mut line);
    let line = &line[0..line.len()-1]; // remove newline

    let mut i = 0;
    let mut t = 0;
    let mut vv = [0 as u8; SCREEN_HEIGHT];
    let mut ii = [0 as usize; SCREEN_HEIGHT];
    while screen.top < SCREEN_HEIGHT - 10 {
        screen.drop_rock(&rocks[i%5], &mut t, &line);
        ii[screen.top] = i;
        i += 1;
    }
    write_lines(&screen, &mut vv);
    let (prep, plen) = find_period(&vv);

    /* This part shows the period etc...
    println!("prep = {prep}, plen = {plen}");
    for j in 0..10 {
        for k in 0..4 {
            print!(" | t={:>4} i={:>4}", j+prep+k*plen, ii[j+prep+k*plen]);
        }
        println!();
    }
    */

    let i0 = ii[prep];
    let i1 = ii[prep+plen];

    let n = (N - i0) / (i1 - i0); // How many full repeats
    let t = n * plen + prep; // How tall is the thing after n full repeats
    // Remainder (unlike in the example case, it does not end with full repeat)
    let mut rem = 0;
    for j in 0..SCREEN_HEIGHT {
        if ii[j] >= i0 + (N - i0) % (i1 - i0) {
            rem = j-prep;
            break;
        }
    }
    println!("{}", t + rem - 1);
}
