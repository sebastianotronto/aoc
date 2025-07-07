const MAX_OVERFLOW: i64 = 10000000000;

pub fn read_from_stdin(key: i64) -> Vec<(usize, i64)> {
    let mut line = String::new();
    let mut v = vec![];
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        v.push((v.len(), line[..line.len()-1].parse::<i64>().unwrap() * key));
        line.clear();
    }
    v
}

fn get_newpos(pos: i64, k: i64, n: i64) -> i64 {
    (pos + k + MAX_OVERFLOW * (n-1)) % (n-1)
}

fn move_to(a: &mut [(usize, i64)], i: usize, j: usize) {
    if i < j {
        for k in i..j { a.swap(k, k+1); }
    } else {
        for k in (j+1..=i).rev() { a.swap(k, k-1); }
    }
}

pub fn mix(a: &mut Vec<(usize, i64)>) {
    for i in 0..a.len() {
        let pos = a.iter().position(|x| x.0 == i).unwrap();
        let newpos = get_newpos(pos as i64, a[pos].1, a.len() as i64) as usize;
        move_to(a, pos, newpos);
    }
}

pub fn groove_sum(a: &Vec<(usize, i64)>) -> i64 {
    let n = a.len();
    let z = a.iter().position(|x| x.1 == 0).unwrap();
    a[(z + 1000) % n].1 +  a[(z + 2000) % n].1 + a[(z + 3000) % n].1
}
