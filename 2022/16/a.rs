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
    max_pos: usize,
    valves: usize,
    pub pos: usize
}

#[derive(Debug, Clone)]
struct Map {
    index: HashMap<u16, usize>,
    state_index: HashMap<u16, usize>,
    pressure: Vec<usize>,
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

impl MapState {
    fn from_usize(i: usize, map: &Map) -> MapState {
        let max_pos = map.index.len();
        MapState {
            max_pos,
            valves: i / max_pos,
            pos: i % max_pos
        }
    }

    fn to_usize(&self) -> usize {
        self.max_pos * self.valves + self.pos
    }

    fn get_valve(&self, i: usize) -> bool {
        self.valves & (1 << i) != 0
    }

    fn toggle_valve(&mut self, i: usize) {
        self.valves ^= 1 << i;
    }
}

impl Map {
    fn from_stdin() -> Map {
        let mut line = String::new();

        // Get the nodes
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

        // Compute the node-name-to-index tables
        let mut j = 0;
        let mut index = HashMap::<u16, usize>::new();
        let mut state_index = HashMap::<u16, usize>::new();
        let mut pressure = vec![0];
        for i in 0..nodes.len() {
            index.insert(nodes[i].name, i);
            if nodes[i].rate != 0 {
                state_index.insert(nodes[i].name, j);
                j += 1;

                // Pre-compute flow rate for all states with node[i] turned on
                for k in 0..pressure.len() {
                    pressure.push(pressure[k] + nodes[i].rate);
                }
            }
        }

        Map { index, state_index, pressure, nodes }
    }

    fn state_max(&self) -> usize {
        self.index.len() * (1 << self.state_index.len())
    }

    fn most_pressure(&self, minutes: usize) -> usize {
        let n = self.state_max();
        let mut t = vec![0 as usize; n];
        let mut u = vec![0 as usize; n];

        // Setup table for last minute
        for s in 0..n {
            t[s] = self.pressure[MapState::from_usize(s, self).valves];
            u[s] = t[s];
        }

        // Dynamic programming counting back to 0 minutes
        for i in 0..minutes-1 {
            // Double buffer technique so we don't have to swap vectors
            let (current, next) = if i % 2 == 0 {
                (&mut t, &u)
            } else {
                (&mut u, &t)
            };
            for s in 0..n {
                let mut state = MapState::from_usize(s, self);
                let mut k = 0;
                let ind = self.index[&self.nodes[state.pos].name];
                let p = self.pressure[state.valves];

                // Try turning on the valve
                if self.nodes[ind].rate > 0 {
                    let si = self.state_index[&self.nodes[ind].name];
                    if !state.get_valve(si) {
                        state.toggle_valve(si);
                        k = max(k, p + next[state.to_usize()]);
                        state.toggle_valve(si);
                    }
                }

                // Try moving to a neighbor
                for v in &self.nodes[ind].neighbors {
                    state.pos = self.index[v];
                    k = max(k, p + next[state.to_usize()]);
                }
                current[s] = k;
            }
        }
        if 0 == minutes % 2 { t[0] } else { u[0] } // Initial state = 0
    }
}

fn main() {
    let map = Map::from_stdin();
    let result = map.most_pressure(30);
    println!("{result}");
}
