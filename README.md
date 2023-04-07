# Description
Provides colors for plugins to use in chat.

# Colors
## Colors for all games
```
{color:default}
{color:team}
```

## Colors for CS:S, DOD:S, HL2:DM, TF2 and SDK 2013
```
{color:black}
{color:blue}
{color:bronze}
{color:brown}
{color:coral}
{color:crimson}
{color:cyan}
{color:emerald}
{color:gold}
{color:gray}
{color:green}
{color:grey}
{color:lime}
{color:magenta}
{color:olive}
{color:orange}
{color:pink}
{color:purple}
{color:red}
{color:silver}
{color:teal}
{color:tomato}
{color:turquoise}
{color:white}
{color:yellow}
{color:team_spec} // for CS:S, DOD:S, HL2:DM and TF2
{color:team_t} // for CS:S
{color:team_ct} // for CS:S
{color:team_allies} // for DOD:S
{color:team_axis} // for DOD:S
{color:team_red} // for HL2:DM and TF2
{color:team_blue} // for HL2:DM and TF2
```

### Hex colors:
```
{color:#FFFFFF}
{color:#000000}
{color:#FFFFFF50} // transparent color
{color:#00000015} // transparent color
```

### RGB colors:
```
{color:rgb(255, 255, 255)}
{color:rgb(0, 0, 0)}
{color:rgba(255, 255, 255, 0.31)} // transparent color
{color:rgba(0, 0, 0, 0.08)} // transparent color
```

## Colors for CS:GO
```
{color:blue}
{color:bluegrey}
{color:darkblue}
{color:darkred}
{color:green}
{color:gray}
{color:gray2}
{color:grey}
{color:grey2}
{color:lightgreen}
{color:lightred}
{color:lime}
{color:red}
{color:orange}
{color:purple}
{color:yellow}
```

## Colors for L4D and L4D2
```
{color:olive}
{color:orange}
```

# Defines
```sourcepawn
#define SOURCECOLORS_MAX_MESSAGE_LENGTH        256
```

# Functions
```sourcepawn
/**
 * Retrieves the chat parameters for the following message (sent by a function from this library).
 * 
 * @param author        Author's index (0 = server, SOURCECOLORS_AUTHOR_RECEIVER if the author is the receiver).
 * @return              True if the chat parameters are set for the following message, false otherwise.
 */
bool CGetChatTextParams(int& author);

/**
 * Sets the chat parameters for the following message (sent by a function from this library).
 * 
 * @param author        Author's index (0 = server, SOURCECOLORS_AUTHOR_RECEIVER to set the receiver as the author).
 * @error               Invalid author index or author not connected.
 */
void CSetChatTextParams(int author);

/**
 * Resets the chat parameters for the following message (sent by a function from this library).
 */
void CResetChatTextParams();

/**
 * Prints a message to a specific client in the chat area.
 * 
 * @param client        Client's index.
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 * @error               Invalid client index or client not connected.
 */
void CPrintToChat(int client, const char[] format, any ...);

/**
 * Prints a message to all clients in the chat area.
 * 
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 */
void CPrintToChatAll(const char[] format, any ...);

/**
 * Replies to a command.
 * 
 * @param client        Client's index (0 = server).
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 * @error               Invalid client index or client not connected.
 */
void CReplyToCommand(int client, const char[] format, any ...);

/**
 * Displays usage of an admin command to users depending on the setting of the sm_show_activity cvar.
 * All users receive a message in their chat text, except for the originating client, who receives it both in chat and console.
 * 
 * @param client        Client's index (0 = server).
 * @param tag           Tag to prepend to the message.
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 * @error               Invalid client index or client not connected.
 */
void CShowActivity(int client, const char[] tag, const char[] format, any ...);

/**
 * Formats a string by replacing color tags with color values.
 * 
 * @param buffer        Destination string buffer.
 * @param maxlen        Maximum length of the string buffer.
 * @return              The number of characters written.
 */
int CFormat(char[] buffer, int maxlen);

/**
 * Removes color tags from a string.
 * 
 * @param buffer        Destination string buffer.
 * @param maxlen        Maximum length of the string buffer.
 * @return              The number of characters written.
 */
int CRemoveTags(char[] buffer, int maxlen);

/**
 * Retrieves a color's value from a color's tag.
 * 
 * @param color         Color's tag.
 * @param buffer        Buffer to store the color's value.
 * @param maxlen        Maximum length of the buffer.
 * @return              The number of characters written.
 */
int CGetColor(const char[] color, char[] buffer, int maxlen);
```

# Examples
```sourcepawn
char color[256];
CGetColor("blue", color, sizeof(color));

// {color:team} = the team color of the receiver
CPrintToChatAll("{color:team}%N :{color:default} test message", client);

// {color:team} = the team color of the client
CSetChatTextParams(client);
CPrintToChatAll("{color:team}%N :{color:default} test message", client);
```
