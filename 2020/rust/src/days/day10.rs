use core::num;
use std::collections::VecDeque;

use crate::solver::Solver;

pub struct Day10 {
    numbers: Vec<i64>,
}

impl Day10 {
    fn solve_part1(&mut self) -> i64 {
        let mut diff1 = 0;
        let mut diff3 = 1;
        self.numbers.sort_unstable();
        for (i, n) in self.numbers.iter().enumerate() {
            let diff = if i == 0 { *n } else { *n - self.numbers[i - 1] };
            match diff {
                1 => diff1 += 1,
                3 => diff3 += 1,
                _ => (),
            }
        }
        diff1 * diff3
    }

    fn solve_part2(&mut self) -> i64 {
        self.numbers.sort_unstable();
        let mut numbers = VecDeque::from(self.numbers.clone());
        // add an adapter with jolt 0
        numbers.push_front(0);
        // add an adapter with jolt 3 higher than last adapter
        numbers.push_back(numbers.back().unwrap() + 3);

        -1
    }
}

impl Solver for Day10 {
    fn new(lines: impl Iterator<Item = String>) -> Self {
        Day10 {
            numbers: lines.map(|l| l.parse().unwrap()).collect(),
        }
    }

    fn solve(&mut self) -> (i64, i64) {
        (self.solve_part1(), self.solve_part2())
    }
}

#[cfg(test)]
mod tests {
    use crate::days::day10::Day10;

    const INPUT: &[i64] = &[
        28, 33, 18, 42, 31, 14, 46, 20, 48, 47, 24, 23, 49, 45, 19, 38, 39, 11, 1, 32, 25, 35, 8,
        17, 7, 9, 4, 2, 34, 10, 3,
    ];

    #[test]
    fn part1() {
        assert_eq!(
            Day10 {
                numbers: INPUT.to_vec(),
            }
            .solve_part1(),
            220
        )
    }
}
