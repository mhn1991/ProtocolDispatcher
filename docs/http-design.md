# HTTP Design

## Purpose

HTTP is the first concrete protocol to implement because it is easier to reason about than FIX and gives a good foundation for the dispatch architecture.

Boost.Beast will be used for HTTP integration.

## HTTP Scope In This Project

The caller provides an HTTP-shaped request object. This is above raw packet parsing.

The HTTP subsystem is responsible for:

- validating HTTP request data
- translating between project models and Beast types when needed
- handling HTTP request/response processing

## Recommended Request Shape

Do not model HTTP payload as generic `List<tuple>` collections everywhere.

That approach becomes weak because:

- tuple positions are ambiguous
- required fields are unclear
- validation becomes harder
- semantics get buried in conventions

Instead, HTTP should have a protocol-specific request contract with named fields.

Conceptually useful fields:

- method
- path
- headers
- query parameters
- body
- version

## Body Design Note

The HTTP body should not always be treated as key-value tuples.

HTTP body may be:

- raw text
- JSON
- form data
- binary content

So the body model should allow content plus content type, not just a list of pairs.

## Main HTTP Components

### `HttpRequestData`

Owns the project-level HTTP request contract.

### `HttpResponseData`

Owns the normalized HTTP response shape returned by the HTTP subsystem.

### `HttpValidator`

Validates HTTP-specific fields such as:

- required request members
- method validity
- header structure
- body consistency rules

### `HttpHandler`

Owns HTTP processing logic. It should:

- accept HTTP requests
- run HTTP-specific validation
- perform processing
- return a dispatch result

### `BeastHttpAdapter`

Encapsulates Boost.Beast integration and translation. This keeps Beast from leaking into the whole codebase.

## Boundary Rule

The core dispatcher must not know HTTP semantics.

Only the HTTP subsystem should understand:

- methods
- headers
- query parameters
- body representation
- status handling specific to HTTP
