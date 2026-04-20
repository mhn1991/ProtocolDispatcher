# HTTP Client Design

## Purpose

HTTP is the first concrete protocol to implement because it is easier to reason about than FIX and gives a good foundation for understanding socket programming and message framing.

The implementation goal is to use raw TCP sockets so the project exposes the mechanics of HTTP on the wire instead of hiding them behind a higher-level library.

## HTTP Scope In This Project

The caller provides an HTTP request object. The library then turns that model into raw bytes, sends them over a TCP connection, and parses the response bytes back into a structured response.

The HTTP subsystem is responsible for:

- validating HTTP request data
- serializing requests into HTTP wire format
- reading and parsing HTTP responses from the socket
- orchestrating the outbound request/response flow

## Recommended Request Shape

Do not model HTTP requests as generic `List<tuple>` collections everywhere.

That approach becomes weak because:

- tuple positions are ambiguous
- required fields are unclear
- validation becomes harder
- semantics get buried in conventions

Instead, HTTP should have a protocol-specific request contract with named fields.

Conceptually useful fields:

- method
- scheme
- host
- port
- path
- headers
- query parameters
- body

## Body Design Note

The HTTP body should not always be treated as key-value tuples.

HTTP body may be:

- raw text
- JSON
- form data
- binary content

So the body model should allow content plus content type, not just a list of pairs.

## Minimal Initial Scope

The initial implementation should stay deliberately small:

- HTTP/1.1 over plain TCP
- one request per connection
- request line, headers, optional body
- response status line, headers, optional body
- enough framing support to handle `Content-Length`

Things that can wait:

- TLS
- chunked transfer encoding
- keep-alive and connection reuse
- redirects
- compression
- HTTP/2

## Main HTTP Components

### `HttpRequest`

Owns the project-level HTTP request contract used by the caller and serializer.

### `HttpResponse`

Owns the structured HTTP response returned by the parser and client.

### `HttpValidator`

Validates HTTP-specific fields such as:

- required request members
- method validity
- host and port presence
- header structure
- body consistency rules

### `HttpSerializer`

- builds the request line
- appends query parameters to the target path
- formats headers
- ensures required headers are present when the chosen scope needs them
- appends the request body

### `HttpParser`

- parses the status line
- parses headers
- reads the response body according to the response framing rules supported by the current scope

### `HttpClient`

Owns outbound HTTP processing logic. It should:

- accept HTTP requests
- run HTTP-specific validation
- use `net::TcpClient` for connect/send/receive
- invoke `HttpSerializer` and `HttpParser`
- return a structured response

## Preferred Flow

1. Build an `HttpRequest`.
2. Validate it.
3. Serialize it into bytes.
4. Send it through `net::TcpClient`.
5. Parse the response bytes into `HttpResponse`.

If the project keeps `Dispatcher`, it should wrap this flow rather than replace it.

## Boundary Rule

The core layer must not know HTTP semantics.

Only the HTTP subsystem should understand:

- methods
- headers
- query parameters
- body representation
- status handling specific to HTTP
