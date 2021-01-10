use crate::solver::Solver;

enum Instruction {
    Acc(i64),
    Jmp(i64),
    Nop,
}

#[derive(Default)]
struct Handheld {
    instructions: Vec<Instruction>,
    ip: usize,
    acc: i64,
}

impl Handheld {
    fn new(lines: impl Iterator<Item = String>) -> Self {
        let mut hh = Handheld::default();
        for ref line in lines {
            let mut parts = line.split(' ');
            let op_str = parts.next();
            let arg_str = parts.next();
            if op_str.is_none() || arg_str.is_none() {
                continue;
            }
            let op = op_str.unwrap();
            let arg = arg_str.unwrap().parse::<i64>();
            if arg.is_err() {
                continue;
            }
            hh.instructions.push(match op {
                "acc" => Instruction::Acc(arg.unwrap()),
                "jmp" => Instruction::Jmp(arg.unwrap()),
                "nop" => Instruction::Nop,
                _ => continue,
            });
        }
        hh
    }

    fn execute_instruction(&mut self) {
        let instruction = &self.instructions[self.ip];
        match instruction {
            Instruction::Acc(arg) => self.acc += *arg,
            Instruction::Jmp(arg) => self.ip += *arg as usize,
            Instruction::Nop => (),
        }
    }
}

pub struct Day8 {
    hh: Handheld,
}

impl Day8 {
    fn solve_part1(&self) -> i64 {
        -1
    }

    fn solve_part2(&self) -> i64 {
        -1
    }
}

impl Solver for Day8 {
    fn new(lines: impl Iterator<Item = String>) -> Self {
        Day8 {
            hh: Handheld::new(lines),
        }
    }

    fn solve(&mut self) -> (i64, i64) {
        (self.solve_part1(), self.solve_part2())
    }
}
