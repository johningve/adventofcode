use crate::solver::Solver;
use std::collections::HashSet;

#[derive(Clone, Copy)]
enum Instruction {
    Acc(i64),
    Jmp(i64),
    Nop(i64),
}

#[derive(Default)]
struct Handheld {
    instructions: Vec<Instruction>,
    ip: i64,
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
                "nop" => Instruction::Nop(arg.unwrap()),
                _ => continue,
            });
        }
        hh
    }

    fn execute_instruction(&mut self) {
        let instruction = &self.instructions[self.ip as usize];
        match instruction {
            Instruction::Acc(arg) => self.acc += *arg,
            Instruction::Jmp(arg) => self.ip += *arg - 1,
            Instruction::Nop(_) => (),
        }
        self.ip += 1;
    }

    fn detect_infinite_loop(&mut self) -> bool {
        self.acc = 0;
        self.ip = 0;
        let mut executed_set = HashSet::new();
        while self.ip >= 0 && self.ip < self.instructions.len() as i64 {
            if executed_set.contains(&self.ip) {
                return true;
            }
            executed_set.insert(self.ip);
            self.execute_instruction();
        }
        return false;
    }

    fn solve_part1(&mut self) -> i64 {
        self.detect_infinite_loop();
        self.acc
    }

    fn solve_part2(&mut self) -> i64 {
        for i in 0..self.instructions.len() {
            let instruction = &mut self.instructions[i];
            let tmp = *instruction;
            *instruction = match instruction {
                Instruction::Nop(arg) => Instruction::Jmp(*arg),
                Instruction::Jmp(arg) => Instruction::Nop(*arg),
                _ => continue,
            };
            drop(instruction);
            if !self.detect_infinite_loop() {
                break;
            }
            self.instructions[i] = tmp;
        }
        self.acc
    }
}

pub struct Day8 {
    hh: Handheld,
}

impl Solver for Day8 {
    fn new(lines: impl Iterator<Item = String>) -> Self {
        Day8 {
            hh: Handheld::new(lines),
        }
    }

    fn solve(&mut self) -> (i64, i64) {
        (self.hh.solve_part1(), self.hh.solve_part2())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use indoc::indoc;

    const INPUT: &str = &indoc! {"
        nop +0
        acc +1
        jmp +4
        acc +3
        jmp -3
        acc -99
        acc +1
        jmp -4
        acc +6
    "};

    #[test]
    fn part1() {
        let mut solution = Day8::new(INPUT.lines().map(|l| l.to_owned()));
        assert_eq!(solution.solve().0, 5);
    }

    #[test]
    fn part2() {
        let mut solution = Day8::new(INPUT.lines().map(|l| l.to_owned()));
        assert_eq!(solution.solve().1, 8);
    }
}
