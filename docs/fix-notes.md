# FIX Notes

## Planned Timing

FIX is intentionally postponed until after HTTP and WebSocket are understood and implemented.

Recommended order:

1. HTTP
2. decide whether the dispatch layer is useful
3. WebSocket
4. FIX

This keeps the project complexity under control.

## Why FIX Is Later

FIX is not just another payload format. It is a stateful financial session protocol with strict behavioral requirements.

If implemented manually, the system becomes responsible for:

- session lifecycle
- sequence numbers
- resend logic
- heartbeats and test requests
- logon and logout behavior
- checksum and body length validation
- recovery after disconnect
- strict tag and field semantics

That makes it a much riskier first protocol than HTTP or WebSocket.

## Planned FIX Subsystem Shape

When FIX is added, it should be treated as its own deeper subsystem behind either the common dispatch platform or a direct client API, depending on what proves cleaner after HTTP and WebSocket.

Likely components:

- `FixMessage`
- `FixSession`
- `FixSessionManager`
- `FixParser`
- `FixSerializer`
- `FixClient`
- `FixStore`
- `FixValidator`

## Architectural Rule

FIX should plug into the top-level routing layer only if that layer still adds real value. Its internal session model should stay isolated from HTTP and WebSocket implementation details.

That prevents the dispatcher from becoming FIX-aware too early.
