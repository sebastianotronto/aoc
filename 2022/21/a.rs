mod common;
use common::*;

pub fn calculate(name: &str, monkeys: &Vec<Monkey>) -> i64 {
    let i = monkeys.iter().position(|m| m.name == name).unwrap();
    match &monkeys[i].kind {
        MonkeyType::Num(n) => *n,
        MonkeyType::Op(op) => {
            let n1 = calculate(&op.m1, &monkeys);
            let n2 = calculate(&op.m2, &monkeys);
            apply_op(n1, n2, op)
        }
    }
}

fn main() {
    let monkeys = read_monkeys_from_stdin();
    println!("{}", calculate(&"root", &monkeys));
}
