use core::result::Result;
use std::net::TcpListener;

fn main() -> Result<(), std::io::Error> {
    let listener = TcpListener::bind("127.0.0.1:8080")?;

    listener
        .incoming()
        .into_iter()
        .for_each(|stream| println!("{:?}", stream));

    Ok(())
}
