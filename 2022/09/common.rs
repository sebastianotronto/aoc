use std::collections::HashSet;

fn get_dir(c: char) -> (i64, i64) {
    match c {
        'R' => (1, 0),
        'L' => (-1, 0),
        'U' => (0, 1),
        'D' => (0, -1),
        _ => panic!("Unexpected char")
    }
}

fn follow(lead: (i64, i64), trail: (i64, i64)) -> (i64, i64) {
    let max1 = |x: i64| x / (2 - (x%2).abs());
    let d = (max1(lead.0 - trail.0), max1(lead.1 - trail.1));
    (trail.0 + d.0, trail.1 + d.1)
}

fn step(r: &mut Vec<(i64, i64)>, d: (i64, i64)) {
    r[0] = (r[0].0 + d.0, r[0].1 + d.1);
    for i in 1..r.len() {
        if (r[i].0 - r[i-1].0).abs() > 1 || (r[i].1 - r[i-1].1).abs() > 1 {
            r[i] = follow(r[i-1], r[i]);
        } else {
            break;
        }
    }
}

pub fn simulate(n: usize) -> HashSet<(i64, i64)> {
    let mut r = vec![(0, 0); n];
    let mut visited = HashSet::<(i64, i64)>::new();
    visited.insert(r[n-1]);

    let mut line = String::new();
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        let dir = get_dir(line.chars().nth(0).unwrap());
        let l = line[2..line.len()-1].parse::<usize>().unwrap();
        for _ in 0..l {
            step(&mut r, dir);
            visited.insert(r[n-1]);
        }
        line.clear();
    }
    visited
}
