# ProtocolDispatcher

ProtocolDispatcher is a C++ project for building outbound protocol clients with a thin optional dispatch layer on top.

## Overview

The current design assumes the caller already knows the protocol. The caller sends:

- a protocol identifier
- protocol-specific request data
- optional metadata

The current implementation strategy is to learn the wire-level mechanics directly instead of hiding them behind a higher-level networking library. For HTTP, the caller provides a structured request model, and the library is responsible for:

- validating the request
- serializing it into raw HTTP bytes
- sending it over a TCP socket
- receiving the raw response bytes
- parsing them back into a structured response

Design rule:

- the caller chooses the protocol
- the protocol module owns protocol semantics
- the optional dispatcher chooses the protocol component
- the protocol component owns protocol rules and wire translation

## Current Scope

The planned implementation order is:

1. raw-socket HTTP client support
2. decide whether the dispatch layer adds value on top of the client APIs
3. WebSocket client support after HTTP is stable
4. FIX later, after the framework and session-oriented protocols are understood

## Architecture Summary

The codebase is split by responsibility:

- `core/` for protocol-agnostic request routing abstractions, if the dispatch layer is kept
- `net/` for low-level socket and connection primitives
- `protocols/http/` for HTTP models, validation, serialization, parsing, and client flow
- `protocols/websocket/` for client-side handshake, session, and message flow concerns
- `tests/` for mirrored test structure
- `docs/` for design notes

Important boundaries:

- raw socket operations should stay inside `net/` and protocol-specific wire code should stay inside protocol modules.
- HTTP and WebSocket types should not leak low-level socket details into the public API.
- If the dispatch layer stays, it should remain a thin orchestration layer rather than the center of the design.

## Project Layout

```text
ProtocolDispatcher/
├── CMakeLists.txt
├── README.md
├── docs/
├── include/ProtocolDispatcher/
├── src/
├── tests/
├── examples/
└── scripts/
```

## Documentation

Detailed design notes are in:

- `docs/architecture.md`
- `docs/dispatch-flow.md`
- `docs/http-client-design.md`
- `docs/websocket-client-design.md`
- `docs/fix-notes.md`

## Status

The repository currently contains the updated skeleton and design notes for an outbound client-oriented implementation. Production networking logic is still placeholder-level.
