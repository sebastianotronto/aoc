pub fn get_elves_from_stdin() -> Vec<Vec<i64>> {
    let mut e = Vec::<Vec::<i64>>::new();
    e.push(Vec::<i64>::new());
    let mut line = String::new();
    loop {
        match std::io::stdin().read_line(&mut line).unwrap() {
            0 => break,
            1 => e.push(Vec::<i64>::new()),
            _ => {
                let n = line.trim().parse::<i64>().unwrap();
                let last = e.len() - 1;
                e[last].push(n);
            }
        }
        line.clear();
    }
    e
}
