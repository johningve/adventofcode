#!/usr/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 [day number]"
    exit 1
fi

main_file="src/main.rs"
day_file="src/day$1.rs"

if [ -f "$day_file" ]; then
    echo "File '$day_file' already exists!"
    exit 1
fi

search_pattern="    \"day[[:digit:]]*\" => day[[:digit:]]*::Day[[:digit:]]*"
insert_pattern="    \"day$1\" => day$1::Day$1,"

# add new day to solutions

tac "$main_file" | sed "0,/$search_pattern/s/$search_pattern/$insert_pattern\n&/" | tac > "${main_file}.tmp"
cp -f "${main_file}.tmp" "$main_file"
rm "${main_file}.tmp"

# write code skeleton for new file
cat <<EOF > "$day_file"
use crate::solver::Solver;

pub struct Day$1 {
    lines: Vec<String>,
}

impl Day$1 {
    fn solve_part1(&self) -> i64 {
        -1
    }

    fn solve_part2(&self) -> i64 {
        -1
    }
}

impl Solver for Day$1 {
    fn new(lines: impl Iterator<Item = String>) -> Self {
        Day$1 {
            lines: lines.collect(),
        }
    }

    fn solve(&mut self) -> (i64, i64) {
        (self.solve_part1(), self.solve_part2())
    }
}
EOF
