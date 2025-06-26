mod common;
use common::*;

pub fn main() {
    let play_score = |s: &[u8]| {
        let other = s[0] as i64 - ('A' as i64);
        let w = s[2] as i64 - ('X' as i64);
        (other + w + 2) % 3 + 1
    };
    let win_score = |s: &[u8]| 3 * ((s[2] as i64) - ('X' as i64));
    let score = get_score(play_score, win_score);
    println!("{score}");
}
