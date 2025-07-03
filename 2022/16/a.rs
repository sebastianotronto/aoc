use std::cmp::max;
use std::collections::HashMap;

#[derive(Debug, Clone)]
struct Node {
    name: u16,
    rate: usize,
    neighbors: Vec<u16>
}

#[derive(Debug, Copy, Clone)]
struct MapState {
    valves: usize,
    pos_ind: usize,
    max_pos: usize
}

#[derive(Debug, Clone)]
struct Map {
    index: HashMap<u16, usize>,
    nodes: Vec<Node>
}

fn getname(line: &str) -> u16 {
    100 * (line.chars().nth(0).unwrap() as u16) +
          (line.chars().nth(1).unwrap() as u16)
}

impl Node {
    fn from_line(line: &str) -> Node {
        let name = getname(&line[6..]);
        let j = line.find(';').unwrap();
        let rate = line[23..j].parse::<usize>().unwrap();
        let mut neighbors = vec![];
        let mut i = j+24;
        // "tunnels lead to valves" vs "tunnel lead to valve"
        // What kind of sadistic animal made these inputs?
        if line.chars().nth(i).unwrap() == ' ' { i += 1; }
        while i < line.len() {
            neighbors.push(getname(&line[i..]));
            i += 4;
        }
        Node { name, rate, neighbors }
    }
}

impl Map {
    fn from_stdin() -> Map {
        let mut line = String::new();
        let mut nodes = Vec::<Node>::new();
        while std::io::stdin().read_line(&mut line).unwrap() > 0 {
            let node = Node::from_line(&line);
            if nodes.len() > 0 && node.name == getname("AA") {
                nodes.push(nodes[0].clone());
                nodes[0] = node;
            } else {
                nodes.push(node);
            }
            line.clear();
        }
        let index = nodes.iter()
            .enumerate()
            .map(|(i, n)| (n.name, i))
            .collect::<HashMap<_, _>>();
        Map { index, nodes }
    }

    fn state_max(&self) -> usize {
        let mut i: usize = 0;
        let mut tot: usize = 0;
        for n in &self.nodes {
            if n.rate == 0 { continue; }
            tot += 1 << i;
            i += 1;
        }
        let len = self.nodes.len();
        tot * len + len
    }

    fn released_pressure(&self) -> usize {
        self.nodes.iter()
            .map(|n| if n.valve_on { n.rate } else { 0 })
            .sum()
    }

    fn most_pressure(&self, minutes: usize) -> usize {
        let n = self.state_max();
        let mut t = vec![0 as usize; n];
        let mut u = vec![0 as usize; n];
        let mut map = self.clone();

        // Setup table for last minute
        for s in 0..n {
            map.set_state(s);
            t[s] = map.released_pressure();
        }

        // Dynamic programming counting back to 0 minutes
        for i in (0..minutes).rev() {
            // Double buffer technique so we don't have to swap vectors
            let (current, next) = if i % 2 == minutes % 2 {
                (&mut t, &mut u)
            } else {
                (&mut u, &mut t)
            };
            for s in 0..n {
                map.set_state(s);
                let pos = map.pos;
                let mut k = 0;
                let ind = map.index[&pos];
                let p = map.released_pressure();

                // Try turning on the valve
                if map.nodes[ind].rate > 0 && !map.nodes[ind].valve_on {
                    map.nodes[ind].valve_on = true;
                    k = max(k, p + next[map.get_state()]);
                    map.nodes[ind].valve_on = false;
                }

                // Try moving to a neighbor
                for v in &map.nodes[ind].neighbors {
                    map.pos = *v;
                    k = max(k, p + next[map.get_state()]);
                }
                current[s] = k;
            }
        }
        if 0 == minutes % 2 { t[0] } else { u[0] }
    }
}

fn main() {
    let map = Map::from_stdin();
    println!("{}", map.most_pressure(29));
}
