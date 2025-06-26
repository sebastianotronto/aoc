use std::cmp::max;
mod common;
use common::*;

fn count_visible_from(grid: &Grid, i0: usize, j0: usize) -> usize {
    let x = grid[i0][j0].0;
    let mut top = 0;
    for i in (0..i0).rev() {
        top += 1;
        if grid[i][j0].0 >= x { break; }
    }

    let mut bottom = 0;
    for i in i0+1..grid.len() {
        bottom += 1;
        if grid[i][j0].0 >= x { break; }
    }

    let mut left = 0;
    for j in (0..j0).rev() {
        left += 1;
        if grid[i0][j].0 >= x { break; }
    }

    let mut right = 0;
    for j in j0+1..grid[0].len() {
        right += 1;
        if grid[i0][j].0 >= x { break; }
    }

    top * bottom * left * right
}

fn max_view_factor(grid: &Grid) -> usize {
    let mut m = 0;
    for i in 0..grid.len() {
        for j in 0..grid[0].len() {
            m = max(m, count_visible_from(grid, i, j));
        }
    }
    m
}

fn main() {
    let grid = read_grid_from_stdin();
    println!("{}", max_view_factor(&grid));
}
