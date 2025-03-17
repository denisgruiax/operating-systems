use std::sync::mpsc::{self, SendError};
use std::thread;

fn main() {
    let (tx, rx) = mpsc::channel();

    let handle = thread::spawn(move || {
        tx.send(String::from("Hi from second thread")).unwrap();
        Ok(())
    });

    let status: Result<(), SendError<String>> = handle.join().unwrap();

    println!(
        "Message: {}, Finishing status: {:?}",
        rx.recv().unwrap(),
        status
    );
}

/*
    Output:

    Message: Hi from second thread, Finishing status: Ok(())
*/
