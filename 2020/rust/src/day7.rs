use crate::solver::Solver;
use crate::util::push_key;
use regex::Regex;
use std::collections::{HashMap, HashSet, VecDeque};

#[derive(Clone)]
struct BagRule {
    name: String,
    number: i32,
}

#[derive(Default)]
pub struct Day7 {
    compatible: HashSet<String>,
    child_to_parent: HashMap<String, Vec<BagRule>>,
    parent_to_child: HashMap<String, Vec<BagRule>>,
}

impl Day7 {
    // cannot use recursion due to needing a mutable reference to self
    fn find_all_compatible(&mut self, rules: &Vec<BagRule>) {
        let mut work = VecDeque::new();
        work.push_back(rules);
        while let Some(rules) = work.pop_front() {
            for ref rule in rules {
                self.compatible.insert(rule.name.clone());
                if let Some(parent_rules) = self.child_to_parent.get(&rule.name) {
                    work.push_back(parent_rules);
                }
            }
        }
    }

    fn find_all_required(&self, rules: &Vec<BagRule>) -> i32 {
        let mut required = 1;
        for rule in rules {
            required += rule.number
                * match self.parent_to_child.get(&rule.name) {
                    Some(rules) => self.find_all_required(rules),
                    None => 1,
                };
        }
        required
    }

    fn solve_part1(&mut self) -> i64 {
        let rules = self
            .child_to_parent
            .get("shiny gold")
            .unwrap_or(&Vec::new())
            .clone();
        self.find_all_compatible(&rules);
        return self.compatible.len() as i64;
    }

    fn solve_part2(&self) -> i64 {
        let rules = self
            .parent_to_child
            .get("shiny gold")
            .unwrap_or(&Vec::new())
            .clone();
        return self.find_all_required(&rules) as i64 - 1;
    }
}

impl Solver for Day7 {
    fn new(lines: impl Iterator<Item = String>) -> Self {
        let mut day7 = Self::default();
        let parent_reg = Regex::new(r"([\w ]+?) bags contain").unwrap();
        let child_reg = Regex::new(r"(\d+) ([\w ]+?) bag").unwrap();

        for ref line in lines {
            let matches = match parent_reg.captures(line) {
                Some(matches) => matches,
                None => continue,
            };

            let parent = matches.get(1).unwrap().as_str().to_owned();
            let mut suffix = &line[matches.get(0).unwrap().end()..];
            while let Some(matches) = child_reg.captures(suffix) {
                let count = matches
                    .get(1)
                    .unwrap()
                    .as_str()
                    .parse::<i32>()
                    .unwrap_or_default();
                let child = matches.get(2).unwrap().as_str().to_owned();
                push_key(
                    &mut day7.child_to_parent,
                    child.clone(),
                    BagRule {
                        name: parent.clone(),
                        number: count,
                    },
                );
                push_key(
                    &mut day7.parent_to_child,
                    parent.clone(),
                    BagRule {
                        name: child.clone(),
                        number: count,
                    },
                );
                suffix = &suffix[matches.get(0).unwrap().end()..];
            }
        }

        day7
    }

    fn solve(&mut self) -> (i64, i64) {
        (self.solve_part1(), self.solve_part2())
    }
}
