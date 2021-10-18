use std::collections::HashMap;
use std::hash::Hash;

#[macro_export]
macro_rules! post_inc {
    ($x:expr) => {{
        let t = $x;
        $x += 1;
        t
    }};
}

#[macro_export]
macro_rules! add_solutions {
	($($n: literal => $m:ident :: $t:ident),+ $(,)*) => {
		$(
		mod $m;
		use $m::$t;
		)+
		pub fn get_solution(day: &str, lines: impl Iterator<Item = String>) -> Option<(i64, i64)> {
            use crate::solver::Solver;
			match day {
				$($n => Some($t::new(lines).solve()),)+
				_ => None,
			}
		}
	};
}

pub fn push_key<K, V>(map: &mut HashMap<K, Vec<V>>, key: K, value: V)
where
    K: Eq + Hash,
{
    match map.get_mut(&key) {
        Some(v) => {
            v.push(value);
        }
        None => {
            map.insert(key, vec![value]);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn push_key_test() {
        let mut m = HashMap::new();
        m.insert("foo", vec!["foo"]);

        push_key(&mut m, "foo", "bar");
        push_key(&mut m, "bar", "baz");

        assert_eq!(m.get("foo"), Some(&vec!["foo", "bar"]));
        assert_eq!(m.get("bar"), Some(&vec!["baz"]));
    }
}
