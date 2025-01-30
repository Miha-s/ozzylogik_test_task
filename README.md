# Ozzylogik Test Task
Realization of time-efficient program that does static text analysis

## Task
Implement TCP client-server application, that does the following:  
Client can send to server any text, server responds with following information about the text:
 - number of words
 - number of unique words
 - number of words in longest unique words sequence

After displaying data in console, client ends the communication and exits.

## Specific requirements
 - Words like `Alice's`, `isn't`, `I'm` must be considered as one word
 - Text encoding is UTF-8
 - Server responds with JSON
 - Server logs its execution
 - Program must be time-efficient
 - Server implemented using Boost
 - Client implemented using Qt
 - Client and server must be cross platform

## Made assumptions
 - If we use `'` in text to indicate quoting text, space before or after must be present.  
 Example:
> "sdfi'adsf" - one word  
> "sdfi 'asdf" - two words
 - There isn't an easy way to work with whole UNICODE UTF-8 encodding. Any attempt would probably be only partial solution. So only ASCII subset of UTF-8 encoding is considered for this program.
 - Not many clients is quering server at the same time. If this is otherwise, a multithreading can be easily added, by running `io_context.run()` in thread pool, as sessions is independend of one another, no synchronization is required.
