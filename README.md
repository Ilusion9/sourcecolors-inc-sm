# Description
Provides colors for plugins to use in chat.

# Colors
## Colors for all games
```
{color:default}
{color:team}
```

## Colors for CS:S, DOD:S, HL2:DM and TF2
```
{color:azure}
{color:black}
{color:blue}
{color:brown}
{color:coral}
{color:crimson}
{color:cyan}
{color:emerald}
{color:gold}
{color:green}
{color:grey}
{color:lime}
{color:magenta}
{color:orange}
{color:pink}
{color:purple}
{color:red}
{color:silver}
{color:teal}
{color:turquoise}
{color:white}
{color:yellow}
{color:team_spec}
{color:team_t} // only for CS:S
{color:team_ct} // only for CS:S
{color:team_allies} // only for DOD:S
{color:team_axis} // only for DOD:S
{color:team_red} // only for HL2:DM and TF2
{color:team_blue} // only for HL2:DM and TF2
```

### Hex colors:
```
{color:#FFFFFF}
{color:#000000}
{color:#FFFFFF50} // transparent color
{color:#00000015} // transparent color
```

## Colors for CS:GO
```
{color:blue}
{color:bluegrey}
{color:darkblue}
{color:darkred}
{color:green}
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
 * Retrieves a color's value from a color's name or hex value.
 * 
 * @param color         Color's name or hex value.
 * @param buffer        Buffer to store the color's value.
 * @param maxlen        Maximum length of the buffer.
 * @return              The number of characters written.
 */
int CGetColor(const char[] color, char[] buffer, int maxlen);
```

# Examples
```sourcepawn
// {color:team} = the team color of the receiver
CPrintToChatAll("client is{color:team} %N{color:default} : test message", client);

// {color:team} = the team color of the client
CSetChatTextParams(client);
CPrintToChatAll("client is{color:team} %N{color:default} : test message", client);
```
