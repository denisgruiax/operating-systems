use futures_util::{SinkExt, StreamExt};
use rand::{Rng, rngs::ThreadRng};
use std::{thread, time::Duration};
use tokio::net::TcpStream;
use tokio_tungstenite::{MaybeTlsStream, WebSocketStream, connect_async, tungstenite::Message};

#[tokio::main]
async fn main() {
    let mut ws_stream = connect_to_server("ws://127.0.0.1:8080").await;
    let mut rng = rand::rng();

    loop {
        send_message(&mut ws_stream, &mut rng).await;

        if let Some(message) = ws_stream.next().await {
            println!(
                "Received from server: {}",
                message.expect("Failed to unwrap the message from server.")
            );
        }

        thread::sleep(Duration::from_millis(3000));
    }
}

async fn connect_to_server(url: &str) -> WebSocketStream<MaybeTlsStream<TcpStream>> {
    let (ws_stream, _) = connect_async(url).await.expect("Failed to connect");

    println!("Connected to Websocket server.");

    ws_stream
}

async fn send_message(
    ws_stream: &mut WebSocketStream<MaybeTlsStream<TcpStream>>,
    rng: &mut ThreadRng,
) {
    let number = Message::from(rng.random_range(0..120).to_string());
    println!("Sending to server: {}", number);
    ws_stream
        .send(number)
        .await
        .expect("Failed to send message to server.");
}
