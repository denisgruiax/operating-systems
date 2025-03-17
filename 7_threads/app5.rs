use std::sync::Arc;
use std::sync::Mutex;
use std::thread;

fn main() {
    let counter = Arc::new(Mutex::new(0));
    let mut threads = vec![];

    for _ in 1..=10 {
        let counter = Arc::clone(&counter);

        threads.push(thread::spawn(move || {
            *counter.lock().unwrap() += 1;
        }));
    }

    for t in threads {
        t.join().unwrap();
    }

    println!("Size of counter is: {}", *counter.lock().unwrap());
}

/*
    Output:

    Size of counter is: 10
*/
