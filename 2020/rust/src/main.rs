use solver::Solver;

use std::env;
use std::fs::File;
use std::io::{self, BufRead};
use std::iter::Iterator;
use std::path::PathBuf;
use std::process;

#[macro_use]
mod solver;
mod util;

add_solutions![
    "day1" => day1::Day1,
    "day2" => day2::Day2,
    "day3" => day3::Day3,
    "day4" => day4::Day4,
    "day5" => day5::Day5,
];

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

    if let Some(solution) = get_solution(&args[1], lines) {
        println!("{}: {}, {}", args[1], solution.0, solution.1);
    } else {
        println!("Solution for {} not found", args[1]);
        process::exit(1);
    }

    Ok(())
}
