#[derive(Debug)]
pub struct Monkey {
    items: Vec<i64>,
    op: fn(i64, i64) -> i64,
    oparg: i64,
    div: i64,
    iftrue: usize,
    iffalse: usize,
    pub inspected: usize
}

fn read_monkey_from_stdin() -> Monkey {
    let mut line = String::new();
    let stdin = std::io::stdin();

    let _ = stdin.read_line(&mut line);
    line.clear();

    let _ = stdin.read_line(&mut line);
    let mut l = 16;
    let mut items = Vec::<i64>::new();
    while line.chars().nth(l).unwrap() != '\n' {
        l += 2;
        let end = line[l..].find(|c| c == ',' || c == '\n').unwrap() + l;
        items.push(line[l..end].parse::<i64>().unwrap());
        l = end;
    }
    line.clear();

    let _ = stdin.read_line(&mut line);
    let old = line.chars().nth(25).unwrap() == 'o';
    let oparg = if old { 0 } else {
        line[25..line.len()-1].parse::<i64>().unwrap()
    };
    let op = match line.chars().nth(23).unwrap() {
        '*' => if old { |x, _| x * x } else { |x, y| x * y },
        '+' => if old { |x, _| x + x } else { |x, y| x + y },
        c => panic!("Expected operator, got {}", c)
    };
    line.clear();

    let _ = stdin.read_line(&mut line);
    let div = line[21..line.len()-1].parse::<i64>().unwrap();
    line.clear();

    let _ = stdin.read_line(&mut line);
    let iftrue = line[29..line.len()-1].parse::<usize>().unwrap();
    line.clear();

    let _ = stdin.read_line(&mut line);
    let iffalse = line[30..line.len()-1].parse::<usize>().unwrap();
    line.clear();

    Monkey { items, op, oparg, div, iftrue, iffalse, inspected: 0 }
}

pub fn read_input() -> Vec<Monkey> {
    let mut v = Vec::<Monkey>::new();
    let mut line = String::new();
    loop {
        v.push(read_monkey_from_stdin());
        if std::io::stdin().read_line(&mut line).unwrap() == 0 { break; }
    }
    v
}

fn play_round(m: &mut Vec<Monkey>, div: i64, modulus: i64) {
    for i in 0..m.len() {
        for k in 0..m[i].items.len() {
            let mut x = (m[i].op)(m[i].items[k], m[i].oparg) / div;
            if div == 1 { x %= modulus; }
            let j = if x % m[i].div == 0 { m[i].iftrue } else { m[i].iffalse };
            m[j].items.push(x);
        }
        m[i].inspected += m[i].items.len();
        m[i].items.clear();
    }
}

fn get_modulus(monkeys: &Vec<Monkey>) -> i64 {
    let mut modulus = 1;
    for m in monkeys { modulus *= m.div; }
    modulus
}

pub fn res_after_n_rounds(m: &mut Vec<Monkey>, n: usize, div: i64) -> usize {
    let modulus = get_modulus(&m);
    for _ in 0..n { play_round(m, div, modulus); }

    let mut m1 = 0;
    let mut m2 = 0;
    for m in m {
        if m.inspected >= m1 {
            m2 = m1;
            m1 = m.inspected;
        } else if m.inspected >= m2 {
            m2 = m.inspected;
        }
    }

    m1 * m2
}
