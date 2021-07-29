#if defined _sourcecolors_included
    #endinput
#endif
#define _sourcecolors_included

#define MAX_MESSAGE_LENGTH               256
#define kActivityNone                    0
#define kActivityNonAdmins               1
#define kActivityNonAdminsNames          2
#define kActivityAdmins                  4
#define kActivityAdminsNames             8
#define kActivityRootNames               16

enum struct ColorInfo
{
	char colorTag[64];
	char colorHex[64];
}

#include <sourcecolors/morecolors>
#include <sourcecolors/colors>

/**
 * Prints a message to a specific client in the chat area.
 * 
 * @param client            Client index.
 * @param format            Formatting rules.
 * @param ...               Variable number of format parameters.
 * @error                   If the client is not connected or invalid.
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
	int index = CPreFormat(buffer, sizeof(buffer));
	VFormat(buffer[index], sizeof(buffer) - index, format, 3);
	
	CFormat(buffer[index], sizeof(buffer) - index);
	CSendMessage(client, buffer);
}

/**
 * Prints a message to a specific client in the chat area.
 *
 * @param client            Client index.
 * @param author            Author index.
 * @param chatMessage       Regular chat message?
 * @param format            Formatting rules.
 * @param ...               Variable number of format parameters.
 * @error                   If the client is not connected or invalid.
 * @error                   If the author is not connected or invalid.
 */
stock void CPrintToChat_Ex(int client, int author, bool chatMessage, const char[] format, any ...)
{
	if (client < 1 || client > MaxClients)
	{
		ThrowError("Invalid client index %d", client);
	}
	
	if (!IsClientConnected(client))
	{
		ThrowError("Client %i is not connected", client);
	}
	
	if (author)
	{
		if (author < 1 || author > MaxClients)
		{
			ThrowError("Invalid author index %d", author);
		}
		
		if (!IsClientConnected(author))
		{
			ThrowError("Author %i is not connected", author);
		}
	}
	
	SetGlobalTransTarget(client);
	
	char buffer[MAX_MESSAGE_LENGTH];
	int index = CPreFormat(buffer, sizeof(buffer));
	VFormat(buffer[index], sizeof(buffer) - index, format, 5);
	
	CFormat(buffer[index], sizeof(buffer) - index);
	CSendMessage(client, buffer, author, chatMessage);
}

/**
 * Prints a message to all clients in the chat area.
 * 
 * @param format            Formatting rules.
 * @param ...               Variable number of format parameters.
 */
stock void CPrintToChatAll(const char[] format, any ...)
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientConnected(i) || IsFakeClient(i))
		{
			continue;
		}
		
		SetGlobalTransTarget(i);
		
		char buffer[MAX_MESSAGE_LENGTH];
		int index = CPreFormat(buffer, sizeof(buffer));
		VFormat(buffer[index], sizeof(buffer) - index, format, 2);
		
		CFormat(buffer[index], sizeof(buffer) - index);
		CSendMessage(i, buffer);
	}
}

/**
 * Prints a message to all clients in the chat area.
 *
 * @param author            Author index.
 * @param chatMessage       Regular chat message?
 * @param format            Formatting rules.
 * @param ...               Variable number of format parameters.
 * @error                   If the author is not connected or invalid.
 */
stock void CPrintToChatAll_Ex(int author, bool chatMessage, const char[] format, any ...)
{
	if (author)
	{
		if (author < 1 || author > MaxClients)
		{
			ThrowError("Invalid author index %d", author);
		}
		
		if (!IsClientConnected(author))
		{
			ThrowError("Author %i is not connected", author);
		}
	}
	
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientConnected(i) || IsFakeClient(i))
		{
			continue;
		}
		
		SetGlobalTransTarget(i);
		
		char buffer[MAX_MESSAGE_LENGTH];
		int index = CPreFormat(buffer, sizeof(buffer));
		VFormat(buffer[index], sizeof(buffer) - index, format, 4);
		
		CFormat(buffer[index], sizeof(buffer) - index);
		CSendMessage(i, buffer, author, chatMessage);
	}
}

/**
 * Prints a message to all clients from a specific team in the chat area.
 * 
 * @param team              Team index.
 * @param format            Formatting rules.
 * @param ...               Variable number of format parameters.
 */
