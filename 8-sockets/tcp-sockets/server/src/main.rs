use std::io::{Read, Write};
use std::net::{TcpListener, TcpStream};

fn main() {
    let listener = TcpListener::bind("127.0.0.1:8080").unwrap();
    println!("Server running on 127.0.0.1:8080 ⚡️");

    listener.incoming().for_each(|s| handle_client(s.unwrap()));
}

fn handle_client(mut stream: TcpStream) {
    let mut buffer: [u8; 128] = [0; 128];

    stream.read(&mut buffer).iter().for_each(|bytes_size| {
        println!(
            "Received {} bytes from the client: {:?}",
            bytes_size,
            String::from_utf8_lossy(&buffer[..*bytes_size])
        );

        stream.write("Message received!".as_bytes()).unwrap();
    });
}

/*
    Server reads full message in one go because TCP buffering holds everything until read() is called.
*/