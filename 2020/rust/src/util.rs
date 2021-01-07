#[macro_export]
macro_rules! post_inc {
	($x:expr) => {{
		let t = $x;
		$x += 1;
		t
	}};
}
