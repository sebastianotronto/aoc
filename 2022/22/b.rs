use std::mem::swap;
mod common;
use common::*;

// Use 4 for the test input, 50 for the real one
//const CUBE_SIZE: usize = 4;
const CUBE_SIZE: usize = 50;

// Connections between faces to make the cube 3D.
// This is hard coded to work for my specific input.
// To make it work for a different input you have to change this.
// The faces are in top-to-bottom, left-to-right order of input.
// For each face, the 4 connections are in order right, down, left, up.

// Test case. Configuration:
//   0     U = 0, D = 4
// 123     R = 5, L = 2
//   45    F = 3, B = 1
/*
const CONNECTIONS: [[Connection; 4]; 6] = [
    // Face 0 = U
    [
        Connection { face: 5, side: Direction::Right },
        Connection { face: 3, side: Direction::Up },
        Connection { face: 2, side: Direction::Up },
        Connection { face: 1, side: Direction::Up },
    ],

    // Face 1
    [
        Connection { face: 2, side: Direction::Left },
        Connection { face: 4, side: Direction::Down },
        Connection { face: 5, side: Direction::Down },
        Connection { face: 0, side: Direction::Up },
    ],

    // Face 2
    [
        Connection { face: 3, side: Direction::Left },
        Connection { face: 4, side: Direction::Left },
        Connection { face: 1, side: Direction::Right },
        Connection { face: 0, side: Direction::Left },
    ],

    // Face 3
    [
        Connection { face: 5, side: Direction::Up },
        Connection { face: 4, side: Direction::Up },
        Connection { face: 2, side: Direction::Right },
        Connection { face: 0, side: Direction::Down },
    ],

    // Face 4
    [
        Connection { face: 5, side: Direction::Left },
        Connection { face: 1, side: Direction::Down },
        Connection { face: 2, side: Direction::Down },
        Connection { face: 3, side: Direction::Down },
    ],

    // Face 5
    [
        Connection { face: 0, side: Direction::Right },
        Connection { face: 1, side: Direction::Left },
        Connection { face: 4, side: Direction::Right },
        Connection { face: 3, side: Direction::Right },
    ],
];
*/

// Input. Configuration:
//  01
//  2 
// 34
// 5
const CONNECTIONS: [[Connection; 4]; 6] = [
    // Face 0 = U
    [
        Connection { face: 1, side: Direction::Left },
        Connection { face: 2, side: Direction::Up },
        Connection { face: 3, side: Direction::Left },
        Connection { face: 5, side: Direction::Left },
    ],

    // Face 1
    [
        Connection { face: 4, side: Direction::Right },
        Connection { face: 2, side: Direction::Right },
        Connection { face: 0, side: Direction::Right },
        Connection { face: 5, side: Direction::Down },
    ],

    // Face 2
    [
        Connection { face: 1, side: Direction::Down },
        Connection { face: 4, side: Direction::Up },
        Connection { face: 3, side: Direction::Up },
        Connection { face: 0, side: Direction::Down },
    ],

    // Face 3
    [
        Connection { face: 4, side: Direction::Left },
        Connection { face: 5, side: Direction::Up },
        Connection { face: 0, side: Direction::Left },
        Connection { face: 2, side: Direction::Left },
    ],

    // Face 4
    [
        Connection { face: 1, side: Direction::Right },
        Connection { face: 5, side: Direction::Right },
        Connection { face: 3, side: Direction::Right },
        Connection { face: 2, side: Direction::Down },
    ],

    // Face 5
    [
        Connection { face: 4, side: Direction::Down },
        Connection { face: 1, side: Direction::Up },
        Connection { face: 0, side: Direction::Up },
        Connection { face: 3, side: Direction::Down },
    ],
];


#[derive(Copy, Clone, Debug)]
struct Connection {
    pub face: usize,
    pub side: Direction
}

struct Face {
    pub tiles: [[Tile; CUBE_SIZE]; CUBE_SIZE],
    offset_i: usize,
    offset_j: usize
}

#[derive(PartialEq, Debug, Copy, Clone)]
struct Position {
    f: usize,
    i: usize,
    j: usize,
    d: Direction
}

#[allow(dead_code)]
impl Face {
    pub fn empty() -> Face {
        Face {
            tiles: [[Tile::Skip; CUBE_SIZE]; CUBE_SIZE],
            offset_i: 0,
            offset_j: 0
        }
    }

    pub fn is_empty(&self) -> bool {
        self.tiles[0][0] == Tile::Skip
    }

    pub fn print(&self) {
        for i in 0..CUBE_SIZE {
            for j in 0..CUBE_SIZE {
                print!("{}", self.tiles[i][j].to_char());
            }
            println!();
        }
    }
}

struct Cube {
    pub faces: Vec<Face>
}

type StepFn = fn(&Cube, Position) -> Position;

