# Architecture

## Goal

ProtocolDispatcher is an outbound protocol client library with an optional dispatch layer for routing structured requests.

The caller already knows the protocol and supplies:

- the protocol identifier
- the protocol-specific request data
- optional metadata

This means the system is not responsible for protocol detection from raw bytes in the current design. Its primary job is to execute a protocol request correctly. If the dispatch layer is retained, its secondary job is to route a validated request to the correct protocol component and return a normalized result.

## Core Design Principle

Keep protocol work close to the protocol and keep the dispatch layer thin.

- The caller chooses the protocol.
- The protocol component owns protocol rules and wire-level translation.
- The dispatcher, if present, only selects the protocol component and coordinates shared result handling.

The dispatch layer must not become the place where HTTP, WebSocket, or future FIX logic accumulates.

## Main Responsibilities

### Core

The core layer is protocol-agnostic and contains:

- `DispatchRequest`
- `DispatchResult`
- `Error`
- `Status`
- `IProtocolHandler`
- `Dispatcher`
- `HandlerRegistry`

Core responsibilities:

- accept a request envelope
- validate envelope-level data
- resolve the correct protocol component when routing is needed
- invoke it
- return a unified result when the caller wants a common abstraction

Core must not know protocol-specific field names, protocol semantics, or wire framing details.

### Protocol Layers

Each protocol owns its own request/response models, validation rules, serialization/parsing logic, and client behavior.

Current planned protocol areas:

- HTTP
- WebSocket
- FIX later

### Network Layer

The network layer owns low-level socket concerns for outbound connections.

Rule:

- socket and connection primitives should stay inside `net/`.
- HTTP and WebSocket wire logic should stay inside their protocol directories.
- Core interfaces should remain project-owned if they continue to exist.

This keeps the architecture stable if connection details change later.

## Preferred Call Path

The preferred path for the current strategy is protocol-first, not dispatcher-first.

For HTTP:

1. The caller creates an `HttpRequest`.
2. `HttpValidator` checks protocol-specific correctness.
3. `HttpSerializer` builds the wire-format request bytes.
4. `net::TcpClient` performs connect, send, and receive.
5. `HttpParser` converts response bytes into `HttpResponse`.

If a common entry point is still useful later, `Dispatcher` can wrap this flow. It should not replace it as the primary mental model.

## Project Layout

The codebase is organized by responsibility:

- `include/ProtocolDispatcher/core/`
- `include/ProtocolDispatcher/common/`
- `include/ProtocolDispatcher/net/`
- `include/ProtocolDispatcher/protocols/http/`
- `include/ProtocolDispatcher/protocols/websocket/`
- `include/ProtocolDispatcher/protocols/fix/`
- `src/...` mirrors implementation
- `tests/` mirrors source areas
- `docs/` stores design notes

Tests stay under top-level `tests/`, not inside protocol source directories. The test tree mirrors the production structure.

## Phased Development

Recommended order:

1. Add an HTTP client using raw TCP sockets.
2. Evaluate whether the dispatch abstractions are helping or adding ceremony.
3. Add a WebSocket client after the HTTP path is stable.
4. Add FIX later after the system patterns are stable.

This order gives experience with both request/response and session-oriented flows before implementing a stricter protocol like FIX.
