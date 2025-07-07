#[derive(Debug)]
pub struct Operation {
    pub m1: String,
    pub m2: String,
    pub op: char
}

#[derive(Debug)]
pub enum MonkeyType {
    Num(i64),
    Op(Operation)
}

#[derive(Debug)]
pub struct Monkey {
    pub name: String,
    pub kind: MonkeyType
}

pub fn read_monkeys_from_stdin() -> Vec<Monkey> {
    let mut v = vec![];
    let mut line = String::new();
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        let name = String::from(&line[0..4]);
        let monkey = match line.chars().nth(6).unwrap() {
            '0'..='9' => {
                let n = line[6..line.len()-1].parse::<i64>().unwrap();
                Monkey { name, kind: MonkeyType::Num(n) }
            },
            _ => {
                let m1 = String::from(&line[6..10]);
                let m2 = String::from(&line[13..17]);
                let op = Operation { m1, m2, op: line.chars().nth(11).unwrap() };
                Monkey { name, kind: MonkeyType::Op(op) }
            }
        };
        v.push(monkey);
        line.clear();
    }
    v
}

pub fn apply_op(n1: i64, n2: i64, op: &Operation) -> i64 {
    match op.op {
        '+' => n1 + n2,
        '-' => n1 - n2,
        '*' => n1 * n2,
        '/' => n1 / n2,
        _ => panic!("invalid operator")
    }
}