impl Cube {
    pub fn from_stdin() -> Cube {
        let mut faces = vec![];
        let mut line = String::new();
        let mut offset_i = 0;
        while faces.len() < 6 {
            let mut row = [Face::empty(), Face::empty(), Face::empty(),
                           Face::empty(), Face::empty(), Face::empty()];
            for k in 0..CUBE_SIZE {
                let _ = std::io::stdin().read_line(&mut line);
                let bytes = &line.as_bytes();
                for l in 0..line.len()-1 {
                    row[l / CUBE_SIZE].tiles[k][l % CUBE_SIZE] =
                        Tile::from_byte(bytes[l]);
                }
                line.clear();
            }
            let mut offset_j = 0;
            for mut r in row {
                r.offset_i = offset_i;
                r.offset_j = offset_j;
                if !r.is_empty() {
                    faces.push(r);
                }
                offset_j += CUBE_SIZE;
            }
            offset_i += CUBE_SIZE;
        }
        let _ = std::io::stdin().read_line(&mut line); // Read empty line
        assert!(faces.len() == 6, "Cube has {} faces", faces.len());
        Cube { faces }
    }

    fn start_position(&self) -> Position {
        let j = self.faces[0].tiles[0].iter()
            .position(|t| *t == Tile::Walk).unwrap();
        Position { f: 0, i: 0, j, d: Direction::Right }
    }

    pub fn walk(&self, pos: Position, n: usize, step: StepFn) -> Position {
        let mut p = pos;
        for _ in 0..n { p = step(self, p); }
        p
    }
}

fn flips(d1: Direction, d2: Direction) -> bool {
    match d1 {
        Direction::Right | Direction::Up =>
            d2 == Direction::Right || d2 == Direction::Up,
        Direction::Down | Direction::Left =>
            d2 == Direction::Down || d2 == Direction::Left
    }
}

fn swaps(d1: Direction, d2: Direction) -> bool {
    match d1 {
        Direction::Right | Direction::Left =>
            d2 == Direction::Up || d2 == Direction::Down,
        Direction::Up | Direction::Down =>
            d2 == Direction::Right || d2 == Direction::Left
    }
}

fn validate_connections(conn: &[[Connection; 4]; 6]) {
    for i in 0..6 {
        for j in 0..4 {
            let c = conn[i][j];
            let d = conn[c.face][c.side.value()];
            assert!(d.face == i, "Bad connection: face {}-{}", i, j);
            assert!(d.side.value() == j, "Bad connection: side {}-{}", i, j);
        }
    }
}

fn overflow(i: i64, j: i64) -> Option<Direction> {
    if i == -1 { return Some(Direction::Up) }
    if j == -1 { return Some(Direction::Left) }
    if i as usize == CUBE_SIZE { return Some(Direction::Down) }
    if j as usize == CUBE_SIZE { return Some(Direction::Right) }
    None
}

fn on_other_side(i: i64, flip: bool, positive: bool) -> usize {
    const CUBE_SIZE_I64: i64 = CUBE_SIZE as i64;
    (if i >= 0 && i < CUBE_SIZE_I64 {
        if flip { CUBE_SIZE_I64 - i - 1 } else { i }
    } else {
        if positive { 0 } else { CUBE_SIZE_I64 - 1 }
    }) as usize
}

fn step(cube: &Cube, p: Position) -> Position {
    let s = p.d.step();
    let mut inext = s.0 + p.i as i64;
    let mut jnext = s.1 + p.j as i64;

    let ret = if let Some(d) = overflow(inext, jnext) {
        let conn = CONNECTIONS[p.f][d.value()];
        let flip = flips(p.d, conn.side);
        let new_direction = conn.side.opposite();
        let positive = new_direction.is_positive();
        if swaps(p.d, conn.side) { swap(&mut inext, &mut jnext) }
        Position {
            f: conn.face,
            i: on_other_side(inext, flip, positive),
            j: on_other_side(jnext, flip, positive),
            d: conn.side.opposite()
        }
    } else {
        Position {
            f: p.f,
            i: inext as usize,
            j: jnext as usize,
            d: p.d
        }
    };

    if cube.faces[ret.f].tiles[ret.i][ret.j] == Tile::Wall { p } else { ret }
}

fn password(cube: &Cube, p: Position) -> usize {
    let f = &cube.faces[p.f];
    1000 * (p.i + f.offset_i + 1) + 4 * (p.j + f.offset_j + 1) + p.d.value()
}

fn main() {
    validate_connections(&CONNECTIONS);
    let cube = Cube::from_stdin();
    let mut position = cube.start_position();
    let (turns, steps) = read_instruction_line_from_stdin();
    for i in 0..turns.len() {
        position = cube.walk(position, steps[i], step);
        position.d = position.d.turn(turns[i]);
    }
    position = cube.walk(position, steps[steps.len()-1], step);
    println!("{}", password(&cube, position));
}
