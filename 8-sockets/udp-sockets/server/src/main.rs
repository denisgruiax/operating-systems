use std::net::UdpSocket;

fn main() -> std::io::Result<()> {
    let mut buffer = [0; 128];
    let socket = UdpSocket::bind("127.0.0.1:8080")?;

    println!("UDP server is listening on 127.0.0.1:8080");

    std::iter::repeat_with(|| {
        socket
            .recv_from(&mut buffer)
            .map(|(amt, src)| (amt, src, buffer))
    })
    .map_while(Result::ok)
    .try_for_each(|(amt, src, buffer)| {
        println!(
            "Received {} from {}",
            String::from_utf8_lossy(&buffer[..amt]),
            src
        );

        Ok::<(), std::io::Error>(())
    })?;

    Ok(())
}
