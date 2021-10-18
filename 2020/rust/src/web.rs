use reqwest::blocking::Client;
use reqwest::cookie::Jar;
use std::fs;
use std::path::PathBuf;
use std::sync::Arc;

const SESSION_FILE: &str = ".session";
const CACHE_DIR: &str = ".aoc_cache";

pub struct AocClient {
    client: Client,
}

impl AocClient {
    pub fn new() -> anyhow::Result<Self> {
        let session = fs::read_to_string(SESSION_FILE)?;
        let jar = Jar::default();
        jar.add_cookie_str(
            &format!("session={}; Domain=adventofcode.com", session),
            &"https://adventofcode.com".parse().unwrap(),
        );
        let client = Client::builder().cookie_provider(Arc::new(jar)).build()?;
        Ok(Self { client })
    }

    pub fn load_input(&self, year: u32, day: u32) -> anyhow::Result<PathBuf> {
        let file = PathBuf::from(format!("{}/{}_{}.txt", CACHE_DIR, year, day));
        if !file.exists() {
            if !PathBuf::from(CACHE_DIR).is_dir() {
                fs::create_dir(CACHE_DIR)?;
            }
            let request = self
                .client
                .get(format!(
                    "https://adventofcode.com/{}/day/{}/input",
                    year, day
                ))
                .build()?;
            let input = self.client.execute(request)?;
            fs::write(&file, input.bytes()?)?;
        }
        Ok(file)
    }
}
