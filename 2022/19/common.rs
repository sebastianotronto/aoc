// This works for part 1, but it is too slow for part 2.
// May be I am doing something wrong with caching?

use std::cmp::{max, Ordering};
use std::ops::{AddAssign, SubAssign};
use std::collections::HashMap;

#[derive(Debug, Copy, Clone, PartialEq, Eq, Hash)]
pub struct Stock {
    pub ore: i32,
    pub cla: i32,
    pub obs: i32
}

impl Stock {
    pub fn all_lower(&self, other: &Self) -> bool {
        self.ore <= other.ore && self.cla <= other.cla && self.obs <= other.obs
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
    }
}

impl SubAssign<&Stock> for Stock {
    fn sub_assign(&mut self, other: &Self) {
        self.ore -= other.ore;
        self.cla -= other.cla;
        self.obs -= other.obs;
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
            bots: Stock { ore: 1, cla: 0, obs: 0 },
            resources: Stock { ore: 0, cla: 0, obs: 0 }
        }
    }
}

#[derive(Debug, Clone, Hash)]
pub struct Blueprint {
    ore_bot_cost: Stock,
    cla_bot_cost: Stock,
    obs_bot_cost: Stock,
    geo_bot_cost: Stock,
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
        let ore_bot_cost = Stock { ore, cla: 0, obs: 0 };

        let ore = Blueprint::parse_one_resource(&line, &mut i);
        let cla_bot_cost = Stock { ore, cla: 0, obs: 0 };

        let (ore, cla) = Blueprint::parse_two_resources(&line, &mut i);
        let obs_bot_cost = Stock { ore, cla, obs: 0 };

        let (ore, obs) = Blueprint::parse_two_resources(&line, &mut i);
        let geo_bot_cost = Stock { ore, cla: 0, obs };

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
    s: &Status,
    m: i32,
    mem: &mut HashMap<(Status, i32), i64>
) -> i64 {
    if m <= 1 { return 0; }

    if let Some(r) = mem.get(&(s.clone(), m)) { return *r; }

    let mut new_status = s.clone();
    new_status.resources += &new_status.bots;

    // If a geode bot can be built, it is always the best thing to do
    if m > 1 && s.resources >= bp.geo_bot_cost {
        new_status.resources -= &bp.geo_bot_cost;
        let result = (m - 1) as i64 + most_geodes(bp, &new_status, m-1, mem);
        mem.insert((s.clone(), m), result);
        return result;
    }

    let mut result = 0;

    // The second check is to avoid producing too many bots for each given
    // type of resource. For example, 5 ore bots will produce more ore
    // than the factory can ever consume, since all bots cost at most 4 ore.
    let can_obs = s.resources >= bp.obs_bot_cost &&
        s.bots.obs < bp.geo_bot_cost.obs;
    let can_cla = s.resources >= bp.cla_bot_cost &&
        s.bots.cla < bp.obs_bot_cost.cla;
    let can_ore = s.resources >= bp.ore_bot_cost &&
        s.bots.ore < 4;

    if m > 2 && can_obs {
        new_status.resources -= &bp.obs_bot_cost;
        new_status.bots.obs += 1;
        result = max(result, most_geodes(bp, &new_status, m-1, mem));
        new_status.bots.obs -= 1;
        new_status.resources += &bp.obs_bot_cost;
    }

    if m > 3 && can_cla {
        new_status.resources -= &bp.cla_bot_cost;
        new_status.bots.cla += 1;
        result = max(result, most_geodes(bp, &new_status, m-1, mem));
        new_status.bots.cla -= 1;
        new_status.resources += &bp.cla_bot_cost;
    }

    if m > 4 && can_ore {
        new_status.resources -= &bp.ore_bot_cost;
        new_status.bots.ore += 1;
        result = max(result, most_geodes(bp, &new_status, m-1, mem));
        new_status.bots.ore -= 1;
        new_status.resources += &bp.ore_bot_cost;
    }

    if !can_obs || !can_cla || !can_ore {
        result = max(result, most_geodes(bp, &new_status, m-1, mem));
    }

    mem.insert((s.clone(), m), result);
    result
}
