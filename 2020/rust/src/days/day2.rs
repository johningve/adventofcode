use crate::solver::Solver;
use regex::Regex;

pub struct PasswordRule {
    min: usize,
    max: usize,
    rule: char,
    password: String,
}

impl PasswordRule {
    fn parse(line: String) -> Option<Self> {
        let re = Regex::new(r"(\d+)-(\d+)\s([a-z]):\s([a-z]+)").unwrap();
        let matches = re.captures(line.as_str())?;

        let min = matches.get(1).unwrap().as_str().parse();
        let max = matches.get(2).unwrap().as_str().parse();
        let rule = matches.get(3).unwrap().as_str().chars().next().unwrap();
        let password = matches.get(4).unwrap().as_str();

        // Ignores errors for now
        if max.is_err() || min.is_err() {
            return None;
        }

        Some(PasswordRule {
            min: min.unwrap(),
            max: max.unwrap(),
            rule,
            password: password.to_owned(),
        })
    }

    fn validate_part1(&self) -> bool {
        let occurrences = self.password.matches(self.rule).count();
        occurrences >= self.min && occurrences <= self.max
    }

    fn validate_part2(&self) -> bool {
        let pos1 = self.password.chars().nth(self.min - 1).unwrap() == self.rule;
        let pos2 = self.password.chars().nth(self.max - 1).unwrap() == self.rule;

        pos1 != pos2
    }
}

pub struct Day2 {
    rules: Vec<PasswordRule>,
}

impl Day2 {
    fn solve_part1(&self) -> i64 {
        let mut count: i64 = 0;
        for rule in &self.rules {
            if rule.validate_part1() {
                count += 1;
            }
        }
        count
    }

    fn solve_part2(&self) -> i64 {
        let mut count: i64 = 0;
        for rule in &self.rules {
            if rule.validate_part2() {
                count += 1;
            }
        }
        count
    }
}

impl Solver for Day2 {
    fn new(lines: impl Iterator<Item = String>) -> Self {
        let mut d = Day2 { rules: Vec::new() };
        for ref line in lines {
            if let Some(rule) = PasswordRule::parse(line.to_owned()) {
                d.rules.push(rule);
            }
        }
        d
    }

    fn solve(&mut self) -> (i64, i64) {
        (self.solve_part1(), self.solve_part2())
    }
}

#[cfg(test)]
mod tests {
    use super::PasswordRule;

    #[test]
    fn part1() {
        let rule1 = PasswordRule::parse(String::from("1-3 a: abcde")).unwrap();
        let rule2 = PasswordRule::parse(String::from("1-3 b: cdefg")).unwrap();
        let rule3 = PasswordRule::parse(String::from("2-9 c: ccccccccc")).unwrap();
        assert!(rule1.validate_part1());
        assert!(!rule2.validate_part1());
        assert!(rule3.validate_part1());
    }

    #[test]
    fn part2() {
        let rule1 = PasswordRule::parse(String::from("1-3 a: abcde")).unwrap();
        let rule2 = PasswordRule::parse(String::from("1-3 b: cdefg")).unwrap();
        let rule3 = PasswordRule::parse(String::from("2-9 c: ccccccccc")).unwrap();
        assert!(rule1.validate_part2());
        assert!(!rule2.validate_part2());
        assert!(!rule3.validate_part2());
    }
}
