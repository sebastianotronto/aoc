mod common;
use common::*;

fn main() {
    let fs = FileSystem::build_from_stdin();
    let remaining = 70000000 - fs[0].real_size(&fs);
    let ds: usize = fs.iter()
        .filter(|f| matches!(f.kind, FileType::Directory(_)))
        .map(|f| f.real_size(&fs))
        .filter(|s| *s + remaining >= 30000000)
        .min().unwrap();
    println!("{ds}");
}
