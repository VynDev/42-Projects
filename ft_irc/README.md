# Protocol:

## Packet structure

Protocol version (4B) | Size of content (4B) | Message type (4B) | Content (Max length defined by MESSAGE_MAXLENGTH)

### Protocol version
	
Defined by PROTO_VERSION

### Message type

Types are defined by PROTO_TYPE_*

# Text message type (PROTO_TYPE_TEXT)

## In chat **client** commands

/connect \<host\> [port]

/msg \<target\> \<text\>

/nick \<nickname\>

/join \<channel\>

/leave [channel]

/who

## [Protocol] Commands from the **client** to the **server**

/msg \<target\> \<text\>

/nick \<nickname\>

/join \<channel\>

/leave [channel]

/who

## [Protocol] Commands from the **server** to the **client**

/msg \<sender\> \<target\> \<text\>

/nick \<old nickname\> \<new nickname\>

/join \<channel\> \<nickname\>

/leave \<channel\> \<nickname\>
