#if defined _sourcecolors_included
    #endinput
#endif
#define _sourcecolors_included

#define MAX_MESSAGE_LENGTH        256

#define kActivityNone                  0
#define kActivityNonAdmins             1
#define kActivityNonAdminsNames        2
#define kActivityAdmins                4
#define kActivityAdminsNames           8
#define kActivityRootNames             16

#include <sourcecolors/morecolors>
#include <sourcecolors/colors>

/**
 * Prints a message to a specific client in the chat area.
 * 
 * @param client        Client's index.
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 * @error               Invalid client index, client not connected.
 */
stock void CPrintToChat(int client, const char[] format, any ...)
{
	if (client < 1 || client > MaxClients)
	{
		ThrowError("Invalid client index %d", client);
	}
	
	if (!IsClientConnected(client))
	{
		ThrowError("Client %d is not connected", client);
	}
	
	SetGlobalTransTarget(client);
	
	char buffer[MAX_MESSAGE_LENGTH];
	VFormat(buffer, sizeof(buffer), format, 3);
	
	CPreFormat(buffer, sizeof(buffer));
	CFormat(buffer, sizeof(buffer));
	CSendMessage(client, buffer);
}

/**
 * Prints a message to a specific client in the chat area.
 *
 * @param client             Client's index.
 * @param author             Author's index.
 * @param chatMessage        Regular chat message?
 * @param format             Formatting rules.
 * @param ...                Variable number of format parameters.
 * @error                    Invalid client index, client not connected, invalid author index, author not connected.
 */
stock void CPrintToChat_Ex(int client, int author, bool chatMessage, const char[] format, any ...)
{
	if (client < 1 || client > MaxClients)
	{
		ThrowError("Invalid client index %d", client);
	}
	
	if (!IsClientConnected(client))
	{
		ThrowError("Client %d is not connected", client);
	}
	
	if (author)
	{
		if (author < 1 || author > MaxClients)
		{
			ThrowError("Invalid author index %d", author);
		}
		
		if (!IsClientConnected(author))
		{
			ThrowError("Author %d is not connected", author);
		}
	}
	
	SetGlobalTransTarget(client);
	
	char buffer[MAX_MESSAGE_LENGTH];
	VFormat(buffer, sizeof(buffer), format, 5);
	
	CPreFormat(buffer, sizeof(buffer));
	CFormat(buffer, sizeof(buffer));
	CSendMessage(client, buffer, author, chatMessage);
}

/**
 * Prints a message to all clients in the chat area.
 * 
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
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
		VFormat(buffer, sizeof(buffer), format, 2);
		
		CPreFormat(buffer, sizeof(buffer));
		CFormat(buffer, sizeof(buffer));
		CSendMessage(i, buffer);
	}
}

/**
 * Prints a message to all clients in the chat area.
 *
 * @param author             Author's index.
 * @param chatMessage        Regular chat message?
 * @param format             Formatting rules.
 * @param ...                Variable number of format parameters.
 * @error                    Invalid author index, author not connected.
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
			ThrowError("Author %d is not connected", author);
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
		VFormat(buffer, sizeof(buffer), format, 4);
		
		CPreFormat(buffer, sizeof(buffer));
		CFormat(buffer, sizeof(buffer));
		CSendMessage(i, buffer, author, chatMessage);
	}
}

/**
 * Prints a message to all clients from a specific team in the chat area.
 * 
 * @param team          Team's index.
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
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
		VFormat(buffer, sizeof(buffer), format, 3);
		
		CPreFormat(buffer, sizeof(buffer));
		CFormat(buffer, sizeof(buffer));
		CSendMessage(i, buffer);
	}
}

/**
 * Prints a message to all clients from a specific team in the chat area.
 *
 * @param team               Team's index.
 * @param author             Author's index.
 * @param chatMessage        Regular chat message?
 * @param format             Formatting rules.
 * @param ...                Variable number of format parameters.
 * @error                    Invalid author index, author not connected.
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
			ThrowError("Author %d is not connected", author);
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
		VFormat(buffer, sizeof(buffer), format, 5);
		
		CPreFormat(buffer, sizeof(buffer));
		CFormat(buffer, sizeof(buffer));
		CSendMessage(i, buffer, author, chatMessage);
	}
}

/**
 * Replies to a message in a command.
 *
 * @param client        Client's index.
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 * @error               Invalid client index, client not connected.
 */
