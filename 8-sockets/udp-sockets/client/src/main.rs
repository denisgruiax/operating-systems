use std::net::UdpSocket;

fn main() -> std::io::Result<()> {
    let mut buffer = [0; 128];
    let socket = UdpSocket::bind("127.0.0.1:0")?;
    socket.connect("127.0.0.1:8080")?;

    socket.send("Hello UDP server".as_bytes())?;

    let amt = socket.recv(&mut buffer)?;
    
    println!("Received: {}", String::from_utf8_lossy(&buffer[..amt]));

    Ok(())
}
