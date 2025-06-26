pub type Grid = Vec<Vec<char>>;

fn read_rows() -> Vec<Vec<char>> {
    let mut rows = Vec::<Vec::<char>>::new();
    let mut line = String::new();
    loop {
        let mut row = Vec::<char>::new();

        std::io::stdin().read_line(&mut line).unwrap();
        let line_chars = line.as_bytes();
        if line_chars[1] == '1' as u8 {
            let _ = std::io::stdin().read_line(&mut line);
            break;
        }

        let mut i = 0;
        while i < line_chars.len() {
            row.push(line_chars[i+1] as char);
            i += 4;
        }

        rows.push(row);
        line.clear();
    }

    rows
}

fn rows_to_grid(rows: &Vec<Vec<char>>) -> Grid {
    let mut grid = vec![Vec::<char>::new(); rows[0].len()];
    for row in rows.iter().rev() {
        for i in 0..row.len() {
            if row[i] != ' ' {
                grid[i].push(row[i]);
            }
        }
    }
    grid
}

fn next_usize(line: &str, s: usize) -> (usize, usize) {
    let i = line[s..].find(|c: char| c.is_digit(10)).unwrap() + s;
    let j = line[i..].find(|c: char| c.is_whitespace()).unwrap() + i;
    (line[i..j].parse::<usize>().unwrap(), j)
}

pub fn read_move(line: &str) -> (usize, usize, usize) {
    let (n, i) = next_usize(line, 0);
    let (from, i) = next_usize(line, i);
    let (to, _) = next_usize(line, i);

    (n, from, to)
}

pub fn get_grid_from_stdin() -> Grid {
    rows_to_grid(&read_rows())
}

pub fn apply_moves_from_stdin<F: Fn(&mut Grid, &str) -> ()>(grid: &mut Grid, apply_move: F) {
    let mut line = String::new();
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        apply_move(grid, &line);
        line.clear();
    }
}

pub fn print_top(grid: &Grid) {
    for column in grid {
        let c = match column.last() { Some(d) => d, None => &'_' };
        print!("{}", c);
    }
    println!();
}
