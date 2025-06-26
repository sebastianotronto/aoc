mod common;
use common::*;

fn apply_move(grid: &mut Vec::<Vec::<char>>, line: &str) {
    let (n, from, to) = read_move(&line);

    for _ in 0..n {
        let x = grid[from-1].pop().unwrap();
        grid[to-1].push(x);
    }
}

fn main() {
    let mut grid = get_grid_from_stdin();
    apply_moves_from_stdin(&mut grid, apply_move);
    print_top(&grid);
}
