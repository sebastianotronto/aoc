pub fn get_score(play_score: fn(&[u8]) -> i64, win_score: fn(&[u8]) -> i64) -> i64 {
    let mut score = 0;
    let mut line = String::new();
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        let l = line.as_bytes();
        score += play_score(l) + win_score(l);
        line.clear();
    }
    score
}
