use std::cmp::{min, max};
use std::ops::{Index, IndexMut};

pub struct Map {
    cells: Vec<Vec<bool>>,
    pub xmin: usize,
    pub xmax: usize,
    pub ymin: usize,
    pub ymax: usize
}

fn line_from_str(s: &str) -> Vec<(usize, usize)> {
    let mut line = vec![];
    let mut i = 0;
    while i < s.len() {
        let mut j = s[i..].find(',').unwrap();
        let x = s[i..i+j].parse::<usize>().unwrap();
        i += j+1;
        j = s[i..].find(|c| c == ' ' || c == '\n').unwrap();
        let y = s[i..i+j].parse::<usize>().unwrap();
        i += j+4;
        line.push((x, y));
    }
    line
}

impl Index<(usize, usize)> for Map {
    type Output = bool;
    fn index(&self, i: (usize, usize)) -> &bool {
        self.validate_index(i);
        &self.cells[i.1-self.ymin][i.0-self.xmin]
    }
}

impl IndexMut<(usize, usize)> for Map {
    fn index_mut(&mut self, i: (usize, usize)) -> &mut bool {
        self.validate_index(i);
        &mut self.cells[i.1-self.ymin][i.0-self.xmin]
    }
}

impl Map {
    fn in_bounds(&self, i: (usize, usize)) -> bool {
        i.0 >= self.xmin && i.0 <= self.xmax &&
        i.1 >= self.ymin && i.1 <= self.ymax
    }

    fn validate_index(&self, i: (usize, usize)) {
        if !self.in_bounds(i) {
            panic!("Out of bounds: {} {} outside [{}, {}]x[{}, {}]",
                i.0, i.1, self.xmin, self.xmax, self.ymin, self.ymax);
        }
    }

    pub fn at(&self, i: (usize, usize)) -> bool {
        self.in_bounds(i) && self[i]
    }

    fn set_bounds(&mut self, lines: &Vec<Vec<(usize, usize)>>) {
        for l in lines {
            for p in l {
                self.xmin = min(self.xmin, p.0);
                self.xmax = max(self.xmax, p.0);
                self.ymin = min(self.ymin, p.1);
                self.ymax = max(self.ymax, p.1+1);
            }
        }

        // Part 2 requires a larger map
        self.xmin = min(self.xmin, 500 - self.ymax - 1);
        self.xmax = max(self.xmax, 500 + self.ymax + 1);
        self.cells = vec![
            vec![false; self.xmax-self.xmin+1]; self.ymax-self.ymin+1
        ];
    }

    fn fill_line(&mut self, line: &Vec<(usize, usize)>) {
        for i in 0..line.len()-1 {
            if line[i].0 == line[i+1].0 {
                let y0 = min(line[i].1, line[i+1].1);
                let y1 = max(line[i].1, line[i+1].1);
                for y in y0..=y1 {
                    self[(line[i].0, y)] = true;
                }
            } else {
                let x0 = min(line[i].0, line[i+1].0);
                let x1 = max(line[i].0, line[i+1].0);
                for x in x0..=x1 {
                    self[(x, line[i].1)] = true;
                }
            }
        }
    }

    fn from_lines(lines: &Vec<Vec<(usize, usize)>>) -> Map {
        let mut map = Map {
             cells: vec![],
             xmin: 500,
             xmax: 500,
             ymin: 0,
             ymax: 0
        };
        map.set_bounds(lines);
        for l in lines { map.fill_line(l); }
        map
    }

    #[allow(dead_code)]
    pub fn print(&self) {
        println!("x: {} to {}", self.xmin, self.xmax);
        println!("y: {} to {}", self.ymin, self.ymax);
        for v in &self.cells {
            for b in v {
                print!("{}", if *b { '#' } else { '.' });
            }
            println!();
        }
    }
}

pub fn read_map_from_stdin() -> Map {
    let mut lines = Vec::<Vec<(usize, usize)>>::new();
    let mut s = String::new();
    while std::io::stdin().read_line(&mut s).unwrap() > 0 {
        lines.push(line_from_str(&s));
        s.clear();
    }
    Map::from_lines(&lines)
}
