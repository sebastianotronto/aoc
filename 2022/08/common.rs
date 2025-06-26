pub type Grid = Vec<Vec<(i8, bool)>>;

pub fn read_grid_from_stdin() -> Grid {
    let mut grid = Vec::<Vec<(i8, bool)>>::new();
    let mut line = String::new();
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        let row = line[..line.len()-1].as_bytes().iter()
            .map(|b| ((*b as i8) - ('0' as i8), false)).collect();
        grid.push(row);
        line.clear();
    }
    grid
}
