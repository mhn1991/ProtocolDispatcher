# ProtocolDispatcher

ProtocolDispatcher is a C++ project for routing structured protocol requests to protocol-specific handlers.

## Overview

The current design assumes the caller already knows the protocol. The caller sends:

- a protocol identifier
- protocol-specific request data
- optional metadata

The dispatcher does not detect protocols from raw packets in this phase. Its responsibility is to route the request to the correct handler and return a normalized result.

Core rule:

- the caller chooses the protocol
- the dispatcher chooses the handler
- the handler owns protocol rules

## Current Scope

The planned implementation order is:

1. dispatch framework
2. HTTP support using Boost.Beast
3. WebSocket support using Boost.Beast
4. FIX later, after the framework and session-oriented protocols are understood

## Architecture Summary

The codebase is split by responsibility:

- `core/` for protocol-agnostic dispatch components
- `protocols/http/` for HTTP models, validation, and handling
- `protocols/websocket/` for upgrade, session, and message flow concerns
- `transport/` for Boost.Beast integration
- `tests/` for mirrored test structure
- `docs/` for design notes

Important boundary:

- Boost.Beast should stay in transport/protocol adapter layers and should not leak into the whole codebase.

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
- `docs/http-design.md`
- `docs/websocket-design.md`
- `docs/fix-notes.md`

## Status

The repository currently contains the initial project skeleton and design documentation. Production logic has not been implemented yet.