stock void CPrintToChatTeam(int team, const char[] format, any ...)
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i) || GetClientTeam(i) != team)
		{
			continue;
		}
		
		SetGlobalTransTarget(i);
		
		char buffer[MAX_MESSAGE_LENGTH];
		int index = CPreFormat(buffer, sizeof(buffer));
		VFormat(buffer[index], sizeof(buffer) - index, format, 3);
		
		CFormat(buffer[index], sizeof(buffer) - index);
		CSendMessage(i, buffer);
	}
}

/**
 * Prints a message to all clients from a specific team in the chat area.
 *
 * @param team              Team index.
 * @param author            Author index.
 * @param chatMessage       Regular chat message?
 * @param format            Formatting rules.
 * @param ...               Variable number of format parameters.
 * @error                   If the author is not connected or invalid.
 */
stock void CPrintToChatTeam_Ex(int team, int author, bool chatMessage, const char[] format, any ...)
{
	if (author)
	{
		if (author < 1 || author > MaxClients)
		{
			ThrowError("Invalid author index %d", author);
		}
		
		if (!IsClientConnected(author))
		{
			ThrowError("Author %i is not connected", author);
		}
	}
	
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i) || GetClientTeam(i) != team)
		{
			continue;
		}
		
		SetGlobalTransTarget(i);
		
		char buffer[MAX_MESSAGE_LENGTH];
		int index = CPreFormat(buffer, sizeof(buffer));
		VFormat(buffer[index], sizeof(buffer) - index, format, 5);
		
		CFormat(buffer[index], sizeof(buffer) - index);
		CSendMessage(i, buffer, author, chatMessage);
	}
}

/**
 * Replies to a message in a command.
 *
 * @param client            Client index, or 0 for server.
 * @param format            Formatting rules.
 * @param ...               Variable number of format parameters.
 * @error                   If the client is not connected or invalid.
 */
stock void CReplyToCommand(int client, const char[] format, any ...)
{
	if (client < 0 || client > MaxClients)
	{
		ThrowError("Invalid client index %d", client);
	}
	
	if (!client)
	{
		SetGlobalTransTarget(LANG_SERVER);
		
		char buffer[MAX_MESSAGE_LENGTH];
		VFormat(buffer, sizeof(buffer), format, 3);
		CRemoveTags(buffer, sizeof(buffer));
		
		PrintToServer(buffer);
		return;
	}
	
	if (!IsClientConnected(client))
	{
		ThrowError("Client %i is not connected", client);
	}
	
	char buffer[MAX_MESSAGE_LENGTH];
	SetGlobalTransTarget(client);
	
	if (GetCmdReplySource() == SM_REPLY_TO_CONSOLE)
	{
		VFormat(buffer, sizeof(buffer), format, 3);
		CRemoveTags(buffer, sizeof(buffer));
		PrintToConsole(client, buffer);
	}
	else
	{
		int index = CPreFormat(buffer, sizeof(buffer));
		VFormat(buffer[index], sizeof(buffer) - index, format, 3);
		CFormat(buffer[index], sizeof(buffer) - index);
		CSendMessage(client, buffer);
	}
}

/**
 * Replies to a message in a command.
 *
 * @param client            Client index, or 0 for server.
 * @param replySource       ReplySource value.
 * @param format            Formatting rules.
 * @param ...               Variable number of format parameters.
 * @error                   If the client is not connected or invalid.
 */
stock void CReplyToCommand_Ex(int client, ReplySource replySource, const char[] format, any ...)
{
	char buffer[254];
	SetGlobalTransTarget(client);
	VFormat(buffer, sizeof(buffer), format, 4);
	
	ReplySource currentSource = SetCmdReplySource(replySource);
	CReplyToCommand(client, buffer);
	SetCmdReplySource(currentSource);
}

/**
 * Displays usage of an admin command to users depending on the 
 * setting of the sm_show_activity cvar.  All users receive a message 
 * in their chat text, except for the originating client, who receives 
 * the message both in chat and console.
 *
 * @param client            Client index doing the action, or 0 for server.
 * @param tag               Tag to prepend to the message.
 * @param format            Formatting rules.
 * @param ...               Variable number of format parameters.
 * @error                   If the client is not connected or invalid.
 */
