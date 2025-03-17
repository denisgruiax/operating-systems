use std::thread;
use std::sync::mpsc;
use std::time::Duration;

fn main() {
    let (tx, rx) = mpsc::channel();

    thread::spawn(move || {
        thread::sleep(Duration::from_secs(2));
        tx.send(String::from("Hi from second thread")).unwrap();
    });
    
    loop {
        match rx.try_recv() {
            Ok(value) => println!("Received: {}", value),
            Err(mpsc::TryRecvError::Empty) => {
                println!("No messages yet...");
                thread::sleep(Duration::from_millis(500));
            }
            Err(mpsc::TryRecvError::Disconnected) => {
                println!("Sender disconnected, exiting.");
                break;
            }
        }
    }
}

/*
    Output:

    No messages yet...
    No messages yet...
    No messages yet...
    No messages yet...
    Received: Hi from second thread
    Sender disconnected, exiting.
*/