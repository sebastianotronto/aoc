#[derive(Copy, Clone, Hash, Eq, PartialEq)]
pub struct Pos {
    pub x: i64,
    pub y: i64
}

#[derive(Copy, Clone, Ord, PartialOrd, Eq, PartialEq)]
pub struct Range {
    pub left: i64,
    pub right: i64
}

#[derive(Copy, Clone, Hash, Eq, PartialEq)]
pub struct Sensor {
    pub s: Pos,
    pub b: Pos,
    pub d: i64
}

pub fn distance(p: Pos, q: Pos) -> i64 {
   (p.x-q.x).abs() + (p.y-q.y).abs() 
}

impl Sensor {
    pub fn from_line(line: &str) -> Sensor {
        let mut i = 1 + line.find('=').unwrap();
        let mut j = line.find(',').unwrap();
        let sx = line[i..j].parse::<i64>().unwrap();

        i = j+4;
        j = line.find(':').unwrap();
        let sy = line[i..j].parse::<i64>().unwrap();

        i = 1 + j + line[j..].find('=').unwrap();
        j = i + line[i..].find(',').unwrap();
        let bx = line[i..j].parse::<i64>().unwrap();

        i = j+4;
        j = line.len()-1;
        let by = line[i..j].parse::<i64>().unwrap();

        let s = Pos { x: sx, y: sy };
        let b = Pos { x: bx, y: by };
        let d = distance(s, b);
        Sensor { s, b, d }
    }

    pub fn get_range(&self, y: i64) -> Range {
        let d = distance(self.s, Pos { x: self.s.x, y });
        Range {
            left: self.s.x - self.d + d,
            right: self.s.x + self.d - d
        }
    }
}

pub fn read_sensors_from_stdin() -> Vec<Sensor> {
    let mut v = Vec::<Sensor>::new();
    let mut line = String::new();
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        v.push(Sensor::from_line(&line));
        line.clear();
    }
    v
}
