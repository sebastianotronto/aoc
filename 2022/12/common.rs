use std::collections::VecDeque;

#[derive(Copy, Clone)]
pub struct Cell {
    pub h: i8,
    #[allow(unused)]
    pub is_start: bool,
    pub seen: usize
}

pub struct Map {
    pub cells: Vec<Vec<Cell>>,
    pub end: (usize, usize)
}

impl Map {
    pub fn neighbors(&self, v: (usize, usize)) -> Vec<(usize, usize)> {
        [
            ((v.0 as i64) -1, v.1 as i64),
            ((v.0 as i64) +1, v.1 as i64),
            (v.0 as i64, (v.1 as i64) -1),
            (v.0 as i64, (v.1 as i64) +1)
        ].iter()
         .filter(|p| p.0 >= 0 && p.0 < self.cells.len() as i64 &&
                     p.1 >= 0 && p.1 < self.cells[0].len() as i64)
         .map(|x| (x.0 as usize, x.1 as usize))
         .collect()
    }
}

pub fn read_input() -> Map {
    let mut cells = Vec::<Vec<Cell>>::new();
    let mut end = (0, 0);
    let mut line = String::new();
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        let mut v = Vec::<Cell>::new();
        let cs = line.as_bytes();
        for i in 0..line.len()-1 {
            let mut is_start = false;
            let h = match cs[i] as char {
                'a'..='z' => cs[i] - ('a' as u8),
                'S' => { is_start = true; 0 },
                'E' => { end = (cells.len(), i); 26 },
                u => panic!("Unexpected char {}", u)
            } as i8;
            let seen = if cs[i] as char == 'E' { 0 } else { usize::MAX };
            v.push(Cell { h, is_start, seen });
        }
        cells.push(v);
        line.clear();
    }
    Map { cells, end }
}

pub fn shortest_path_back(map: &mut Map, end: fn(&Cell) -> bool) -> usize {
    let mut next = VecDeque::from([map.end]);
    while !next.is_empty() {
        let i = next.pop_front().unwrap();
        let v = map.cells[i.0][i.1];
        for j in map.neighbors(i) {
            let w = &mut map.cells[j.0][j.1];
            if w.h - v.h >= -1 && w.seen == usize::MAX {
                w.seen = v.seen + 1;
                if end(w) { return w.seen; }
                next.push_back(j);
            }
        }
    }
    panic!("No path found");
}
