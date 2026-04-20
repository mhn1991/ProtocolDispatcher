# WebSocket Client Design

## Why It Comes Later

WebSocket should come after the raw-socket HTTP client path is working, because the opening handshake is HTTP-shaped and the session is more stateful than plain REST calls.

## Key Difference From HTTP

HTTP is usually request/response and commonly treated as stateless per request.

WebSocket starts with an HTTP Upgrade handshake, but after that it becomes a long-lived, stateful message stream.

Because of that, WebSocket should not be modeled as just another HTTP payload shape.

## Architectural Split

Recommended components:

- `WebSocketHandshake`
- `WebSocketSession`
- `WebSocketClient`
- `WebSocketValidator`

The important point is responsibility separation, not the exact name.

## Responsibilities

### Handshake Handling

The client must handle the HTTP Upgrade boundary explicitly.

The handshake path is responsible for:

- building the upgrade request
- validating the upgrade response
- creating the session object

### Session

`WebSocketSession` owns the live connection after the upgrade.

Session concerns include:

- connection lifecycle
- read/write loop
- connection state
- close behavior
- ping/pong or heartbeat concerns

### Client Flow

Once a session is established, individual messages can be sent, received, and interpreted according to application rules.

This remains separate from the optional core dispatch layer that routes by top-level protocol.

## Boundary Rule

Do not collapse HTTP and WebSocket into one component just because the handshake starts with HTTP.

Use HTTP for:

- request/response dispatch

Use WebSocket for:

- long-lived session management
- message flow after the handshake succeeds

## Why WebSocket Comes Before FIX

WebSocket introduces state, lifecycle, and continuous communication. That is valuable experience before implementing FIX, which has even stricter session behavior.
