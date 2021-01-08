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
		fn get_solution(day: &str, lines: impl Iterator<Item = String>) -> Option<(i64, i64)> {
			match day {
				$($n => Some($t::new(lines).solve()),)+
				_ => None,
			}
		}
	};
}
