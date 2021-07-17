# R-Type's RFC

## Arguments

| Argument                  | Description                               |
| ------------------------- | ----------------------------------------- |
| CommandID                 | Command ID.                               |
| UserID                    | User ID.                                  |
| RoomID                    | Room ID.                                  |
| Port                      | Port.                                     |
| Name                      | Name                                      |
| Place                     | Place inside the room                     |
| NumberofPlayer            | Number of player inside the room          |
| Bomb                      | Number of bombs which be given            |
| Life                      | Number of players' lives                  |

## TCP

### Server -> Client Requests

| Request name              | Arguments                                                 | Description                                                |
| ------------------------- | --------------------------------------------------------- | ---------------------------------------------------------- |
| UNKNOWN                   | ()                                                        | Response if the command previously sent is not recognized. |
| SC_OK                     | (CommandID)                                               | Response if the command previously sent is okay.           |
| SC_ERROR                  | (CommandID, message)                                      | Response if the command previously sent has an error.      |
| SC_ROOM                   | (RoomID, Name, Port, Place, NumberofPlayer, Bomb, Life)   | Description of one room                                    |
| SC_PLAYER_UUID            | (UserID)                                                  | PlayerID                                                   |
| SC_ROOM_LOCATION          | (Port)                                                    | Port of the game room                                      |

### Client -> Server Requests

| Request name              | Arguments                 | Description                                                               |
| ------------------------- | ------------------------- | ------------------------------------------------------------------------- |
| CS_CREATE_ROOM            | (Name, Place, Bomb, Life) | Create a game room on the server                                          |
| CS_JOIN_ROOM              | (RoomID)                  | Join a room                                                               |
| CS_GET_ROOM               | ()                        | Get all existing rooms on the server                                      |
| CS_LEAVE_ROOM             | (RoomID)                  | Leave a room                                                              |

## UDP

### Server -> Client Requests

| Request name              | Arguments                                                 | Description                                                |
| ------------------------- | --------------------------------------------------------- | ---------------------------------------------------------- |
| SC_UPDATE                 | (RTypeNetworkObject)                                      | Description (Response with SC_OK(CS_ACTION))               |
| SC_ERROR_SIZE             | ()                                                        | When the request sent wasn't a wrong size                  |
| SC_ERROR_AUTH             | ()                                                        | When the user isn't authorizate to make request            |
| SC_ERROR_REQUEST          | ()                                                        | When the send request sent doesn't exist on the server     |
| SC_ERROR_UNKNOW           | ()                                                        | When error has occured                                     |

### Client -> Server Requests

| Request name              | Arguments                                                 | Description                                                |
| ------------------------- | --------------------------------------------------------- | ---------------------------------------------------------- |
| CS_ACTION                 | ( RTypeNetworkInput)                                      | Description (Response with SC_OK(CS_UPDATE))               |
