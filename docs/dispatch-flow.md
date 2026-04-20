# Dispatch Flow

This document describes the optional common routing layer. It is not the primary implementation path for HTTP.

## Request Model

The caller sends a structured dispatch request instead of raw packet bytes.

Conceptually the request contains:

- protocol identifier
- protocol-specific payload
- optional metadata

Example idea:

- protocol: HTTP
- payload: HTTP request data
- metadata: trace or caller context

## Flow

1. The caller creates a `DispatchRequest`.
2. `Dispatcher` checks envelope-level validity.
3. `Dispatcher` asks `HandlerRegistry` for the component bound to the request protocol.
4. The resolved protocol component validates the protocol-specific payload.
5. The protocol component performs serialization, network I/O, parsing, and protocol-specific processing.
6. The protocol component returns a `DispatchResult`.
7. The dispatcher returns that result to the caller.

For HTTP specifically, direct use of `HttpClient` is expected to be the simpler path while the project is learning raw sockets.

## Validation Split

Validation should be split by level.

### Dispatcher validation

The dispatcher validates only request-envelope concerns:

- protocol field exists
- payload exists
- component is registered

### Protocol validation

Each protocol component validates its own protocol contract:

- required fields
- allowed field values
- field shape and consistency
- protocol-specific semantics

This keeps protocol rules and wire details out of the core dispatch layer.

## Result Model

The result returned to the caller should be standardized across protocols.

Expected concerns:

- success or failure
- protocol
- output data
- error details
- status or error category

The caller should not need different control flow for every protocol just to interpret success or failure.

## Error Categories

Useful error categories for the framework:

- unsupported protocol
- invalid request envelope
- invalid protocol payload
- protocol execution failure
- network I/O failure
- internal system failure

## Why There Is No Protocol Detection Layer

We explicitly removed protocol detection because the caller already knows the protocol and supplies it.

So this project is a protocol dispatch system, not a packet classification system.

It is also acceptable for callers to bypass this layer and call a protocol client directly when they do not need cross-protocol routing.
