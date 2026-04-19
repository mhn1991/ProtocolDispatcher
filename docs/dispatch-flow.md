# Dispatch Flow

## Request Model

The caller sends a structured dispatch request instead of raw packet bytes.

Conceptually the request contains:

- protocol identifier
- protocol-specific payload
- optional metadata

Example idea:

- protocol: HTTP
- payload: HTTP-shaped data
- metadata: trace or caller context

## Flow

1. The caller creates a `DispatchRequest`.
2. `Dispatcher` checks envelope-level validity.
3. `Dispatcher` asks `HandlerRegistry` for the handler bound to the request protocol.
4. The resolved handler validates the protocol-specific payload.
5. The handler executes protocol-specific processing.
6. The handler returns a `DispatchResult`.
7. The dispatcher returns that result to the caller.

## Validation Split

Validation should be split by level.

### Dispatcher validation

The dispatcher validates only request-envelope concerns:

- protocol field exists
- payload exists
- handler is registered

### Handler validation

Each handler validates its own protocol contract:

- required fields
- allowed field values
- field shape and consistency
- protocol-specific semantics

This keeps protocol rules out of the core dispatch layer.

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
- handler execution failure
- internal system failure

## Why There Is No Protocol Detection Layer

We explicitly removed protocol detection because the caller already knows the protocol and supplies it.

So this project is a protocol dispatch system, not a packet classification system.
