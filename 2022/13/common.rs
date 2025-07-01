use std::cmp::Ordering;

#[derive(Debug)]
pub enum Packet {
    Number(i64),
    List(Vec<Packet>)
}

fn compare_lists(l: &Vec<Packet>, k: &Vec<Packet>) -> Ordering {
    for i in 0..std::cmp::min(l.len(), k.len()) {
        let ord = compare(&l[i], &k[i]);
        if ord != Ordering::Equal { return ord; }
    }
    l.len().cmp(&k.len())
}

fn compare_list_single(l: &Vec<Packet>, p: &Packet) -> Ordering {
    if l.len() == 0 { return Ordering::Less; }
    let ord = compare(&l[0], p);
    if ord != Ordering::Equal { return ord; }
    l.len().cmp(&1)
}

pub fn compare(p: &Packet, q: &Packet) -> Ordering {
    match p {
        Packet::Number(n) => {
            match q {
                Packet::Number(m) => n.cmp(&m),
                Packet::List(k) => compare_list_single(k, p).reverse()
            } 
        },
        Packet::List(l) => {
            match q {
                Packet::Number(_) => compare_list_single(l, q),
                Packet::List(k) => compare_lists(l, k)
            }
        }
    }
}

fn parse_int(line: &[u8], i: &mut usize) -> i64 {
    let mut r: i64 = 0;
    loop {
        match line[*i] {
            b'0'..=b'9' => r = r * 10 + (line[*i] as i64) - ('0' as i64),
            b',' | b']' => return r,
            x => panic!("Error: unexpected '{}' at position {} in parse_int",
                        x as char, *i)
        }
        *i += 1;
    }
}

fn parse_list(line: &[u8], i: &mut usize) -> Packet {
    if line[*i] != b'[' {
        panic!("Error: sub-list at {} does not start with '['", *i);
    }
    *i += 1;
    let mut v = Vec::<Packet>::new();
    while *i < line.len() && line[*i] != b'\n' {
        match line[*i] {
            b']' => { *i += 1; return Packet::List(v); },
            b'[' => v.push(parse_list(line, i)),
            b'0'..=b'9' => v.push(Packet::Number(parse_int(line, i))),
            b' ' | b',' => *i += 1,
            x => panic!("Error: unexpected '{}' at position {}", x as char, *i)
        }
    }
    panic!("Error: finished parsing at {}, but ']' not found", *i);
}

pub fn parse(line: &[u8]) -> Packet {
    let mut i = 0;
    parse_list(line, &mut i)
}
