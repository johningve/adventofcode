use std::env;
use std::fs::File;
use std::io::{self, BufRead};
use std::iter::Iterator;
use std::path::PathBuf;
use std::process;

#[macro_use]
mod solver;
mod days;
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
    let lines = io::BufReader::new(file).lines().map(Result::unwrap);

    if let Some(solution) = days::get_solution(&args[1], lines) {
        println!("{}: {}, {}", args[1], solution.0, solution.1);
    } else {
        println!("Solution for {} not found", args[1]);
        process::exit(1);
    }

    Ok(())
}
