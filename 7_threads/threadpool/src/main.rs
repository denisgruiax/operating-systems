use core::result::Result;
use std::{
    fs,
    io::{BufRead, BufReader, Write},
    net::{TcpListener, TcpStream},
};

fn main() -> Result<(), std::io::Error> {
    let listener = TcpListener::bind("127.0.0.1:8080")?;

    listener
        .incoming()
        .into_iter()
        .for_each(|stream| handle_connection(stream.unwrap()).unwrap());

    Ok(())
}

fn handle_connection(mut stream: TcpStream) -> Result<(), std::io::Error> {
    let buffer_reader = BufReader::new(&stream);
    let request_line = buffer_reader.lines().next().unwrap().unwrap();

    let (status_line, filename) = if request_line == "GET / HTTP/1.1" {
        ("HTTP/1.1 200 OK", "hello.html")
    } else {
        ("HTTP/1.1 404 NOT FOUND", "404.html")
    };

    let contents = fs::read_to_string(filename)?;
    let length = contents.len();
    let response = format!("{status_line}\r\nContent-Length: {length}\r\n\r\n{contents}");

    stream.write_all(response.as_bytes()).unwrap();

    Ok(())
}
