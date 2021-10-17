use crate::solver::Solver;
use regex::Regex;

#[derive(Default)]
struct Passport {
    byr: i16,
    iyr: i16,
    eyr: i16,
    hgt: String,
    hcl: String,
    ecl: String,
    pid: String,
    // cid is never used
}

const VALID_ECL: &[&str] = &["amb", "blu", "brn", "gry", "grn", "hzl", "oth"];

impl Passport {
    fn parse(fields: impl Iterator<Item = String>) -> Self {
        let mut passport = Passport::default();
        let field_reg = Regex::new(r"([a-z]+):([a-z\d#]+)").unwrap();
        for ref field in fields {
            if let Some(matches) = field_reg.captures(field) {
                let field = matches.get(1).unwrap().as_str();
                let value = matches.get(2).unwrap().as_str();
                match field {
                    "byr" => passport.byr = value.parse().unwrap_or_default(),
                    "iyr" => passport.iyr = value.parse().unwrap_or_default(),
                    "eyr" => passport.eyr = value.parse().unwrap_or_default(),
                    "hgt" => passport.hgt = value.to_owned(),
                    "hcl" => passport.hcl = value.to_owned(),
                    "ecl" => passport.ecl = value.to_owned(),
                    "pid" => passport.pid = value.to_owned(),
                    _ => (),
                }
            }
        }
        passport
    }

    fn validate_part1(&self) -> bool {
        !(self.byr == 0
            || self.iyr == 0
            || self.eyr == 0
            || self.hgt.is_empty()
            || self.hcl.is_empty()
            || self.ecl.is_empty()
            || self.pid.is_empty())
    }

    fn validate_part2(&self) -> bool {
        if !self.validate_part1() {
            return false;
        }
        if self.byr < 1920 || self.byr > 2002 {
            return false;
        }
        if self.iyr < 2010 || self.iyr > 2020 {
            return false;
        }
        if self.eyr < 2020 || self.eyr > 2030 {
            return false;
        }
        if self.hgt.contains("cm") {
            if let Ok(h) = self.hgt[..self.hgt.len() - 2].parse::<i16>() {
                if !(150..=193).contains(&h) {
                    return false;
                }
            }
        } else if self.hgt.contains("in") {
            if let Ok(h) = self.hgt[..self.hgt.len() - 2].parse::<i16>() {
                if !(59..=76).contains(&h) {
                    return false;
                }
            }
        } else {
            return false;
        }
        if !Regex::new(r"^#[\da-f]{6}$")
            .unwrap()
            .is_match(self.hcl.as_str())
        {
            return false;
        }
        if !VALID_ECL.contains(&self.ecl.as_str()) {
            return false;
        }
        if !Regex::new(r"(^\d{9}$)")
            .unwrap()
            .is_match(self.pid.as_str())
        {
            return false;
        }

        true
    }
}

pub struct Day4 {
    passports: Vec<Passport>,
}

impl Day4 {
    fn solve_part1(&self) -> i64 {
        let mut num_valid = 0;
        for passport in &self.passports {
            if passport.validate_part1() {
                num_valid += 1;
            }
        }
        num_valid
    }

    fn solve_part2(&self) -> i64 {
        let mut num_valid = 0;
        for passport in &self.passports {
            if passport.validate_part2() {
                num_valid += 1;
            }
        }
        num_valid
    }
}

impl Solver for Day4 {
    fn new(lines: impl Iterator<Item = String>) -> Self {
        let mut passports = Vec::new();
        let mut fields = Vec::new();
        for line in lines {
            if line.is_empty() {
                passports.push(Passport::parse(fields.into_iter()));
                fields = Vec::new();
            }
            fields.append(
                line.split(' ')
                    .map(|l| l.to_owned())
                    .collect::<Vec<_>>()
                    .as_mut(),
            );
        }
        passports.push(Passport::parse(fields.into_iter()));
        Day4 { passports }
    }

    fn solve(&mut self) -> (i64, i64) {
        (self.solve_part1(), self.solve_part2())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use indoc::indoc;

    const INPUT_PART1: &str = indoc! {"
        ecl:gry pid:860033327 eyr:2020 hcl:#fffffd
        byr:1937 iyr:2017 cid:147 hgt:183cm

        iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884
        hcl:#cfa07d byr:1929

        hcl:#ae17e1 iyr:2013
        eyr:2024
        ecl:brn pid:760753108 byr:1931
        hgt:179cm

        hcl:#cfa07d eyr:2025 pid:166559648
        iyr:2011 ecl:brn hgt:59in
    "};

    #[test]
    fn part1() {
        let day4 = Day4::new(INPUT_PART1.lines().map(|l| l.to_owned()));
        assert_eq!(day4.solve_part1(), 2);
    }

    const INPUT_PART2: &str = indoc! {"
        eyr:1972 cid:100
        hcl:#18171d ecl:amb hgt:170 pid:186cm iyr:2018 byr:1926

        iyr:2019
        hcl:#602927 eyr:1967 hgt:170cm
        ecl:grn pid:012533040 byr:1946

        hcl:dab227 iyr:2012
        ecl:brn hgt:182cm pid:021572410 eyr:2020 byr:1992 cid:277

        hgt:59cm ecl:zzz
        eyr:2038 hcl:74454a iyr:2023
        pid:3556412378 byr:2007

        pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:1980
        hcl:#623a2f

        eyr:2029 ecl:blu cid:129 byr:1989
        iyr:2014 pid:896056539 hcl:#a97842 hgt:165cm

        hcl:#888785
        hgt:164cm byr:2001 iyr:2015 cid:88
        pid:545766238 ecl:hzl
        eyr:2022

        iyr:2010 hgt:158cm hcl:#b6652a ecl:blu byr:1944 eyr:2021 pid:093154719
    "};

    #[test]
    fn part2() {
        let day4 = Day4::new(INPUT_PART2.lines().map(|l| l.to_owned()));
        assert_eq!(day4.solve_part2(), 4);
    }
}
