use std::ops;

pub enum FileType {
    File(usize),
    Directory(Vec<usize>)
}

pub struct File {
    pub kind: FileType,
    name: String
}

impl File {
    pub fn real_size(&self, fs: &FileSystem) -> usize {
        match &self.kind {
            FileType::File(s) => *s,
            FileType::Directory(c) =>
                c.iter().map(|x: &usize| fs[*x].real_size(&fs)).sum()
        }
    }
}

pub struct FileSystem {
    files: Vec<File>
}

impl FileSystem {
    fn new() -> Self {
        Self {
            files: vec![File {
                kind: FileType::Directory(Vec::<usize>::new()),
                name: String::from("/")
            }]
        }
    }

    pub fn build_from_stdin() -> Self {
        let mut fs = FileSystem::new();
        let mut path = Path::new();
        let mut line = String::new();
        while std::io::stdin().read_line(&mut line).unwrap() > 0 {
            if &line[..5] == "$ cd " {
                exec_cd(&line[5..], &mut path, &fs);
            } else if &line[..3] == "dir" {
                fs.add_dir(&line[4..line.len()-1], path.last());
            } else if line.as_bytes()[0] != '$' as u8 {
                let i = line.find(' ').unwrap();
                let size = line[0..i].parse::<usize>().unwrap();
                fs.add_file(&line[i+1..line.len()-1], size, path.last());
            }
            line.clear();
        }
        fs
    }

    fn make_parent(&mut self, id: usize, parent: usize) {
        let p = &mut self.files[parent];
        if let FileType::Directory(v) = &mut p.kind {
            v.push(id);
        } else {
            panic!("Parent is not a directory");
        }
    }

    fn add_dir(&mut self, name: &str, parent: usize) {
        let id = self.files.len();
        self.files.push(
            File {
                kind: FileType::Directory(Vec::<usize>::new()),
                name: String::from(name)
            }
        );
        self.make_parent(id, parent);
    }

    fn add_file(&mut self, name: &str, size: usize, parent: usize) {
        let id = self.files.len();
        self.files.push(
            File {
                kind: FileType::File(size),
                name: String::from(name)
            }
        );
        self.make_parent(id, parent);
    }

    pub fn iter(&self) -> impl Iterator<Item = &File>{
        self.files.iter()
    }
}

impl ops::Index<usize> for FileSystem {
    type Output = File;
    fn index(&self, i: usize) -> &File {
        &self.files[i]
    }
}

struct Path {
    stack: Vec<usize>
}

impl Path {
    fn new() -> Self { Self { stack: vec![0] } } // 0 is the id of "/"
    fn last(&self) -> usize { *self.stack.last().unwrap() }
    fn clear(&mut self) { self.stack.drain(1..); }
    fn pop(&mut self) { self.stack.pop(); }
    fn push(&mut self, dir_id: usize) { self.stack.push(dir_id); }
}

fn exec_cd(line: &str, path: &mut Path, fs: &FileSystem) {
    if line.as_bytes()[0] == '/' as u8 {
        path.clear();
    } else if &line[..2] == ".." {
        path.pop();
    } else {
        let current_dir = &fs[path.last()];
        if let FileType::Directory(children) = &current_dir.kind {
            for c in children {
                if fs[*c].name == &line[..line.len()-1] {
                    path.push(*c);
                    return;
                }
            }
        } else {
            panic!("Non-directory in path");
        }
        panic!("Directory not found in current path");
    }
}
