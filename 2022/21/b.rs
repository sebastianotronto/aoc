mod common;
use common::*;

fn solve_for_humn(name: &str, n1: i64, monkeys: &Vec<Monkey>) -> i64 {
    if name == "humn" { return n1; }

    let i = monkeys.iter().position(|m| m.name == name).unwrap();
    if let MonkeyType::Op(op) = &monkeys[i].kind {
        if let Some(n2) = result_or_unknown(&op.m1, &monkeys) {
            // n1 = n2 [op] [unknown]
            match op.op {
                '+' => solve_for_humn(&op.m2, n1-n2, &monkeys),
                '-' => solve_for_humn(&op.m2, n2-n1, &monkeys),
                '*' => solve_for_humn(&op.m2, n1/n2, &monkeys),
                '/' => solve_for_humn(&op.m2, n2/n1, &monkeys),
                _ => panic!("invalid operator")
            }
        } else {
            if let Some(n2) = result_or_unknown(&op.m2, &monkeys) {
                // n1 = [unknown] [op] n2
                match op.op {
                    '+' => solve_for_humn(&op.m1, n1-n2, &monkeys),
                    '-' => solve_for_humn(&op.m1, n1+n2, &monkeys),
                    '*' => solve_for_humn(&op.m1, n1/n2, &monkeys),
                    '/' => solve_for_humn(&op.m1, n1*n2, &monkeys),
                    _ => panic!("invalid operator")
                }
            } else { panic!("both sides undetermined"); }
        }
    } else { panic!("found number when trying to solve for humn"); }
}

fn result_or_unknown(name: &str, monkeys: &Vec<Monkey>) -> Option<i64> {
    if name == "humn" { return None; }

    let i = monkeys.iter().position(|m| m.name == name).unwrap();
    match &monkeys[i].kind {
        MonkeyType::Num(n) => Some(*n),
        MonkeyType::Op(op) => {
            let n1 = result_or_unknown(&op.m1, &monkeys)?;
            let n2 = result_or_unknown(&op.m2, &monkeys)?;
            Some(apply_op(n1, n2, op))
        }
    }
}

pub fn solve(monkeys: &Vec<Monkey>) -> i64 {
    let i = monkeys.iter().position(|m| m.name == "root").unwrap();
    if let MonkeyType::Op(op) = &monkeys[i].kind {
        if let Some(n) = result_or_unknown(&op.m1, &monkeys) {
            return solve_for_humn(&op.m2, n, monkeys);
        } else {
            if let Some(n) = result_or_unknown(&op.m2, &monkeys) {
                return solve_for_humn(&op.m1, n, &monkeys);
            } else { panic!("humn not found"); }
        }
    } else { panic!("root monkey is of type number"); }
}

fn main() {
    let monkeys = read_monkeys_from_stdin();
    println!("{}", solve(&monkeys));
}
