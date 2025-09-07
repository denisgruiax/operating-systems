use bytes::Bytes;
use std::collections::HashMap;
use std::net::TcpStream;
use std::os::unix::process;
use std::sync::{Arc, Mutex};
use tokio::net::TcpListener;

static ADDRESS: &'static str = "127.0.0.1:6479";

type DB = Arc<Mutex<HashMap<String, Bytes>>>;

#[tokio::main]
async fn main() {
    let listener = TcpListener::bind(ADDRESS).await.unwrap();

    println!("TcpListener is listening on: {}", ADDRESS);

    let db: DB = Arc::new(Mutex::new(HashMap::new()));

    loop {
        let (socket, _) = listener.accept().await.unwrap();

        let db = db.clone();
        println!("Accepted new connection");

        tokio::spawn(async move {
            process(socket, db).await;
        });
    }
}

async fn process(socket: TcpStream, db: DB) {}
