use crate::solver::Solver;
use std::cmp;

pub struct Day5 {
    boarding_passes: Vec<String>,
}

fn get_boarding_id(boarding_pass: &String) -> i64 {
    let (mut row_lower, mut row_upper, mut column_lower, mut column_upper) = (0, 127, 0, 7);
    for c in boarding_pass.chars() {
        match c {
            'F' => row_upper = (row_upper + row_lower) / 2,
            'B' => row_lower = (row_upper + row_lower) / 2 + 1,
            'L' => column_upper = (column_upper + column_lower) / 2,
            'R' => column_lower = (column_upper + column_lower) / 2 + 1,
            _ => (),
        }
    }
    cmp::min(row_lower, row_upper) * 8 + cmp::max(column_lower, column_upper)
}

impl Day5 {
    fn solve_part1(&self) -> i64 {
        let mut highest_id = 0;
        for boarding_pass in &self.boarding_passes {
            let id = get_boarding_id(boarding_pass);
            if id > highest_id {
                highest_id = id;
            }
        }
        highest_id
    }

    fn solve_part2(&self) -> i64 {
        let mut seats = [false; 1024];
        for boarding_pass in &self.boarding_passes {
            let id = get_boarding_id(boarding_pass);
            seats[id as usize] = true;
        }
        let middle = 512;
        for i in 1..(middle - 1) {
            if !seats[middle - i] && (seats[middle - i - 1] && seats[middle - i + 1]) {
                return (middle - i) as i64;
            }
            if !seats[middle + i] && (seats[middle + i - 1] && seats[middle + i + 1]) {
                return (middle + i) as i64;
            }
        }
        -1
    }
}

impl Solver for Day5 {
    fn new(lines: impl Iterator<Item = String>) -> Self {
        Day5 {
            boarding_passes: lines.collect(),
        }
    }

    fn solve(&mut self) -> (i64, i64) {
        (self.solve_part1(), self.solve_part2())
    }
}
