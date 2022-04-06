# Description
Another multicolors library.
Credits to: multicolors, colors, morecolors, colorlib creators.

## Colors CSS, TF2, DODS, HL2DM
```
{color:default}
{color:team}
{color:red}
{color:blue}
{color:green}
{color:white}
{color:yellow}
{color:purple}
{color:orange}
{color:lime}
{color:grey}
{color:black}
```

You can use any HEX color like this
```
{color:#FFFFFF}
{color:#121212}
{color:#AB89EA}
etc.
```

## Colors for other games
```
{color:default}
{color:team}
{color:darkred}
{color:green}
{color:lightgreen}
{color:lime}
{color:red}
{color:grey}
{color:yellow}
{color:orange}
{color:bluegrey}
{color:blue}
{color:darkblue}
{color:grey2}
{color:orchid}
{color:lightred}
```

# Functions
```sourcepawn

/**
 * Prints a message to a specific client in the chat area.
 */
void CPrintToChat(int client, const char[] format, any ...);

/**
 * Prints a message to a specific client in the chat area.
 */
void CPrintToChat_Ex(int client, int author, bool chatMessage, const char[] format, any ...)

/**
 * Prints a message to all clients in the chat area.
 */
void CPrintToChatAll(const char[] format, any ...)

/**
 * Prints a message to all clients in the chat area.
 */
void CPrintToChatAll_Ex(int author, bool chatMessage, const char[] format, any ...)

/**
 * Prints a message to all clients from a specific team in the chat area.
 */
void CPrintToChatTeam(int team, const char[] format, any ...)

/**
 * Prints a message to all clients from a specific team in the chat area.
 */
void CPrintToChatTeam_Ex(int author, int team, bool chatMessage, const char[] format, any ...)

/**
 * Replies to a message in a command.
 */
void CReplyToCommand(int client, const char[] format, any ...)

/**
 * Replies to a message in a command.
 */
void CReplyToCommand_Ex(int client, int author, bool chatMessage, const char[] format, any ...)

/**
 * Replies to a message in a command.
 */
void CReplyToCommandSource(int client, ReplySource replySource, const char[] format, any ...)

/**
 * Replies to a message in a command.
 */
void CReplyToCommandSource_Ex(int client, int author, bool chatMessage, ReplySource replySource, const char[] format, any ...)

/**
 * Displays usage of an admin command to users depending on the 
 * setting of the sm_show_activity cvar. All users receive a message 
 * in their chat text, except for the originating client, who receives 
 * the message both in chat and console.
 */
void CShowActivity(int client, const char[] tag, const char[] format, any ...)

/**
 * Displays usage of an admin command to users depending on the 
 * setting of the sm_show_activity cvar. All users receive a message 
 * in their chat text, except for the originating client, who receives 
 * the message both in chat and console.
 */
void CShowActivity_Ex(int client, int author, const char[] tag, const char[] format, any ...)

/**
 * Displays usage of an admin command to users depending on the 
 * setting of the sm_show_activity cvar. All users receive a message 
 * in their chat text, except for the originating client, who receives 
 * the message both in chat and console.
 */
void CShowActivityAdmin(char[] clientName, AdminId adminId, const char[] tag, const char[] format, any ...)

/**
 * Displays usage of an admin command to users depending on the 
 * setting of the sm_show_activity cvar. All users receive a message 
 * in their chat text, except for the originating client, who receives 
 * the message both in chat and console.
 */
void CShowActivityAdmin_Ex(char[] clientName, AdminId adminId, int author, const char[] tag, const char[] format, any ...)

/**
 * Prepares a string to display the message correctly in the chat.
 */
int CPreFormat(char[] message, int maxlen)

/**
 * Replace color tags from a string with actual color values.
 */
int CFormat(char[] format, int maxlen)

/**
 * Remove color tags from a string.
 */
int CRemoveTags(char[] format, int maxlen)

/**
 * Remove colors from a string.
 */
int CRemoveColors(char[] format, int maxlen)
```
