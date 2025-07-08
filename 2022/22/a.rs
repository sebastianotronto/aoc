use std::cmp::max;
mod common;
use common::*;

#[derive(Copy, Clone, Debug)]
pub struct Position {
    pub i: usize,
    pub j: usize,
    pub d: Direction
}

pub struct Map {
    pub tiles: Vec<Vec<Tile>>
}

type StepFn = fn(&Map, Position) -> Position;

impl Map {
    pub fn from_stdin() -> Map {
        let mut maxlen = 0;
        let mut tiles = vec![];
        let mut line = String::new();
        while std::io::stdin().read_line(&mut line).unwrap() > 1 {
            let v = line[0..line.len()-1].as_bytes().iter()
                .map(|b| Tile::from_byte(*b)).collect::<Vec<_>>();
            maxlen = max(maxlen, v.len());
            tiles.push(v);
            line.clear();
        }
        for v in &mut tiles {
            while v.len() < maxlen { v.push(Tile::Skip); }
        }
        Map { tiles }
    }

    pub fn start_position(&self) -> Position {
        let first_valid = self.tiles[0].iter()
            .position(|t| *t == Tile::Walk).unwrap();
        Position { i: 0, j: first_valid, d: Direction::Right }
    }

    pub fn walk(&self, pos: Position, n: usize, step: StepFn) -> Position {
        let mut p = pos;
        for _ in 0..n { p = step(self, p); }
        p
    }
}

fn step(map: &Map, position: Position) -> Position {
    let imax = map.tiles.len();
    let jmax = map.tiles[0].len();
    let s = position.d.step();
    let mut p = position;
    loop {
        let inext = ((s.0 + imax as i64) as usize + p.i) % imax;
        let jnext = ((s.1 + jmax as i64) as usize + p.j) % jmax;
        p = Position { i: inext, j: jnext, d: p.d };
        match map.tiles[p.i][p.j] {
            Tile::Walk => return p,
            Tile::Wall => return position,
            Tile::Skip => ()
        }
    }
}

fn password(p: Position) -> usize {
    1000 * (p.i+1) + 4 * (p.j+1) + p.d.value()
}

fn main() {
    let map = Map::from_stdin();
    let (turns, steps) = read_instruction_line_from_stdin();
    let mut position = map.start_position();

    for i in 0..turns.len() {
        position = map.walk(position, steps[i], step);
        position.d = position.d.turn(turns[i]);
    }
    position = map.walk(position, steps[steps.len()-1], step);
    println!("{}", password(position));
}
