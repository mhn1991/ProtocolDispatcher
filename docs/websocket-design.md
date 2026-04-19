# WebSocket Design

## Beast Support

Boost.Beast supports WebSocket and is appropriate for this project.

That makes it a good fit after HTTP because it keeps the same general library family while introducing a more stateful communication model.

## Key Difference From HTTP

HTTP is usually request/response and commonly treated as stateless per request.

WebSocket starts with an HTTP Upgrade handshake, but after that it becomes a long-lived, stateful message stream.

Because of that, WebSocket should not be modeled as just another HTTP payload shape.

## Architectural Split

Recommended components:

- `WebSocketUpgradeHandler`
- `WebSocketSession`
- `WebSocketMessageDispatcher`
- `WebSocketValidator`

In the current file tree, the equivalent planned components are represented by:

- `WebSocketHandler`
- `WebSocketSession`
- `WebSocketValidator`

The important point is responsibility separation, not the exact name.

## Responsibilities

### Upgrade Handling

The system must handle the HTTP Upgrade boundary explicitly.

The upgrade path is responsible for:

- recognizing an upgrade request
- performing the WebSocket handshake
- creating the session object

### Session

`WebSocketSession` owns the live connection after the upgrade.

Session concerns include:

- connection lifecycle
- read/write loop
- connection state
- close behavior
- ping/pong or heartbeat concerns

### Message Dispatch

Once a session is established, individual messages can be routed or interpreted according to application rules.

This is separate from the core protocol dispatcher that routes by top-level protocol.

## Boundary Rule

Do not collapse HTTP and WebSocket into one handler just because the handshake starts with HTTP.

Use HTTP for:

- request/response dispatch

Use WebSocket for:

- long-lived session management
- message flow after upgrade

## Why WebSocket Comes Before FIX

WebSocket introduces state, lifecycle, and continuous communication. That is valuable experience before implementing FIX, which has even stricter session behavior.
