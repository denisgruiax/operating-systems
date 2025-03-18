/*
    Write a C program consisting of a single process running 6 threads (including the initial one).
    The process creates an array of 5 characters, whose elements are initialized with '#'.
    There will be 5 "producer" threads in the process that will continuously fill in a random location in the array with one character each,
as follows: the first thread with the character 'A', the second with 'B' and so on up to 'E'.

    Each "producer" thread will count how many characters it has entered into the array;
    the first thread will terminate when it has entered 100,000 characters, the second 200,000 and so on.
    The main thread will continuously display the contents of the array until all the "producer" threads terminate,
at which point it will take over their state and terminate the process.
*/

use std::sync::Arc;
use std::sync::Mutex;
use std::thread;

fn main() {
    let table = Arc::new(Mutex::new(['#', '#', '#', '#', '#']));
    let mut handles = vec![];

    for id in 1..=5 as u8 {
        let table = Arc::clone(&table);
        let character = match_character(id);

        handles.push(thread::spawn(move || {
            let mut counter = 0;

            for _ in 1..=(id as u64 * 100_000) {
                let index: usize = rand::random_range(0..5);
                let mut table = table.lock().unwrap();

                table[index] = character;

                counter += 1;
            }

            counter
        }));
    }

    while !handles.iter().all(|handle| handle.is_finished()) {
        print_table(&table);
    }

    handles
        .into_iter()
        .map(|h| h.join().unwrap())
        .collect::<Vec<i32>>()
        .iter()
        .enumerate()
        .for_each(|(id, counter)| println!("Thread {} wrote {} characters", id + 1, counter));
}

fn print_table(table: &Arc<Mutex<[char; 5]>>) -> () {
    table.lock().unwrap().iter().for_each(|c| print!("{}", c));

    println!();
}

fn match_character(thread_id: u8) -> char {
    match thread_id {
        1 => 'A',
        2 => 'B',
        3 => 'C',
        4 => 'D',
        5 => 'E',
        _ => panic!("Wrong id have been given to the function"),
    }
}