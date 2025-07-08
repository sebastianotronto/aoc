use std::cmp::*;

#[derive(PartialEq, Copy, Clone, Debug)]
pub enum Tile { Walk, Wall, Skip }

#[allow(dead_code)]
impl Tile {
    pub fn from_byte(b: u8) -> Tile {
        match b {
            b'.' => Tile::Walk,
            b'#' => Tile::Wall,
            b' ' => Tile::Skip,
            _ => panic!("not a valid tile {}", b)
        }
    }

    pub fn to_char(&self) -> char {
        match self {
            Tile::Walk => '.',
            Tile::Wall => '#',
            Tile::Skip => ' '
        }
    }
}

#[derive(PartialEq, Copy, Clone, Debug)]
pub enum Direction { Up, Down, Right, Left }

#[allow(dead_code)]
impl Direction {
    pub fn from_char(c: char) -> Direction {
        match c {
            'U' => Direction::Up,
            'D' => Direction::Down,
            'R' => Direction::Right,
            'L' => Direction::Left,
            _ => panic!("invalid char for direction")
        }
    }

    pub fn turn(&self, t: Direction) -> Direction {
        match t {
            Direction::Right => match self {
                Direction::Up => Direction::Right,
                Direction::Right => Direction::Down,
                Direction::Down => Direction::Left,
                Direction::Left => Direction::Up
            },
            Direction::Left => match self {
                Direction::Up => Direction::Left,
                Direction::Left => Direction::Down,
                Direction::Down => Direction::Right,
                Direction::Right => Direction::Up
            }
            _ => panic!("cannot turn up or down")
        }
    }

    pub fn step(&self) -> (i64, i64) {
        match self {
            Direction::Up => (-1, 0),
            Direction::Down => (1, 0),
            Direction::Right => (0, 1),
            Direction::Left => (0, -1)
        }
    }

    pub fn value(&self) -> usize {
        match self {
            Direction::Right => 0,
            Direction::Down => 1,
            Direction::Left => 2,
            Direction::Up => 3
        }
    }

    pub fn opposite(&self) -> Direction {
        match self {
            Direction::Right => Direction::Left,
            Direction::Left => Direction::Right,
            Direction::Up => Direction::Down,
            Direction::Down => Direction::Up
        }
    }

    pub fn is_positive(&self) -> bool {
        *self == Direction::Down || *self == Direction::Right
    }
}

pub fn read_instruction_line_from_stdin() -> (Vec<Direction>, Vec<usize>) {
    let mut dir = vec![];
    let mut step = vec![];
    let mut line = String::new();
    let _ = std::io::stdin().read_line(&mut line);
    let mut i = 0;
    while i < line.len()-1 {
        match line.chars().nth(i).unwrap() {
            '0'..='9' => {
                let j = line[i..].find(|c: char| !c.is_digit(10)).unwrap() + i;
                step.push(line[i..j].parse::<usize>().unwrap());
                i = j;
            },
            c => {
                dir.push(Direction::from_char(c));
                i += 1;
            }
        }
    }
    (dir, step)
}
