use std::{env, net::SocketAddr};//io::Error,

use futures_util::{future, StreamExt, TryStreamExt};
use log::*;
use tokio::net::{TcpListener, TcpStream};
use tokio_tungstenite::tungstenite::{Error,Result};
use serde_json::{Value};
mod message_parser;

#[tokio::main]
async fn main() -> Result<(),Error> {
    let _ = env_logger::try_init();
    let addr = env::args().nth(1).unwrap_or_else( || "127.0.0.1:8080".to_string());

    let try_socket = TcpListener::bind(&addr).await;
    let listener = try_socket.expect("Failed to bind");

    while let Ok((stream, _)) = listener.accept().await{
        let peer = stream.peer_addr().expect("Connected streams should have a peer address");
        tokio::spawn(accept_connection(peer, stream));
    }

    Ok(())
}

async fn accept_connection(peer:SocketAddr, stream: TcpStream){
    if let Err(e) = handle_connection(peer, stream).await {
        match e {
            Error::ConnectionClosed |Error::Protocol(_) |Error::Utf8 => (),
            err => error!("Error processing connection: {}",err),
        }
    }

    //let (write,read) = ws_stream.split();

    /*
    read.try_filter(|msg| future::ready(msg.is_text() || msg.is_binary()))
        .forward(write)
        .await
        .expect("Failed to forward messages")
     */
    
}
async fn handle_connection(peer: SocketAddr, stream: TcpStream) -> Result<()> {
    let addr = stream.peer_addr().expect("connected streams should have a peer address");
    info!("Peer address: {}", addr);
    let mut ws_stream = tokio_tungstenite::accept_async(stream)
    .await.expect("Error during the websocket handshake occured");
    info!("New Websocket connection:{}",addr);
    
    while let Some(msg) = ws_stream.next().await {
        let msg = msg?;
        if msg.is_text() {
            //let jsonText = msg.to_text()?;
            //let jsonResult: serde_json::Result<String> = serde_json::from_str(jsonText);
            //let json = jsonResult.unwrap_or("".to_string());

            //let json = jsonResult?;

            let command_result = msg.to_text();
            let command = command_result.unwrap_or("");
            message_parser::parse(command);
        }
    }
    Ok(())
}