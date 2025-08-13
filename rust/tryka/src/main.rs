mod config;
pub use crate::config::CONFIG;
use std::io::{self, BufRead, Write};

#[derive(PartialEq)]
enum State {
    ENTRY,
    EXIT,
    ERROR,
    PCE,
    CL,
    RCCE,
}
use State::*;

fn clear_screen() {
    for _ in 0..100 {
        println!();
    }
}

fn prompt_wait() {
    print!("\n(press enter to continue)");
    io::stdout().flush().unwrap();
    io::stdin().lock().lines().next();
}

fn int_error() -> State {
    clear_screen();
    print!("\nErroneous input, going back to entry.\n");
    prompt_wait();
    ENTRY
}

fn int_entry() -> State {
    clear_screen();
    print!("{}{}", CONFIG.menu.display, CONFIG.menu.options);
    io::stdout().flush().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    match input.trim() {
        "1" => PCE,
        "2" => CL,
        "3" => RCCE,
        "x" => EXIT,
        _ => ERROR,
    }
}

fn int_pce() -> State {
    clear_screen();
    print!("{}{}", CONFIG.pce.display, CONFIG.pce.options);
    io::stdout().flush().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    match input.trim() {
        "1" => ENTRY,
        "2" => ENTRY,
        "3" => ENTRY,
        "4" => ENTRY,
        "5" => ENTRY,
        "x" => ENTRY,
        _ => ERROR,
    }
}

fn int_cl() -> State {
    clear_screen();
    print!("{}{}", CONFIG.cl.display, CONFIG.cl.options);
    io::stdout().flush().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    match input.trim() {
        "1" => ENTRY,
        "2" => ENTRY,
        "3" => ENTRY,
        "x" => ENTRY,
        _ => ERROR,
    }
}

fn int_rcce() -> State {
    clear_screen();
    print!("{}{}", CONFIG.rcce.display, CONFIG.rcce.options);
    io::stdout().flush().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    match input.trim() {
        "1" => ENTRY,
        "2" => ENTRY,
        "3" => ENTRY,
        "4" => ENTRY,
        "x" => ENTRY,
        _ => ERROR,
    }
}

fn main() {
    let mut current_state = ENTRY;
    while current_state != EXIT {
        current_state = match current_state {
            ENTRY => int_entry(),
            ERROR => int_error(),
            PCE => int_pce(),
            CL => int_cl(),
            RCCE => int_rcce(),
            EXIT => EXIT,
        };
    }
    print!("\nExited state machine.\n");
}