stock void CShowActivity(int client, const char[] tag, const char[] format, any ...)
{
	char signUser[MAX_MESSAGE_LENGTH] = "ADMIN";
	char buffer[MAX_MESSAGE_LENGTH];
	
	if (client)
	{
		if (client < 1 || client > MaxClients)
		{
			ThrowError("Invalid client index %d", client);
		}
		
		if (!IsClientConnected(client))
		{
			ThrowError("Client %i is not connected", client);
		}
				
		AdminId adminId = GetUserAdmin(client);
		if (adminId == INVALID_ADMIN_ID || !GetAdminFlag(adminId, Admin_Generic, Access_Effective))
		{
			signUser = "PLAYER";
		}
		
		SetGlobalTransTarget(client);
		VFormat(buffer, sizeof(buffer), format, 4);
		CRemoveTags(buffer, sizeof(buffer));
		PrintToConsole(client, "%s%s", tag, buffer);
	}
	else
	{
		SetGlobalTransTarget(LANG_SERVER);
		VFormat(buffer, sizeof(buffer), format, 4);
		CRemoveTags(buffer, sizeof(buffer));
		PrintToServer("%s%s", tag, buffer);
	}
	
	ConVar cvarActivity = FindConVar("sm_show_activity");
	if (!cvarActivity || !cvarActivity.BoolValue)
	{
		return;
	}
	
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientConnected(i) || IsFakeClient(i))
		{
			continue;
		}
		
		SetGlobalTransTarget(i);		
		AdminId adminId = GetUserAdmin(i);
		VFormat(buffer, sizeof(buffer), format, 4);
		
		if (adminId == INVALID_ADMIN_ID || !GetAdminFlag(adminId, Admin_Generic, Access_Effective))
		{
			if ((cvarActivity.IntValue & kActivityNonAdmins) || (cvarActivity.IntValue & kActivityNonAdminsNames))
			{
				if (cvarActivity.IntValue & kActivityNonAdminsNames || i == client)
				{
					CPrintToChat_Ex(i, client, true, "%s%N: %s", tag, client, buffer);
				}
				else
				{
					CPrintToChat_Ex(i, client, true, "%s%N: %s", tag, signUser, buffer);
				}
			}
		}
		else
		{
			bool rootAccess = GetAdminFlag(adminId, Admin_Root, Access_Effective);
			if ((cvarActivity.IntValue & kActivityAdmins) 
				|| (cvarActivity.IntValue & kActivityAdminsNames) 
				|| ((cvarActivity.IntValue & kActivityRootNames) && rootAccess))
			{
				if ((cvarActivity.IntValue & kActivityAdminsNames) 
					|| ((cvarActivity.IntValue & kActivityRootNames) && rootAccess)
					|| i == client)
				{
					CPrintToChat_Ex(i, client, true, "%s%N: %s", tag, client, buffer);
				}
				else
				{
					CPrintToChat_Ex(i, client, true, "%s%s: %s", tag, signUser, buffer);
				}
			}
		}
	}
}

/**
 * Displays usage of an admin command to users depending on the 
 * setting of the sm_show_activity cvar.  All users receive a message 
 * in their chat text, except for the originating client, who receives 
 * the message both in chat and console.
 *
 * @param client            Client index doing the action, or 0 for server.
 * @param author            Author index.
 * @param tag               Tag to prepend to the message.
 * @param format            Formatting rules.
 * @param ...               Variable number of format parameters.
 * @error                   If the client is not connected or invalid.
 * @error                   If the author is not connected or invalid.
 */
