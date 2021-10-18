use std::env;
use std::fs::File;
use std::io::{self, BufRead};
use std::iter::Iterator;

use anyhow::bail;
use web::AocClient;

#[macro_use]
mod solver;
mod days;
mod util;
mod web;

fn main() -> anyhow::Result<()> {
    let client =
        AocClient::new().expect("you must create a .session file containing your session cookie");

    let mut args = env::args();

    args.next().unwrap();
    let day = args
        .next()
        .expect("you must specify the day to run")
        .parse()
        .expect("the day must be a positive integer");

    let path = client.load_input(2020, day)?;

    let file = File::open(path)?;
    let lines = io::BufReader::new(file).lines().map(Result::unwrap);

    if let Some(solution) = days::get_solution(day, lines) {
        println!("day{}: {}, {}", day, solution.0, solution.1);
    } else {
        bail!("Solution for day{} not found", day);
    }

    Ok(())
}
