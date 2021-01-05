use crate::solver::Solver;
use std::iter::Iterator;

pub struct Day1 {
	numbers: Vec<i64>,
}

fn find_subset_sum(sum: i64, numbers: &Vec<i64>) -> (usize, usize, bool) {
	for (i, n) in numbers.iter().enumerate() {
		for (j, m) in numbers.iter().enumerate() {
			if n + m == sum && i != j {
				return (i, j, true);
			}
		}
	}
	(0, 0, false)
}

impl Day1 {
	fn solve_part1(&self) -> i64 {
		let (i, j, found) = find_subset_sum(2020, &self.numbers);
		if found {
			return self.numbers[i] * self.numbers[j];
		}
		0
	}

	fn solve_part2(&self) -> i64 {
		for (i, n) in self.numbers.iter().enumerate() {
			let (j, k, found) = find_subset_sum(2020 - n, &self.numbers);
			if found && i != j && i != k {
				return n * self.numbers[j] * self.numbers[k];
			}
		}
		0
	}
}

impl Solver for Day1 {
	fn new(lines: impl Iterator<Item = String>) -> Self {
		let numbers: Vec<i64> = lines
			.map(|line| line.parse::<i64>())
			.filter_map(Result::ok)
			.collect();

		Day1 { numbers }
	}

	fn solve(&self) -> (i64, i64) {
		(self.solve_part1(), self.solve_part2())
	}
}

#[cfg(test)]
mod tests {
	use super::*;

	static INPUT: &'static [i64] = &[1721, 979, 366, 299, 675, 1456];

	#[test]
	fn test_part1() {
		let solution = Day1 {
			numbers: INPUT.to_vec(),
		};
		assert_eq!(solution.solve_part1(), 514579);
	}

	#[test]
	fn test_part2() {
		let solution = Day1 {
			numbers: INPUT.to_vec(),
		};
		assert_eq!(solution.solve_part2(), 241861950);
	}
}
