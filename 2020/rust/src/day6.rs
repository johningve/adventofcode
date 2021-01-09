use crate::solver::Solver;
use std::collections::{HashMap, HashSet};

pub struct Day6 {
    lines: Vec<String>,
}

impl Day6 {
    fn solve_part1(&self) -> i64 {
        let mut sum = 0;
        let mut answered_questions = HashSet::new();
        for line in &self.lines {
            if line.is_empty() {
                sum += answered_questions.len();
                answered_questions.clear();
                continue;
            }
            for c in line.chars() {
                answered_questions.insert(c);
            }
        }
        sum += answered_questions.len();
        sum as i64
    }

    fn solve_part2(&self) -> i64 {
        let mut sum = 0;
        let mut group_size = 0;
        let mut answered_questions: HashMap<char, i32> = HashMap::new();
        for line in &self.lines {
            if line.is_empty() {
                for question in &answered_questions {
                    if group_size == *question.1 {
                        sum += 1;
                    }
                }
                answered_questions.clear();
                group_size = 0;
                continue;
            }
            group_size += 1;
            for c in line.chars() {
                match answered_questions.get_mut(&c) {
                    Some(v) => *v += 1,
                    None => {
                        answered_questions.insert(c, 1);
                        ()
                    }
                }
            }
        }
        for question in answered_questions {
            if group_size == question.1 {
                sum += 1
            }
        }
        sum
    }
}

impl Solver for Day6 {
    fn new(lines: impl Iterator<Item = String>) -> Self {
        Day6 {
            lines: lines.collect(),
        }
    }

    fn solve(&mut self) -> (i64, i64) {
        (self.solve_part1(), self.solve_part2())
    }
}
