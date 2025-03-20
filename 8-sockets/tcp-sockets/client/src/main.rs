use std::net::TcpStream;
use std::io::{Write, Read};

fn main() {
    let mut stream = TcpStream::connect("127.0.0.1:8080").unwrap();
    stream.write(b"abcdefghi").unwrap();

    let mut buffer = [0,128];
    stream.read(&mut buffer).unwrap();
    
    println!("Server response: {}", String::from_utf8_lossy(&buffer));
}
