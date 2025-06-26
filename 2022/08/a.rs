use std::cmp::max;
mod common;
use common::*;

fn mark_visible(grid: &mut Grid) {
    let update = |elem: &mut (i8, bool), m: &mut i8| {
        elem.1 = elem.1 || elem.0 > *m;
        *m = max(*m, elem.0);
    };

    for row in &mut *grid {
        // From left
        let mut m = -1;
        for t in &mut *row { update(t, &mut m); }

        // From right
        let mut m = -1;
        for t in &mut row.iter_mut().rev() { update(t, &mut m); }
    }

    for j in 0..grid[0].len() {
        // From top
        let mut m = -1;
        for i in 0..grid.len() { update(&mut grid[i][j], &mut m); }

        // From bottom
        let mut m = -1;
        for i in (0..grid.len()).rev() { update(&mut grid[i][j], &mut m); }
    }
}

fn count_visible(grid: &Grid) -> usize {
    grid.iter()
        .map(|row| row.iter().filter(|c| c.1).count())
        .sum()
}

fn main() {
    let mut grid = read_grid_from_stdin();
    mark_visible(&mut grid);
    println!("{}", count_visible(&grid));
}
