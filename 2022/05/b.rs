mod common;
use common::*;

fn apply_move(grid: &mut Vec::<Vec::<char>>, line: &str) {
    let (n, from, to) = read_move(&line);

    let first_moved = grid[from-1].len()-n;
    let len = grid[from-1].len();
    for i in first_moved..len {
        let x = grid[from-1][i];
        grid[to-1].push(x);
    }
    grid[from-1].drain(first_moved..len);
}

fn main() {
    let mut grid = get_grid_from_stdin();
    apply_moves_from_stdin(&mut grid, apply_move);
    print_top(&grid);
}
