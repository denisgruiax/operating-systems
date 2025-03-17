use std::thread;
use std::time::Duration;

fn main() {
    let handle = thread::spawn(|| {
        for i in 1..=10 {
            println!("Second thread is printing number: {}", i);
            thread::sleep(Duration::from_millis(1));
        }
    });

    for i in 1..=5 {
        println!("The initial thread is printing number: {}", i);
        thread::sleep(Duration::from_micros(5000));
    }

    handle.join().unwrap();
}

/*
    Output:

    The initial thread is printing number: 1
    Second thread is printing number: 1
    Second thread is printing number: 2
    Second thread is printing number: 3
    Second thread is printing number: 4
    Second thread is printing number: 5
    The initial thread is printing number: 2
    Second thread is printing number: 6
    Second thread is printing number: 7
    Second thread is printing number: 8
    Second thread is printing number: 9
    Second thread is printing number: 10
    The initial thread is printing number: 3
    The initial thread is printing number: 4
    The initial thread is printing number: 5
*/