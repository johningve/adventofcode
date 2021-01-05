use std::iter::Iterator;

pub trait Solver {
	fn new(lines: impl Iterator<Item = String>) -> Self;
	fn solve(&self) -> (i64, i64);
}
