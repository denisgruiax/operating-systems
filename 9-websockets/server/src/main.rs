use std::error::Error;

use futures::{SinkExt, StreamExt};
use tokio::net::{TcpListener, TcpSocket, TcpStream};
use tokio_tungstenite::{WebSocketStream, accept_async};
use tungstenite::{Message, Utf8Bytes};

#[tokio::main]
async fn main() {
    let listener = create_listener("127.0.0.1:8080").await;

    while let Ok((tcp_stream, _)) = listener.accept().await {
        tokio::spawn(async move {
            let ws_stream = accept_connection(tcp_stream).await;
            let (mut write, mut read) = ws_stream.split();

            println!("Client connected.");

            while let Some(message) = read.next().await {
                let message = calculate_response(message.expect("Failed to unwrap the message."));

                write.send(message).await.expect("Failed to send messsage.");
            }
        });
    }
}

async fn create_listener(address: &str) -> TcpListener {
    TcpListener::bind(address)
        .await
        .expect("Failed to bind to the given ip.")
}

async fn accept_connection(stream: TcpStream) -> WebSocketStream<TcpStream> {
    accept_async(stream).await.expect("Failed to accept data")
}

fn calculate_response(message: Message) -> Message {
    let number = message
        .to_text()
        .unwrap()
        .parse::<i32>()
        .map(|number| number * 2)
        .unwrap();

    tungstenite::Message::Text(Utf8Bytes::from(number.to_string()))
}
