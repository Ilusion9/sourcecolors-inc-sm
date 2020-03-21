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
```csharp
CPrintToChat(int client, const char[] format, any ...);
// Prints a message to a specific client. The chat sound is disabled.
// If teamcolor is used, the client's teamcolor will be displayed.

CPrintToChat_Ex(int client, int author, const char[] format, any ...)
// Prints a message to a specific client. The chat sound is enabled.
// If teamcolor is used, the author's teamcolor will be displayed.

CPrintToChatAll(const char[] format, any ...)
// Prints a message to a all clients. The chat sound is disabled.
// If teamcolor is used, for every client will be displayed their teamcolor.

CPrintToChatAll_Ex(int author, const char[] format, any ...)
// Prints a message to a all clients. The chat sound is enabled.
// If teamcolor is used, the author's teamcolor will be displayed.

CReplyToCommand(int client, const char[] format, any ...)
// Replies to a message in a command. The chat sound is disabled.
// If teamcolor is used, the client's teamcolor will be displayed.
```

I will come up with the rest.
