fn get_ints(line: &str) -> ((i64, i64), (i64, i64)) {
    let i = line.find('-').unwrap();
    let j = line.find(',').unwrap();
    let k = line[j..].find('-').unwrap() + j;
    ((line[..i].parse().unwrap(), line[i+1..j].parse().unwrap()),
     (line[j+1..k].parse().unwrap(), line[k+1..line.len()-1].parse().unwrap()))
}

pub fn count<F: Fn((i64, i64), (i64, i64)) -> bool>(condition: F) -> i64 {
    let mut line = String::new();
    let mut sum = 0;
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        let (a, b) = get_ints(&line);
        if condition(a, b) {
            sum += 1;
        }
        line.clear();
    }
    sum
}
