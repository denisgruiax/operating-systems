use std::io::{Read, Write};
use std::net::TcpStream;

fn main() {
    let mut stream = TcpStream::connect("127.0.0.1:8080").unwrap();
    stream.write(b"Hello server!").unwrap();

    let mut response = String::new();
    let mut buffer = [0; 128];

    while let Ok(bytes_read) = stream.read(&mut buffer) {
        if bytes_read == 0 {
            break;
        }
        response.push_str(&String::from_utf8_lossy(&buffer[..bytes_read]));
    }

    println!("response: {}\n", response);
}

/*
    Client might need to loop because TCP may deliver the response in multiple parts.
 */