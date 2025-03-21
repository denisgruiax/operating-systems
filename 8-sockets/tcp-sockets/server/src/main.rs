use std::io::{Read, Write};
use std::net::{TcpListener, TcpStream};

use rand::Rng;

fn main() {
    let listener = TcpListener::bind("127.0.0.1:8080").unwrap();
    println!("Server running on 127.0.0.1:8080 ⚡️");

    listener.incoming().for_each(|s| handle_client(s.unwrap()));
}

fn handle_client(mut stream: TcpStream) {
    let mut buffer: [u8; 128] = [0; 128];

    if let Ok(bytes_read) = stream.read(&mut buffer) {
        println!(
            "Received {} bytes from the client: {:?}",
            bytes_read,
            String::from_utf8_lossy(&buffer[..bytes_read])
        );

        let mut rng = rand::rng();
        let response = rng.random_range(0..=100);

        stream
            .write(format!("The random number is: {}", response).as_bytes())
            .unwrap();
    };
}

/*
    Server reads full message in one go because TCP buffering holds everything until read() is called.
*/
