use once_cell::sync::Lazy;
use serde::Deserialize;

#[derive(Deserialize)]
pub struct Config {
    pub menu: Interactive,
    pub pce: Interactive,
    pub cl: Interactive,
    pub rcce: Interactive,
}

#[derive(Deserialize)]
pub struct Interactive {
    pub display: String,
    pub options: String,
}

pub static CONFIG: Lazy<Config> = Lazy::new(|| {
    let exe_dir = std::env::current_exe()
        .expect("failed to get exe path")
        .parent()
        .unwrap()
        .to_path_buf();
    let config_path = exe_dir.join("config.toml");
    let config_str = std::fs::read_to_string(config_path).expect("failed");
    toml::from_str(&config_str).expect("failed to parse config.toml")
});
