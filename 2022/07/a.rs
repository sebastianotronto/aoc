mod common;
use common::*;

fn main() {
    let fs = FileSystem::build_from_stdin();
    let sum: usize = fs.iter()
        .filter(|f| matches!(f.kind, FileType::Directory(_)))
        .map(|f| f.real_size(&fs))
        .filter(|s| *s <= 100000)
        .sum();
    println!("{sum}");
}
