pub enum Instruction {
    Add(i64),
    Noop
}

pub fn read_instruction(line: &str) -> Instruction {
    if &line[..4] == "addx" {
        let n = line[5..line.len()-1].parse::<i64>().unwrap();
        Instruction::Add(n)
    } else {
        Instruction::Noop
    }
}
