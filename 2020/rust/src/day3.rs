use crate::post_inc;
use crate::solver::Solver;

pub struct Day3 {
    slope: Vec<String>,
}

impl Day3 {
    fn trees_on_slope(&self, slope_x: usize, slope_y: usize) -> i64 {
        let (mut num_trees, mut x, mut y) = (0, 0, 0);
        for row in &self.slope {
            if post_inc!(y) % slope_y != 0 {
                continue;
            }
            // can use the bytes instead of chars because we know
            // that the only chars we care about are single byte.
            if row.as_bytes()[x % row.len()] == '#' as u8 {
                num_trees += 1;
            }
            x += slope_x;
        }
        return num_trees;
    }

    fn solve_part1(&self) -> i64 {
        return self.trees_on_slope(3, 1);
    }

    fn solve_part2(&self) -> i64 {
        let mut answer = 1;
        answer *= self.trees_on_slope(1, 1);
        answer *= self.trees_on_slope(3, 1);
        answer *= self.trees_on_slope(5, 1);
        answer *= self.trees_on_slope(7, 1);
        answer *= self.trees_on_slope(1, 2);
        return answer;
    }
}

impl Solver for Day3 {
    fn new(lines: impl Iterator<Item = String>) -> Self {
        Day3 {
            slope: lines.collect(),
        }
    }

    fn solve(&self) -> (i64, i64) {
        (self.solve_part1(), self.solve_part2())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use indoc::indoc;

    const INPUT: &'static str = indoc! {"
        ..##.......
        #...#...#..
        .#....#..#.
        ..#.#...#.#
        .#...##..#.
        ..#.##.....
        .#.#.#....#
        .#........#
        #.##...#...
        #...##....#
        .#..#...#.#
    "};

    #[test]
    fn part1() {
        let solution = Day3::new(INPUT.lines().map(|line| line.to_owned()));
        assert_eq!(solution.solve_part1(), 7);
    }

    #[test]
    fn part2() {
        let solution = Day3::new(INPUT.lines().map(|line| line.to_owned()));
        assert_eq!(solution.solve_part2(), 336);
    }
}
