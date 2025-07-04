// This works for part 1, but it is too slow for part 2.
// May be I am doing something wrong with caching?

use std::cmp::{max, Ordering};
use std::ops::{AddAssign, SubAssign};
use std::collections::HashMap;

#[derive(Debug, Copy, Clone, PartialEq, Eq, Hash)]
pub struct Stock {
    pub ore: i32,
    pub cla: i32,
    pub obs: i32,
    pub geo: i32
}

impl Stock {
    pub fn all_lower(&self, other: &Self) -> bool {
        self.ore <= other.ore && self.cla <= other.cla &&
        self.obs <= other.obs && self.geo <= other.geo
    }
}

impl PartialOrd for Stock {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        if self == other { return Some(Ordering::Equal); }
        if self.all_lower(other) { return Some(Ordering::Less); }
        if other.all_lower(self) { return Some(Ordering::Greater); }
        None
    }
}

impl AddAssign<&Stock> for Stock {
    fn add_assign(&mut self, other: &Self) {
        self.ore += other.ore;
        self.cla += other.cla;
        self.obs += other.obs;
        self.geo += other.geo;
    }
}

impl SubAssign<&Stock> for Stock {
    fn sub_assign(&mut self, other: &Self) {
        self.ore -= other.ore;
        self.cla -= other.cla;
        self.obs -= other.obs;
        self.geo -= other.geo;
    }
}

#[derive(Debug, Copy, Clone, PartialEq, Eq, Hash)]
pub struct Status {
    pub bots: Stock,
    pub resources: Stock
}

impl Status {
    pub fn new() -> Status {
        Status {
            bots: Stock { ore: 1, cla: 0, obs: 0, geo: 0 },
            resources: Stock { ore: 0, cla: 0, obs: 0, geo: 0 }
        }
    }
}

#[derive(Debug, Clone, Hash)]
pub struct Blueprint {
    ore_bot_cost: Stock,
    cla_bot_cost: Stock,
    obs_bot_cost: Stock,
    geo_bot_cost: Stock
}

impl Blueprint {
    fn parse_one_resource(line: &str, i: &mut usize) -> i32 {
        *i = line[*i..].find("costs ").unwrap() + 6 + *i;
        let j = line[*i..].find(' ').unwrap() + *i;
        line[*i..j].parse::<i32>().unwrap()
    }

    fn parse_two_resources(line: &str, i: &mut usize) -> (i32, i32) {
        *i = line[*i..].find("costs ").unwrap() + 6 + *i;
        let j = line[*i..].find(' ').unwrap() + *i;
        let a = line[*i..j].parse::<i32>().unwrap();

        *i = line[*i..].find("and ").unwrap() + 4 + *i;
        let j = line[*i..].find(' ').unwrap() + *i;
        let b = line[*i..j].parse::<i32>().unwrap();

        (a, b)
    }

    pub fn from_line(line: &str) -> Blueprint {
        let mut i = 0;

        let ore = Blueprint::parse_one_resource(&line, &mut i);
        let ore_bot_cost = Stock { ore, cla: 0, obs: 0, geo: 0 };

        let ore = Blueprint::parse_one_resource(&line, &mut i);
        let cla_bot_cost = Stock { ore, cla: 0, obs: 0, geo: 0 };

        let (ore, cla) = Blueprint::parse_two_resources(&line, &mut i);
        let obs_bot_cost = Stock { ore, cla, obs: 0, geo: 0 };

        let (ore, obs) = Blueprint::parse_two_resources(&line, &mut i);
        let geo_bot_cost = Stock { ore, cla: 0, obs, geo: 0 };

        Blueprint { ore_bot_cost, cla_bot_cost, obs_bot_cost, geo_bot_cost }
    }
}

pub fn read_blueprints_from_stdin() -> Vec<Blueprint> {
    let mut v = vec![];
    let mut line = String::new();
    while std::io::stdin().read_line(&mut line).unwrap() > 0 {
        v.push(Blueprint::from_line(&line));
        line.clear();
    }
    v
}

pub fn most_geodes(
    bp: &Blueprint,
    s: Status,
    m: i32,
    mem: &mut HashMap<(Status, i32), i32>
) -> i32 {
    if m == 0 { return s.resources.geo; }
    if m == 1 { return s.resources.geo + s.bots.geo; }

    if let Some(r) = mem.get(&(s, m)) { return *r; }

    let mut new_status = s;
    new_status.resources += &new_status.bots;

    let mut result = 0;

    if m > 1 && s.resources >= bp.geo_bot_cost {
        new_status.resources -= &bp.geo_bot_cost;
        new_status.bots.geo += 1;
        result = most_geodes(bp, new_status, m-1, mem);

        // If a geode bot can be built, it is always the best thing to do
        mem.insert((s, m), result);
        return result;
    }

    if m > 2 && s.resources >= bp.obs_bot_cost {
        new_status.resources -= &bp.obs_bot_cost;
        new_status.bots.obs += 1;
        result = max(result, most_geodes(bp, new_status, m-1, mem));
        new_status.bots.obs -= 1;
        new_status.resources += &bp.obs_bot_cost;
    }

    if m > 3 && s.resources >= bp.cla_bot_cost {
        new_status.resources -= &bp.cla_bot_cost;
        new_status.bots.cla += 1;
        result = max(result, most_geodes(bp, new_status, m-1, mem));
        new_status.bots.cla -= 1;
        new_status.resources += &bp.cla_bot_cost;
    }

    if m > 4 && s.resources >= bp.ore_bot_cost {
        new_status.resources -= &bp.ore_bot_cost;
        new_status.bots.ore += 1;
        result = max(result, most_geodes(bp, new_status, m-1, mem));
        new_status.bots.ore -= 1;
        new_status.resources += &bp.ore_bot_cost;
    }

    result = max(result, most_geodes(bp, new_status, m-1, mem));

    mem.insert((s, m), result);
    result
}
