extern crate indoc;
extern crate regex;

use day1::Day1;
use day2::Day2;
use day3::Day3;
use solver::Solver;

use std::env;
use std::fs::File;
use std::io::{self, BufRead};
use std::iter::Iterator;
use std::path::PathBuf;
use std::process;

mod day1;
mod day2;
mod day3;
mod solver;
#[macro_use]
mod util;

fn main() -> io::Result<()> {
	// open second argument as file
	let args: Vec<String> = env::args().collect();
	if args.len() < 3 {
		println!("Usage: {} [day, e.g. 'day1'] [path to input].", args[0]);
		process::exit(1);
	}
	let path = PathBuf::from(&args[2]);
	let file = File::open(path)?;
	let lines = io::BufReader::new(file).lines().filter_map(Result::ok);

	let results = match args[1].as_str() {
		"day1" => Day1::new(lines).solve(),
		"day2" => Day2::new(lines).solve(),
		"day3" => Day3::new(lines).solve(),
		_ => {
			println!("Unknown day '{}'", args[1]);
			process::exit(1);
		}
	};

	println!("{}: {}, {}", args[1], results.0, results.1);

	Ok(())
}
