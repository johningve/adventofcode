use std::{cmp::Ordering, collections::VecDeque};

use crate::solver::Solver;

const DEFAULT_PREAMBLE_LEN: usize = 25;

pub struct Day9 {
    numbers: Vec<i64>,
    preamble_len: usize,
}

impl Day9 {
    fn solve_part1(&self) -> i64 {
        let mut cache = VecDeque::new();
        let mut iter = self.numbers.iter();
        iter.by_ref()
            .take(self.preamble_len)
            .for_each(|n| cache.push_back(*n));

        'outer: for n in iter {
            for (i, n1) in cache.iter().enumerate() {
                for (j, n2) in cache.iter().enumerate() {
                    if i == j {
                        continue;
                    }
                    if *n == n1 + n2 {
                        cache.pop_front().unwrap();
                        cache.push_back(*n);
                        continue 'outer;
                    }
                }
            }
            return *n;
        }

        -1
    }

    fn solve_part2(&self) -> i64 {
        let number = self.solve_part1();
        for (i, n) in self.numbers.iter().enumerate() {
            let mut largest = *n;
            let mut smallest = *n;
            let mut sum = *n;
            for m in self.numbers.iter().skip(i + 1) {
                if *m < smallest {
                    smallest = *m;
                }
                if *m > largest {
                    largest = *m;
                }
                sum += *m;

                match sum.cmp(&number) {
                    Ordering::Equal => return smallest + largest,
                    Ordering::Greater => break,
                    Ordering::Less => (),
                }
            }
        }
        -1
    }
}

impl Solver for Day9 {
    fn new(lines: impl Iterator<Item = String>) -> Self {
        Day9 {
            numbers: lines.map(|l| l.parse().unwrap()).collect(),
            preamble_len: DEFAULT_PREAMBLE_LEN,
        }
    }

    fn solve(&mut self) -> (i64, i64) {
        (self.solve_part1(), self.solve_part2())
    }
}

#[cfg(test)]
mod tests {
    use super::Day9;

    const INPUT: &[i64] = &[
        35, 20, 15, 25, 47, 40, 62, 55, 65, 95, 102, 117, 150, 182, 127, 219, 299, 277, 309, 576,
    ];

    #[test]
    fn part1() {
        assert_eq!(
            Day9 {
                numbers: INPUT.to_vec(),
                preamble_len: 5
            }
            .solve_part1(),
            127
        );
    }

    #[test]
    fn part2() {
        assert_eq!(
            Day9 {
                numbers: INPUT.to_vec(),
                preamble_len: 5
            }
            .solve_part2(),
            62
        )
    }
}
