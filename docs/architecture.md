# Architecture

## Goal

ProtocolDispatcher is a dispatch framework for structured protocol requests.

The caller already knows the protocol and supplies:

- the protocol identifier
- the protocol-specific request data
- optional metadata

This means the system is not responsible for protocol detection from raw bytes in the current design. Its job is to route a validated request to the correct handler and return a normalized result.

## Core Design Principle

Keep the dispatcher thin.

- The caller chooses the protocol.
- The dispatcher chooses the handler.
- The handler owns protocol rules.

The dispatcher must not become the place where HTTP, WebSocket, or future FIX logic accumulates.

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
- resolve the correct handler
- invoke the handler
- return a unified result

Core must not know protocol-specific field names or protocol semantics.

### Protocol Layers

Each protocol owns its own request/response models, validation rules, and handling logic.

Current planned protocol areas:

- HTTP
- WebSocket
- FIX later

### Transport Layer

Transport adapters integrate external libraries such as Boost.Beast.

Rule:

- Boost.Beast types should stay inside `transport/` and protocol adapters as much as possible.
- Core interfaces should remain project-owned, not library-owned.

This keeps the architecture stable if transport details change later.

## Project Layout

The codebase is organized by responsibility:

- `include/ProtocolDispatcher/core/`
- `include/ProtocolDispatcher/common/`
- `include/ProtocolDispatcher/protocols/http/`
- `include/ProtocolDispatcher/protocols/websocket/`
- `include/ProtocolDispatcher/protocols/fix/`
- `include/ProtocolDispatcher/transport/`
- `src/...` mirrors implementation
- `tests/` mirrors source areas
- `docs/` stores design notes

Tests stay under top-level `tests/`, not inside protocol source directories. The test tree mirrors the production structure.

## Phased Development

Recommended order:

1. Build the dispatch framework.
2. Add HTTP using Boost.Beast.
3. Add WebSocket using Boost.Beast.
4. Add FIX later after the system patterns are stable.

This order gives experience with both request/response and session-oriented flows before implementing a stricter protocol like FIX.
