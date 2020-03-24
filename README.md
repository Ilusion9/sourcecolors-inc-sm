# Description
Another multicolors library.
Credits to: multicolors, colors, morecolors, colorlib creators.

## Colors CSS, TF2, DODS, HL2DM
```
{$default}
{$team}
{$red}
{$blue}
{$green}
{$white}
{$yellow}
{$purple}
{$orange}
{$lime}
{$grey}
{$black}
```

You can use any HEX color like this
```
{#FFFFFF}
{#121212}
{#AB89EA}
etc.
```

## Colors for other games
```
{$default}
{$team}
{$darkred}
{$green}
{$lightgreen}
{$lime}
{$red}
{$grey}
{$yellow}
{$orange}
{$bluegrey}
{$blue}
{$darkblue}
{$grey2}
{$orchid}
{$lightred}
```

# Functions
```sourcepawn

/**
 * Prints a message to a specific client in the chat area.
 * The chat sound is disabled. If teamcolor is used, the client's teamcolor will be displayed.
 */
CPrintToChat(int client, const char[] format, any ...);

/**
 * Prints a message to a specific client in the chat area.
 * The chat sound is disabled by default. If teamcolor is used, the author's teamcolor will be displayed.
 * Index 0 as author is accepted and the teamcolor will be displayed exactly as in PrintToChat.
 */
CPrintToChat_Ex(int client, int author, bool playSound, const char[] format, any ...)

/**
 * Prints a message to all clients in the chat area.
 * The chat sound is disabled. If teamcolor is used, the client's teamcolor will be displayed.
 */
CPrintToChatAll(const char[] format, any ...)

/**
 * Prints a message to all clients in the chat area.
 * The chat sound is disabled by default. If teamcolor is used, the author's teamcolor will be displayed.
 * Index 0 as author is accepted and the teamcolor will be displayed exactly as in PrintToChat.
 */
CPrintToChatAll_Ex(int author, bool playSound, const char[] format, any ...)

/**
 * Replies to a message in a command.
 * The chat sound is disabled. If teamcolor is used, the client's teamcolor will be displayed.
 */
CReplyToCommand(int client, const char[] format, any ...)

/**
 * Displays usage of an admin command to users depending on the setting of the sm_show_activity cvar.
 * The chat sound is enabled. If teamcolor is used, the client's teamcolor will be displayed.
 */
CShowActivity2(int client, const char[] tag, const char[] format, any ...)

/**
 * Displays usage of an admin command to users depending on the setting of the sm_show_activity cvar.
 * The chat sound is enabled. If teamcolor is used, the author's teamcolor will be displayed.
 * Index 0 as author is accepted and the teamcolor will be displayed exactly as in PrintToChat.
 */
CShowActivity2_Ex(int client, int author, const char[] tag, const char[] format, any ...)

/**
 * Replace color tags from string with actual color values.
 */
CFormat(char[] format, int maxlen)

/**
 * Remove color tags from string.
 */
CRemoveColors(char[] format, int maxlen)
```

TO DO: Add CShowActivity, CShowActivity_Ex and examples on how to use all functions.
