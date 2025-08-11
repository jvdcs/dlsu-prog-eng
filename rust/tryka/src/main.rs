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

fn int_entry() -> State {
    clear_screen();
    print!("{}", CONFIG.menu.display);
    io::stdout().flush().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    match input.trim() {
        "1" => State::PCE,
        "2" => State::CL,
        "3" => State::RCCE,
        "x" => State::EXIT,
        _ => State::ERROR,
    }
}

fn int_error() -> State {
    clear_screen();
    println!("\nErroneous input.");
    prompt_wait();
    State::ENTRY
}

fn int_pce() -> State {
    clear_screen();
    println!("{}", CONFIG.pce.display);
    prompt_wait();
    State::ENTRY
}

fn int_cl() -> State {
    clear_screen();
    println!("{}", CONFIG.cl.display);
    prompt_wait();
    State::ENTRY
}

fn int_rcce() -> State {
    clear_screen();
    println!("{}", CONFIG.rcce.display);
    prompt_wait();
    State::ENTRY
}

fn main() {
    let mut current_state = State::ENTRY;
    while current_state != State::EXIT {
        current_state = match current_state {
            State::ENTRY => int_entry(),
            State::ERROR => int_error(),
            State::PCE => int_pce(),
            State::CL => int_cl(),
            State::RCCE => int_rcce(),
            State::EXIT => State::EXIT, 
        };
    }
    println!("\nExited state machine.");
}