stock void CReplyToCommand(int client, const char[] format, any ...)
{	
	if (client)
	{
		if (client < 1 || client > MaxClients)
		{
			ThrowError("Invalid client index %d", client);
		}
		
		if (!IsClientConnected(client))
		{
			ThrowError("Client %d is not connected", client);
		}
		
		SetGlobalTransTarget(client);
		
		char buffer[MAX_MESSAGE_LENGTH];
		VFormat(buffer, sizeof(buffer), format, 3);
		
		if (GetCmdReplySource() == SM_REPLY_TO_CONSOLE)
		{
			CRemoveTags(buffer, sizeof(buffer));
			PrintToConsole(client, buffer);
		}
		else
		{		
			CPreFormat(buffer, sizeof(buffer));
			CFormat(buffer, sizeof(buffer));
			CSendMessage(client, buffer);
		}
	}
	else
	{
		SetGlobalTransTarget(LANG_SERVER);
		
		char buffer[MAX_MESSAGE_LENGTH];
		VFormat(buffer, sizeof(buffer), format, 3);
		
		CRemoveTags(buffer, sizeof(buffer));
		PrintToServer(buffer);
	}
}

/**
 * Replies to a message in a command.
 *
 * @param client             Client's index.
 * @param author             Author's index.
 * @param chatMessage        Regular chat message?
 * @param format             Formatting rules.
 * @param ...                Variable number of format parameters.
 * @error                    Invalid client index, client not connected, invalid author index, author not connected.
 */
stock void CReplyToCommand_Ex(int client, int author, bool chatMessage, const char[] format, any ...)
{
	if (author)
	{
		if (author < 1 || author > MaxClients)
		{
			ThrowError("Invalid author index %d", author);
		}
		
		if (!IsClientConnected(author))
		{
			ThrowError("Author %d is not connected", author);
		}
	}
	
	if (client)
	{
		if (client < 1 || client > MaxClients)
		{
			ThrowError("Invalid client index %d", client);
		}
		
		if (!IsClientConnected(client))
		{
			ThrowError("Client %d is not connected", client);
		}
		
		SetGlobalTransTarget(client);
		
		char buffer[MAX_MESSAGE_LENGTH];
		VFormat(buffer, sizeof(buffer), format, 5);
		
		if (GetCmdReplySource() == SM_REPLY_TO_CONSOLE)
		{
			CRemoveTags(buffer, sizeof(buffer));
			PrintToConsole(client, buffer);
		}
		else
		{
			CPreFormat(buffer, sizeof(buffer));
			CFormat(buffer, sizeof(buffer));
			CSendMessage(client, buffer, author, chatMessage);
		}
	}
	else
	{
		SetGlobalTransTarget(LANG_SERVER);
		
		char buffer[MAX_MESSAGE_LENGTH];
		VFormat(buffer, sizeof(buffer), format, 5);
		
		CRemoveTags(buffer, sizeof(buffer));
		PrintToServer(buffer);
	}
}

/**
 * Replies to a message in a command.
 *
 * @param client             Client's index.
 * @param replySource        ReplySource value.
 * @param format             Formatting rules.
 * @param ...                Variable number of format parameters.
 * @error                    Invalid client index, client not connected.
 */
