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

CPrintToChat_Ex(int client, int author, const char[] format, any ...)
// Prints a message to a specific client. The chat sound is enabled.

CPrintToChatAll(const char[] format, any ...)
// Prints a message to a all clients. The chat sound is disabled.

CPrintToChatAll_Ex(int author, const char[] format, any ...)
// Prints a message to a all clients. The chat sound is enabled.

CReplyToCommand(int client, const char[] format, any ...)
// Replies to a message in a command. The chat sound is disabled.
```

I will come up with the rest.
