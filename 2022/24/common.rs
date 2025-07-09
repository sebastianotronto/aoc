// This code is more complicated than it should be. The reason is that
// for part 1 I decided to ignore the start and finish position, and not
// to treat them as other cells. This way I could get away with not
// considering wall cells '#' at all.
// But then for part 2 it was more convenient to include them, so I
// added an enum Position {} that treats start and finish as special
// cases. This is quite messy.

use std::collections::{VecDeque, HashSet};

#[derive(PartialEq, Debug)]
pub enum Direction { Up, Down, Left, Right, None }

impl Direction {
    pub fn from_byte(b: u8) -> Direction {
        match b {
            b'^' => Direction::Up,
            b'v' => Direction::Down,
            b'>' => Direction::Right,
            b'<' => Direction::Left,
            b'.' => Direction::None,
            x => panic!("unexpected char '{}'", x as char)
        }
    }
}

#[derive(Hash, Eq, PartialEq, Copy, Clone, Debug)]
pub enum Position {
    Start,
    Finish,
    Other { i: usize, j: usize }
}

impl Position {
    pub fn dist(&self, other: Position) -> usize {
        match (*self, other) {
            (Position::Start, Position::Start) |
            (Position::Finish, Position::Finish) =>
                0,
            (Position::Start, Position::Finish) |
            (Position::Finish, Position::Start) =>
                usize::MAX, // Not technically correct, but it works
            (Position::Start | Position::Finish, Position::Other { i, j }) |
            (Position::Other { i, j }, Position::Start | Position::Finish) =>
                i + j,
            (Position::Other { i: i1, j: j1 },
             Position::Other { i: i2, j: j2 }) => {
                let i = (i1 as i64 - i2 as i64).abs() as usize;
                let j = (j1 as i64 - j2 as i64).abs() as usize;
                i + j
            }
        }
    }
}

pub struct Map {
    pub tiles: Vec<Vec<Direction>>,
    pub imax: usize,
    pub jmax: usize
}

#[derive(Hash, Eq, PartialEq, Copy, Clone, Debug)]
struct Node {
    p: Position,
    t: usize
}

impl Map {
    fn submod(i: usize, t: usize, m: usize) -> usize {
        let maybeneg = ((i as i64) - (t as i64)) % m as i64;
        (maybeneg as usize + m) % m
    }

    pub fn is_busy(&self, p: Position, t: usize) -> bool {
        match p {
            Position::Start | Position::Finish => false,
            Position::Other { i, j } => {
                let iup = Self::submod(i, t, self.imax);
                let idown = (i + t) % self.imax;
                let jleft = Map::submod(j, t, self.jmax);
                let jright = (j + t) % self.jmax;

                self.tiles[iup][j] == Direction::Down ||
                self.tiles[idown][j] == Direction::Up ||
                self.tiles[i][jleft] == Direction::Right ||
                self.tiles[i][jright] == Direction::Left
            }
        }
    }

    #[allow(dead_code)]
    pub fn print(&self, t: usize) {
        print!("#.");
        for _ in 0..self.jmax { print!("#"); }
        println!();

        for i in 0..self.imax {
            print!("#");
            for j in 0..self.jmax {
                let p = Position::Other { i, j };
                print!("{}", if self.is_busy(p, t) { '*' } else { '.' });
            }
            println!("#");
        }

        for _ in 0..self.jmax { print!("#"); }
        print!(".#");
        println!();
    }

    fn mv(&self, p: Position, d: Direction) -> Option<Position> {
        if d == Direction::None { return Some(p); }
        match p {
            Position::Start => if d == Direction::Down {
                Some(Position::Other { i: 0, j: 0 })
            } else { None },
            Position::Finish => if d == Direction::Up {
                Some(Position::Other { i: self.imax-1, j: self.jmax-1 })
            } else { None },
            Position::Other { i, j } => match d {
                Direction::Up => if i > 0 {
                    Some(Position::Other { i: i-1, j })
                } else {
                    if i == 0 && j == 0 {
                        Some(Position::Start)
                    } else { None }
                },
                Direction::Down => if i < self.imax-1 {
                    Some(Position::Other { i: i+1, j })
                } else {
                    if i == self.imax-1 && j == self.jmax-1 {
                        Some(Position::Finish)
                    } else { None }
                },
                Direction::Left => if j > 0 {
                    Some(Position::Other { i, j: j-1 })
                } else { None },
                Direction::Right => if j < self.jmax-1 {
                    Some(Position::Other { i, j: j+1 })
                } else { None },
                Direction::None => panic!("stupid rust")
            }
        }
    }

    fn maybe_push(&self, x: Node, d: Direction, v: &mut HashSet<Node>) {
        if let Some(p) = self.mv(x.p, d) {
            if !self.is_busy(p, x.t+1) {
                v.insert(Node { p, t: x.t+1 });
            }
        }
    }
    
    pub fn shortest_path(
        &self,
        start: Position,
        finish: Position,
        t0: usize
    ) -> usize {
        let mut vnext = HashSet::<Node>::new();
        vnext.insert(Node { p: start, t: t0 });
        while !vnext.is_empty() {
            let mut v = vnext.clone().into_iter().collect::<Vec<_>>();
            // Heuristic: explore first the positions closer to the target
            v.sort_by(|a, b| a.p.dist(finish).cmp(&(b.p.dist(finish))));
            let mut v = VecDeque::<Node>::from(v);
            vnext.clear();
            while !v.is_empty() {
                let x = v.pop_front().unwrap();
                if x.p == finish { return x.t; }
    
                self.maybe_push(x, Direction::Up, &mut vnext);
                self.maybe_push(x, Direction::Down, &mut vnext);
                self.maybe_push(x, Direction::Left, &mut vnext);
                self.maybe_push(x, Direction::Right, &mut vnext);
                if !self.is_busy(x.p, x.t+1) {
                    self.maybe_push(x, Direction::None, &mut vnext);
                }
            }
        }
        panic!("queue is empty");
    }
}

pub fn read_map_from_stdin() -> Map {
    let mut tiles = vec![];
    let mut line = String::new();
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        let bytes = line.as_bytes();
        if bytes[2] == b'#' {
            line.clear();
            continue;
        }
        let i = tiles.len();
        tiles.push(vec![]);
        for j in 1..bytes.len()-2 {
            tiles[i].push(Direction::from_byte(bytes[j]));
        }
        line.clear();
    }
    let imax = tiles.len();
    let jmax = tiles[0].len();
    Map { tiles, imax, jmax }
}
