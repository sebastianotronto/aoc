use std::cmp::max;

pub const SCREEN_WIDTH: usize = 7;
pub const SCREEN_HEIGHT: usize = 100000;

pub struct Screen {
    pub cell: [[bool; SCREEN_WIDTH]; SCREEN_HEIGHT],
    pub top: usize
}

#[derive(Debug)]
pub struct Rock {
    pub a: Vec<(usize, usize)>,
    pub h: usize
}

pub fn get_rocks() -> Vec<Rock> {
    vec![
        Rock { a: vec![(0, 0), (0, 1), (0, 2), (0, 3)], h: 1 },
        Rock { a: vec![(0, 1), (1, 0), (1, 1), (1, 2), (2, 1)], h: 3 },
        Rock { a: vec![(0, 0), (0, 1), (0, 2), (1, 2), (2, 2)], h: 3 },
        Rock { a: vec![(0, 0), (1, 0), (2, 0), (3, 0)], h: 4 },
        Rock { a: vec![(0, 0), (0, 1), (1, 0), (1, 1)], h: 2 }
    ]
}

fn in_bounds(position: (i32, i32)) -> bool {
    position.0 >= 0 && position.1 >= 0 && position.1 < SCREEN_WIDTH as i32
}

impl Screen {
    pub fn new() -> Screen {
        Screen {
            cell: [[false; SCREEN_WIDTH]; SCREEN_HEIGHT],
            top: 0
        }
    }

    fn allowed(&self, rock: &Rock, p: (i32, i32)) -> bool {
        for r in &rock.a {
            let (i, j) = (r.0 as i32 + p.0, r.1 as i32 + p.1);
            if !in_bounds((i, j)) || self.cell[i as usize][j as usize] {
                return false;
            }
        }
        true
    }

    fn draw(&mut self, rock: &Rock, p: (usize, usize), b: bool) {
        for r in &rock.a {
            self.cell[r.0 + p.0][r.1 + p.1] = b;
        }
    }

    fn move_rock(&mut self, r: &Rock, p: (usize, usize), d: (i32, i32)) -> (usize, usize) {
        let newpos = (p.0 as i32 + d.0, p.1 as i32 + d.1);
        if !self.allowed(r, newpos) { return p; }
        let newpos = (newpos.0 as usize, newpos.1 as usize);
        newpos
    }

    pub fn drop_rock(&mut self, r: &Rock, t: &mut usize, gas: &str) {
        let mut p = (self.top + 3, 2);
        loop {
            let d = gas.chars().nth(*t % gas.len()).unwrap();
            let d = if d == '>' { (0, 1) } else { (0, -1) };
            p = self.move_rock(r, p, d);
            *t += 1;
            let q = self.move_rock(r, p, (-1, 0));
            if p == q { break; } else { p = q; }
        }
        self.draw(r, p, true);
        self.top = max(self.top, p.0 + r.h);
    }

    #[allow(dead_code)]
    pub fn print(&self) {
        for i in (0..=self.top).rev() {
            for j in 0..SCREEN_WIDTH {
                print!("{}", if self.cell[i][j] { '#' } else { '.' })
            }
            println!(" {i}");
        }
    }
}
