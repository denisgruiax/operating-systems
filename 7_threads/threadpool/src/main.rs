use core::result::Result;
use std::{io::{BufRead, BufReader}, net::{TcpListener, TcpStream}};

fn main() -> Result<(), std::io::Error> {
    let listener = TcpListener::bind("127.0.0.1:8080")?;

    listener
        .incoming()
        .into_iter()
        .for_each(|stream| handle_connection(stream.unwrap()));

    Ok(())
}

fn handle_connection(mut stream: TcpStream){
    let buffer_reader = BufReader::new(&stream);
    let http_request:Vec<_> = buffer_reader
        .lines()
        .map(|result| result.unwrap())
        .take_while(|line|!line.is_empty())
        .collect();

    println!("Request: {http_request:#?}");
}