stock void CShowActivity_Ex(int client, int author, const char[] tag, const char[] format, any ...)
{
	if (author)
	{
		if (author < 1 || author > MaxClients)
		{
			ThrowError("Invalid author index %d", author);
		}
		
		if (!IsClientConnected(author))
		{
			ThrowError("Author %i is not connected", author);
		}
	}
	
	char signUser[MAX_MESSAGE_LENGTH] = "ADMIN";
	char buffer[MAX_MESSAGE_LENGTH];
	
	if (client)
	{
		if (client < 1 || client > MaxClients)
		{
			ThrowError("Invalid client index %d", client);
		}
		
		if (!IsClientConnected(client))
		{
			ThrowError("Client %i is not connected", client);
		}
				
		AdminId adminId = GetUserAdmin(client);
		if (adminId == INVALID_ADMIN_ID || !GetAdminFlag(adminId, Admin_Generic, Access_Effective))
		{
			signUser = "PLAYER";
		}
		
		SetGlobalTransTarget(client);
		VFormat(buffer, sizeof(buffer), format, 5);
		CRemoveTags(buffer, sizeof(buffer));
		PrintToConsole(client, "%s%s", tag, buffer);
	}
	else
	{
		SetGlobalTransTarget(LANG_SERVER);
		VFormat(buffer, sizeof(buffer), format, 5);
		CRemoveTags(buffer, sizeof(buffer));
		PrintToServer("%s%s", tag, buffer);
	}
	
	ConVar cvarActivity = FindConVar("sm_show_activity");
	if (!cvarActivity || !cvarActivity.BoolValue)
	{
		return;
	}
	
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientConnected(i) || IsFakeClient(i))
		{
			continue;
		}
		
		SetGlobalTransTarget(i);		
		AdminId adminId = GetUserAdmin(i);
		VFormat(buffer, sizeof(buffer), format, 5);
		
		if (adminId == INVALID_ADMIN_ID || !GetAdminFlag(adminId, Admin_Generic, Access_Effective))
		{
			if ((cvarActivity.IntValue & kActivityNonAdmins) || (cvarActivity.IntValue & kActivityNonAdminsNames))
			{
				if (cvarActivity.IntValue & kActivityNonAdminsNames || i == client)
				{
					CPrintToChat_Ex(i, author, true, "%s%N: %s", tag, client, buffer);
				}
				else
				{
					CPrintToChat_Ex(i, author, true, "%s%s: %s", tag, signUser, buffer);
				}
			}
		}
		else
		{
			bool rootAccess = GetAdminFlag(adminId, Admin_Root, Access_Effective);
			if ((cvarActivity.IntValue & kActivityAdmins) 
				|| (cvarActivity.IntValue & kActivityAdminsNames) 
				|| ((cvarActivity.IntValue & kActivityRootNames) && rootAccess))
			{
				if ((cvarActivity.IntValue & kActivityAdminsNames) 
					|| ((cvarActivity.IntValue & kActivityRootNames) && rootAccess)
					|| i == client)
				{
					CPrintToChat_Ex(i, author, true, "%s%N: %s", tag, client, buffer);
				}
				else
				{
					CPrintToChat_Ex(i, author, true, "%s%s: %s", tag, signUser, buffer);
				}
			}
		}
	}
}

/**
 * Prepares a string to display the message correctly in the chat.
 *
 * @param message   The string.
 * @param maxlen    The maximum length of the string.
 * @return          First free index in the string.
 */
stock int CPreFormat(char[] message, int maxlen)
{
	if (GetEngineVersion() == Engine_CSGO)
	{
		return Format(message, maxlen, " \x01");
	}
	
	return Format(message, maxlen, "\x01");
}

/**
 * Replace color tags from a string with actual color values.
 *
 * @param message   The string.
 * @param maxlen    The maximum length of the string.
 * @return          Number of cells written.
 */
stock int CFormat(char[] format, int maxlen)
{
	if (IsSource2009())
	{
		return MC_Format(format, maxlen);
	}
	
	return C_Format(format, maxlen);
}

/**
 * Remove color tags from a string.
 *
 * @param message   The string.
 * @param maxlen    The maximum length of the string.
 * @return          The new size of the string.
 */
stock int CRemoveTags(char[] format, int maxlen)
{
	if (IsSource2009())
	{
		return MC_RemoveTags(format, maxlen);
	}
	
	return C_RemoveTags(format, maxlen);
}

/**
 * Remove colors from a string.
 *
 * @param message   The string.
 * @param maxlen    The maximum length of the string.
 * @return          The new size of the string.
 */
stock int CRemoveColors(char[] format, int maxlen)
{
	if (IsSource2009())
	{
		return MC_RemoveColors(format, maxlen);
	}
	
	return C_RemoveColors(format, maxlen);
}

stock void CSendMessage(int client, const char[] message, int author = -1, bool chatMessage = false)
{
	if (IsSource2009())
	{
		MC_SendMessage(client, message, author, chatMessage);
	}
	else
	{
		C_SendMessage(client, message, author, chatMessage);
	}
}

stock bool IsSource2009()
{
	EngineVersion engineVersion = GetEngineVersion();
	return (engineVersion == Engine_CSS 
		|| engineVersion == Engine_HL2DM 
		|| engineVersion == Engine_DODS 
		|| engineVersion == Engine_TF2);
}