stock void CReplyToCommandSource(int client, ReplySource replySource, const char[] format, any ...)
{	
	if (client)
	{
		if (client < 1 || client > MaxClients)
		{
			ThrowError("Invalid client index %d", client);
		}
		
		if (!IsClientConnected(client))
		{
			ThrowError("Client %d is not connected", client);
		}
		
		SetGlobalTransTarget(client);
		
		char buffer[MAX_MESSAGE_LENGTH];
		VFormat(buffer, sizeof(buffer), format, 4);
		
		if (replySource == SM_REPLY_TO_CONSOLE)
		{
			CRemoveTags(buffer, sizeof(buffer));
			PrintToConsole(client, buffer);
		}
		else
		{			
			CPreFormat(buffer, sizeof(buffer));
			CFormat(buffer, sizeof(buffer));
			CSendMessage(client, buffer);
		}
	}
	else
	{
		SetGlobalTransTarget(LANG_SERVER);
		
		char buffer[MAX_MESSAGE_LENGTH];
		VFormat(buffer, sizeof(buffer), format, 4);
		
		CRemoveTags(buffer, sizeof(buffer));
		PrintToServer(buffer);
	}
}

/**
 * Replies to a message in a command.
 *
 * @param client             Client's index.
 * @param author             Author's index.
 * @param chatMessage        Regular chat message?
 * @param replySource        ReplySource value.
 * @param format             Formatting rules.
 * @param ...                Variable number of format parameters.
 * @error                    Invalid client index, client not connected, invalid author index, author not connected.
 */
stock void CReplyToCommandSource_Ex(int client, int author, bool chatMessage, ReplySource replySource, const char[] format, any ...)
{
	if (author)
	{
		if (author < 1 || author > MaxClients)
		{
			ThrowError("Invalid author index %d", author);
		}
		
		if (!IsClientConnected(author))
		{
			ThrowError("Author %d is not connected", author);
		}
	}
	
	if (client)
	{
		if (client < 1 || client > MaxClients)
		{
			ThrowError("Invalid client index %d", client);
		}
		
		if (!IsClientConnected(client))
		{
			ThrowError("Client %d is not connected", client);
		}
		
		SetGlobalTransTarget(client);
		
		char buffer[MAX_MESSAGE_LENGTH];
		VFormat(buffer, sizeof(buffer), format, 6);
		
		if (replySource == SM_REPLY_TO_CONSOLE)
		{
			CRemoveTags(buffer, sizeof(buffer));
			PrintToConsole(client, buffer);
		}
		else
		{
			CPreFormat(buffer, sizeof(buffer));
			CFormat(buffer, sizeof(buffer));
			CSendMessage(client, buffer, author, chatMessage);
		}
	}
	else
	{
		SetGlobalTransTarget(LANG_SERVER);
		
		char buffer[MAX_MESSAGE_LENGTH];
		VFormat(buffer, sizeof(buffer), format, 6);
		
		CRemoveTags(buffer, sizeof(buffer));
		PrintToServer(buffer);
	}
}

/**
 * Displays usage of an admin command to users depending on the 
 * setting of the sm_show_activity cvar. All users receive a message 
 * in their chat text, except for the originating client, who receives 
 * the message both in chat and console.
 *
 * @param client        Client's index.
 * @param tag           Tag to prepend to the message.
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 * @error               Invalid client index, client not connected.
 */
