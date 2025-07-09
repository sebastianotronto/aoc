use std::collections::{HashMap, HashSet};

const DIRECTIONS: [[(i64, i64); 3]; 4] = [
    [(-1, 0), (-1, 1), (-1, -1)],
    [(1, 0), (1, 1), (1, -1)],
    [(0, -1), (1, -1), (-1, -1)],
    [(0, 1), (1, 1), (-1, 1)]
];

pub fn read_from_stdin() -> (Vec<(i64, i64)>, HashMap<(i64, i64), usize>) {
    let mut v = vec![];
    let mut lookup = HashMap::new();
    let mut line = String::new();
    let mut i = 0;
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        let bytes = line.as_bytes();
        for j in 0..bytes.len() {
            if bytes[j] == b'#' {
                lookup.insert((i, j as i64), v.len());
                v.push((i, j as i64));
            }
        }
        i += 1;
        line.clear();
    }
    (v, lookup)
}

pub fn free_around(e: (i64, i64), m: &HashMap<(i64, i64), usize>) -> bool {
    for d in [
        (-1, -1), (-1,  0), (-1,  1),
        ( 0, -1),           ( 0,  1),
        ( 1, -1), ( 1,  0), ( 1,  1)
    ] {
        if m.contains_key(&(e.0 + d.0, e.1 + d.1)) { return false; }
    }
    true
}

pub fn play(
    elves: &mut Vec<(i64, i64)>,
    lookup: &mut HashMap<(i64, i64), usize>,
    nturns: usize
) -> Option<usize> {
    let mut claimed = HashMap::<(i64, i64), usize>::new();
    let mut stopped = HashSet::<(i64, i64)>::new();
    for t in 0..nturns {
        // First half
        for i in 0..elves.len() {
            let e = elves[i];
            if free_around(e, &lookup) { continue; }
            for j in 0..4 {
                let d = DIRECTIONS[(t+j)%4].iter()
                        .map(|x| (e.0+x.0, e.1+x.1))
                        .collect::<Vec<_>>();
                if !lookup.contains_key(&d[0]) &&
                   !lookup.contains_key(&d[1]) &&
                   !lookup.contains_key(&d[2])
                {
                    if claimed.contains_key(&d[0]) { stopped.insert(d[0]); }
                    claimed.insert(d[0], i);
                    break;
                }
            }
        }

        // Second half
        let mut any_moved = false;
        for (moveto, i) in &claimed {
            if stopped.contains(&moveto) { continue; }
            any_moved = true;
            lookup.remove(&elves[*i]);
            elves[*i] = *moveto;
            lookup.insert(elves[*i], *i);
        }
        if !any_moved { return Some(t); }

        // Cleanup
        claimed.clear();
        stopped.clear();
    }
    None
}
