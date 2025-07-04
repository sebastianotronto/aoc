pub const MAX_LEN: usize = 20;
pub const DIR: [(i8, i8, i8); 6] = [
    (1, 0, 0), (-1, 0, 0), (0, 1, 0), (0, -1, 0), (0, 0, 1), (0, 0, -1)
];

fn inb(i: i8, j: i8, k: i8) -> bool {
    i >= 0 && i < MAX_LEN as i8 &&
    j >= 0 && j < MAX_LEN as i8 &&
    k >= 0 && k < MAX_LEN as i8
}

pub struct Map {
    cell: [[[bool; MAX_LEN]; MAX_LEN]; MAX_LEN]
}

impl Map {
    pub fn new() -> Map {
        Map { cell: [[[false; MAX_LEN]; MAX_LEN]; MAX_LEN] }
    }

    pub fn from_stdin() -> Map {
        let mut map = Map::new();
        let mut line = String::new();
        while std::io::stdin().read_line(&mut line).unwrap() > 0 {
            let i = 0;
            let j = line.find(',').unwrap();
            let x = line[i..j].parse::<usize>().unwrap();
            let i = j+1;
            let j = line[i..].find(',').unwrap() + i;
            let y = line[i..j].parse::<usize>().unwrap();
            let i = j+1;
            let j = line.find('\n').unwrap();
            let z = line[i..j].parse::<usize>().unwrap();
            map.set(x, y, z, true);
            line.clear();
        }
        map
    }

    pub fn get(&self, x: i8, y: i8, z: i8) -> bool {
        inb(x, y, z) && self.cell[x as usize][y as usize][z as usize]
    }

    pub fn set(&mut self, x: usize, y: usize, z: usize, b: bool) {
        self.cell[x][y][z] = b
    }

    fn free_area(&self, x: usize, y: usize, z: usize) -> usize {
        let mut r = 0;
        for d in DIR {
            let (i, j, k) = (x as i8 + d.0, y as i8 + d.1, z as i8 + d.2);
            if !self.get(i, j, k) {
                r += 1
            }
        }
        r
    }

    pub fn total_free_area(&self) -> usize {
        let mut r = 0;
        for i in 0..MAX_LEN {
            for j in 0..MAX_LEN {
                for k in 0..MAX_LEN {
                    if self.get(i as i8, j as i8, k as i8) {
                        r += self.free_area(i, j, k);
                    }
                }
            }
        }
        r
    }

    #[allow(dead_code)]
    fn fill_from(&mut self, x: i8, y: i8, z: i8) {
        if !inb(x, y, z) || self.get(x, y, z) { return; }
        self.set(x as usize, y as usize, z as usize, true);
        for d in DIR {
            self.fill_from(x + d.0, y + d.1, z + d.2);
        }
    }

    #[allow(dead_code)]
    pub fn fill_exterior(&mut self) {
        for i in 0..MAX_LEN {
            for j in 0..MAX_LEN {
                self.fill_from(0 as i8, i as i8, j as i8);
                self.fill_from((MAX_LEN-1) as i8, i as i8, j as i8);
                self.fill_from(i as i8, 0 as i8, j as i8);
                self.fill_from(i as i8, (MAX_LEN-1) as i8, j as i8);
                self.fill_from(i as i8, j as i8, 0 as i8);
                self.fill_from(i as i8, j as i8, (MAX_LEN-1) as i8);
            }
        }
    }
}