stock void CShowActivity(int client, const char[] tag, const char[] format, any ...)
{
	char clientName[MAX_NAME_LENGTH];
	char signUser[MAX_MESSAGE_LENGTH];
	
	if (client)
	{
		if (client < 1 || client > MaxClients)
		{
			ThrowError("Invalid client index %d", client);
		}
		
		if (!IsClientConnected(client))
		{
			ThrowError("Client %d is not connected", client);
		}
		
		GetClientName(client, clientName, sizeof(clientName));
		
		AdminId adminId = GetUserAdmin(client);
		if (adminId != INVALID_ADMIN_ID && GetAdminFlag(adminId, Admin_Generic, Access_Effective))
		{
			strcopy(signUser, sizeof(signUser), "ADMIN");
		}
		else
		{
			strcopy(signUser, sizeof(signUser), "PLAYER");
		}
		
		SetGlobalTransTarget(client);
		
		char buffer[MAX_MESSAGE_LENGTH];
		VFormat(buffer, sizeof(buffer), format, 4);
		
		CRemoveTags(buffer, sizeof(buffer));
		PrintToConsole(client, "%s%s", tag, buffer);
	}
	else
	{
		strcopy(signUser, sizeof(signUser), "ADMIN");
		SetGlobalTransTarget(LANG_SERVER);
		
		char buffer[MAX_MESSAGE_LENGTH];
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
		
		char buffer[MAX_MESSAGE_LENGTH];
		VFormat(buffer, sizeof(buffer), format, 4);
		
		if (adminId == INVALID_ADMIN_ID || !GetAdminFlag(adminId, Admin_Generic, Access_Effective))
		{
			if ((cvarActivity.IntValue & kActivityNonAdmins) || (cvarActivity.IntValue & kActivityNonAdminsNames))
			{
				if (cvarActivity.IntValue & kActivityNonAdminsNames || i == client)
				{
					CPrintToChat_Ex(i, client, true, "%s%s: %s", tag, clientName, buffer);
				}
				else
				{
					CPrintToChat_Ex(i, client, true, "%s%s: %s", tag, signUser, buffer);
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
					CPrintToChat_Ex(i, client, true, "%s%s: %s", tag, clientName, buffer);
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
 * setting of the sm_show_activity cvar. All users receive a message 
 * in their chat text, except for the originating client, who receives 
 * the message both in chat and console.
 *
 * @param client        Client's index.
 * @param author        Author's index.
 * @param tag           Tag to prepend to the message.
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 * @error               Invalid client index, client not connected, invalid author index, author not connected.
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
			ThrowError("Author %d is not connected", author);
		}
	}
	
	char clientName[MAX_NAME_LENGTH];
	char signUser[MAX_MESSAGE_LENGTH];
	
	if (client)
	{
		if (client < 1 || client > MaxClients)
		{
			ThrowError("Invalid client index %d", client);
		}
		
		if (!IsClientConnected(client))
		{
			ThrowError("Client %d is not connected", client);
		}
		
		GetClientName(client, clientName, sizeof(clientName));
		
		AdminId adminId = GetUserAdmin(client);
		if (adminId != INVALID_ADMIN_ID && GetAdminFlag(adminId, Admin_Generic, Access_Effective))
		{
			strcopy(signUser, sizeof(signUser), "ADMIN");
		}
		else
		{
			strcopy(signUser, sizeof(signUser), "PLAYER");
		}
		
		SetGlobalTransTarget(client);
		
		char buffer[MAX_MESSAGE_LENGTH];
		VFormat(buffer, sizeof(buffer), format, 5);
		
		CRemoveTags(buffer, sizeof(buffer));
		PrintToConsole(client, "%s%s", tag, buffer);
	}
	else
	{
		strcopy(signUser, sizeof(signUser), "ADMIN");
		SetGlobalTransTarget(LANG_SERVER);
		
		char buffer[MAX_MESSAGE_LENGTH];
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
		
		char buffer[MAX_MESSAGE_LENGTH];
		VFormat(buffer, sizeof(buffer), format, 5);
		
		if (adminId == INVALID_ADMIN_ID || !GetAdminFlag(adminId, Admin_Generic, Access_Effective))
		{
			if ((cvarActivity.IntValue & kActivityNonAdmins) || (cvarActivity.IntValue & kActivityNonAdminsNames))
			{
				if (cvarActivity.IntValue & kActivityNonAdminsNames || i == client)
				{
					CPrintToChat_Ex(i, author, true, "%s%s: %s", tag, clientName, buffer);
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
					CPrintToChat_Ex(i, author, true, "%s%s: %s", tag, clientName, buffer);
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
 * Displays usage of an admin command to users depending on the 
 * setting of the sm_show_activity cvar. All users receive a message 
 * in their chat text, except for the originating client, who receives 
 * the message both in chat and console.
 *
 * @param clientName        Client's name.
 * @param adminId           Client's admin ID.
 * @param tag               Tag to prepend to the message.
 * @param format            Formatting rules.
 * @param ...               Variable number of format parameters.
 */
stock void CShowActivityAdmin(char[] clientName, AdminId adminId, const char[] tag, const char[] format, any ...)
{
	char signUser[MAX_MESSAGE_LENGTH];
	if (adminId != INVALID_ADMIN_ID && GetAdminFlag(adminId, Admin_Generic, Access_Effective))
	{
		strcopy(signUser, sizeof(signUser), "ADMIN");
	}
	else
	{
		strcopy(signUser, sizeof(signUser), "PLAYER");
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
		adminId = GetUserAdmin(i);
		
		char buffer[MAX_MESSAGE_LENGTH];
		VFormat(buffer, sizeof(buffer), format, 5);
		
		if (adminId == INVALID_ADMIN_ID || !GetAdminFlag(adminId, Admin_Generic, Access_Effective))
		{
			if ((cvarActivity.IntValue & kActivityNonAdmins) || (cvarActivity.IntValue & kActivityNonAdminsNames))
			{
				if (cvarActivity.IntValue & kActivityNonAdminsNames)
				{
					CPrintToChat_Ex(i, author, true, "%s%s: %s", tag, clientName, buffer);
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
					|| ((cvarActivity.IntValue & kActivityRootNames) && rootAccess))
				{
					CPrintToChat_Ex(i, author, true, "%s%s: %s", tag, clientName, buffer);
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
 * Displays usage of an admin command to users depending on the 
 * setting of the sm_show_activity cvar. All users receive a message 
 * in their chat text, except for the originating client, who receives 
 * the message both in chat and console.
 *
 * @param clientName        Client's name.
 * @param adminId           Client's admin ID.
 * @param author            Author's index.
 * @param tag               Tag to prepend to the message.
 * @param format            Formatting rules.
 * @param ...               Variable number of format parameters.
 * @error                   Invalid author index, author not connected.
 */
stock void CShowActivityAdmin_Ex(char[] clientName, AdminId adminId, int author, const char[] tag, const char[] format, any ...)
{
	if (author)
	{
		if (author < 1 || author > MaxClients)
		{
			ThrowError("Invalid author index %d", author);
		}
		
		if (!IsClientConnected(author))
		{
			ThrowError("Author %d is not connected", author);
		}
	}
	
	char signUser[MAX_MESSAGE_LENGTH];
	if (adminId != INVALID_ADMIN_ID && GetAdminFlag(adminId, Admin_Generic, Access_Effective))
	{
		strcopy(signUser, sizeof(signUser), "ADMIN");
	}
	else
	{
		strcopy(signUser, sizeof(signUser), "PLAYER");
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
		adminId = GetUserAdmin(i);
		
		char buffer[MAX_MESSAGE_LENGTH];
		VFormat(buffer, sizeof(buffer), format, 6);
		
		if (adminId == INVALID_ADMIN_ID || !GetAdminFlag(adminId, Admin_Generic, Access_Effective))
		{
			if ((cvarActivity.IntValue & kActivityNonAdmins) || (cvarActivity.IntValue & kActivityNonAdminsNames))
			{
				if (cvarActivity.IntValue & kActivityNonAdminsNames)
				{
					CPrintToChat(i, "%s%s: %s", tag, clientName, buffer);
				}
				else
				{
					CPrintToChat(i, "%s%s: %s", tag, signUser, buffer);
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
					|| ((cvarActivity.IntValue & kActivityRootNames) && rootAccess))
				{
					CPrintToChat(i, "%s%s: %s", tag, clientName, buffer);
				}
				else
				{
					CPrintToChat(i, "%s%s: %s", tag, signUser, buffer);
				}
			}
		}
	}
}

/**
 * Prepares a string to display the message correctly in the chat.
 *
 * @param message        The string.
 * @param maxlen         The maximum length of the string.
 * @return               First free index in the string.
 */
stock int CPreFormat(char[] message, int maxlen)
{
	if (GetEngineVersion() == Engine_CSGO)
	{
		return Format(message, maxlen, " \x01%s", message);
	}
	
	return Format(message, maxlen, "\x01%s", message);
}

/**
 * Replace color tags from a string with actual color values.
 *
 * @param message         The string.
 * @param maxlen          The maximum length of the string.
 * @return                Number of cells written.
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
 * @param message         The string.
 * @param maxlen          The maximum length of the string.
 * @return                The new size of the string.
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
 * @param message         The string.
 * @param maxlen          The maximum length of the string.
 * @return                The new size of the string.
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