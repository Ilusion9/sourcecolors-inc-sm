#if defined _sourcecolors_included
    #endinput
#endif
#define _sourcecolors_included

#include <regex>

#define MAX_MESSAGE_LENGTH 256

enum struct ColorInfo
{
	char colorTag[64];
	char colorHex[64];
}

#include <sourcecolors/morecolors>
#include <sourcecolors/colors>

/**
 * Prints a message to a specific client in the chat area.
 * The chat sound is disabled. If teamcolor is used, the client's teamcolor will be displayed.
 * 
 * @param client        Client index.
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 * @error               If the client is not connected or invalid.
 */
stock void CPrintToChat(int client, const char[] format, any ...)
{
	if (client < 1 || client > MaxClients)
	{
		ThrowError("Invalid client index %d", client);
	}
	
	if (!IsClientConnected(client))
	{
		ThrowError("Client %i is not connected", client);
	}
	
	SetGlobalTransTarget(client);
	
	char buffer[MAX_MESSAGE_LENGTH];
	int buffer_index = CPreFormat(buffer, sizeof(buffer));
	
	VFormat(buffer[buffer_index], sizeof(buffer) - buffer_index, format, 3);
	CFormat(buffer[buffer_index], sizeof(buffer) - buffer_index);
	CSendMessage(client, buffer);
}

/**
 * Prints a message to a specific client in the chat area.
 * The chat sound is enabled. If teamcolor is used, the author's teamcolor will be displayed.
 * 
 * @param client        Client index.
 * @param author        Author index.
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 * @error               If the client is not connected or invalid.
 * @error               If the author is not connected or invalid.
 */
stock void CPrintToChat_Ex(int client, int author, const char[] format, any ...)
{
	if (client < 1 || client > MaxClients)
	{
		ThrowError("Invalid client index %d", client);
	}
	
	if (author < 1 || author > MaxClients)
	{
		ThrowError("Invalid author index %d", author);
	}
	
	if (!IsClientConnected(client))
	{
		ThrowError("Client %i is not connected", client);
	}
	
	if (!IsClientConnected(author))
	{
		ThrowError("Author %i is not connected", author);
	}
	
	SetGlobalTransTarget(client);
	
	char buffer[MAX_MESSAGE_LENGTH];
	int buffer_index = CPreFormat(buffer, sizeof(buffer));
	
	VFormat(buffer[buffer_index], sizeof(buffer) - buffer_index, format, 4);
	CFormat(buffer[buffer_index], sizeof(buffer) - buffer_index);
	CSendMessage(client, buffer, author);
}

/**
 * Prints a message to all clients in the chat area.
 * The chat sound is disabled. If teamcolor is used, the clients teamcolors will be displayed.
 * 
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 */
stock void CPrintToChatAll(const char[] format, any ...)
{
	char buffer[MAX_MESSAGE_LENGTH];
	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && !IsFakeClient(i))
		{
			SetGlobalTransTarget(i);
			int buffer_index = CPreFormat(buffer, sizeof(buffer));

			VFormat(buffer[buffer_index], sizeof(buffer) - buffer_index, format, 2);
			CFormat(buffer[buffer_index], sizeof(buffer) - buffer_index);
			CSendMessage(i, buffer);
		}
	}
}

/**
 * Prints a message to all clients in the chat area.
 * The chat sound is enabled. If teamcolor is used, the author's teamcolor will be displayed.
 * 
 * @param author        Author index.
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 * @error               If the author is not connected or invalid.
 */
stock void CPrintToChatAll_Ex(int author, const char[] format, any ...)
{
	if (author < 1 || author > MaxClients)
	{
		ThrowError("Invalid author index %d", author);
	}
	
	if (!IsClientConnected(author))
	{
		ThrowError("Author %i is not in game", author);
	}
	
	char buffer[MAX_MESSAGE_LENGTH];
	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && !IsFakeClient(i))
		{
			SetGlobalTransTarget(i);
			int buffer_index = CPreFormat(buffer, sizeof(buffer));

			VFormat(buffer[buffer_index], sizeof(buffer) - buffer_index, format, 3);
			CFormat(buffer[buffer_index], sizeof(buffer) - buffer_index);
			CSendMessage(i, buffer, author);
		}
	}
}

/**
 * Replies to a message in a command.
 *
 * A client index of 0 will use PrintToServer().
 * If the command was from the console, PrintToConsole() is used.
 * If the command was from chat, CPrintToChat() is used.
 *
 * @param client        Client index, or 0 for server.
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 * @error               If the client is not connected or invalid.
 */
stock void CReplyToCommand(int client, const char[] format, any ...)
{
	if (client < 0 || client > MaxClients)
	{
		ThrowError("Invalid client index %d", client);
	}
	
	char buffer[MAX_MESSAGE_LENGTH];
	SetGlobalTransTarget(LANG_SERVER);
	
	if (client == 0)
	{
		VFormat(buffer, sizeof(buffer), format, 3);
		CRemoveColors(buffer, sizeof(buffer));
		PrintToServer(buffer);
		return;
	}
	
	if (!IsClientConnected(client))
	{
		ThrowError("Client %i is not in game", client);
	}
	
	SetGlobalTransTarget(client);
	if (GetCmdReplySource() == SM_REPLY_TO_CONSOLE)
	{
		VFormat(buffer, sizeof(buffer), format, 3);
		CRemoveColors(buffer, sizeof(buffer));
		PrintToConsole(client, buffer);
		return;
	}

	int buffer_index = CPreFormat(buffer, sizeof(buffer));
	VFormat(buffer[buffer_index], sizeof(buffer) - buffer_index, format, 3);
	
	CFormat(buffer[buffer_index], sizeof(buffer) - buffer_index);
	CSendMessage(client, buffer);
}

stock void CFormat(char[] format, int maxlen)
{
	if (IsSource2009())
	{
		MC_Format(format, maxlen);
	}
	else
	{
		C_Format(format, maxlen);
	}
}

stock void CRemoveColors(char[] format, int maxlen)
{
	if (IsSource2009())
	{
		MC_RemoveColors(format, maxlen);
	}
	else
	{
		C_RemoveColors(format, maxlen);
	}
}

stock void CSendMessage(int client, const char[] message, int author = 0)
{
	if (IsSource2009())
	{
		MC_SendMessage(client, message, author);
	}
	else
	{
		C_SendMessage(client, message, author);
	}
}

stock int CPreFormat(char[] message, int maxlen)
{
	if (GetEngineVersion() == Engine_CSGO)
	{
		return Format(message, maxlen, " ");
	}

	return Format(message, maxlen, "\x01");
}

stock bool IsSource2009()
{
	if (GetEngineVersion() == Engine_CSS || GetEngineVersion() == Engine_HL2DM || GetEngineVersion() == Engine_DODS || GetEngineVersion() == Engine_TF2)
	{
		return true;
	}
	
	return false;
}
