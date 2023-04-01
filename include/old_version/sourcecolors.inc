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
	SourceColors_SendMessage(client, buffer);
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
	SourceColors_SendMessage(client, buffer, author, chatMessage);
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
		SourceColors_SendMessage(i, buffer);
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
		SourceColors_SendMessage(i, buffer, author, chatMessage);
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
		SourceColors_SendMessage(i, buffer);
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
		SourceColors_SendMessage(i, buffer, author, chatMessage);
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
			SourceColors_SendMessage(client, buffer);
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
			SourceColors_SendMessage(client, buffer, author, chatMessage);
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
			SourceColors_SendMessage(client, buffer);
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
			SourceColors_SendMessage(client, buffer, author, chatMessage);
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
 * in their chat text.
 *
 * @param client        Client's index.
 * @param tag           Tag to prepend to the message.
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 * @error               Invalid client index, client not connected.
 */
stock void CShowActivity(int client, const char[] tag, const char[] format, any ...)
{
	char signUser[128];
	char clientName[MAX_NAME_LENGTH];
	
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
 * in their chat text.
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
	
	char signUser[128];
	char clientName[MAX_NAME_LENGTH];
	
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
 * in their chat text.
 *
 * @param adminName        Admin's name.
 * @param adminId          Admin's AdminId.
 * @param tag              Tag to prepend to the message.
 * @param format           Formatting rules.
 * @param ...              Variable number of format parameters.
 */
stock void CShowActivityAdmin(const char[] adminName, AdminId adminId, const char[] tag, const char[] format, any ...)
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
					CPrintToChat_Ex(i, 0, true, "%s%s: %s", tag, adminName, buffer);
				}
				else
				{
					CPrintToChat_Ex(i, 0, true, "%s%s: %s", tag, signUser, buffer);
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
					CPrintToChat_Ex(i, 0, true, "%s%s: %s", tag, adminName, buffer);
				}
				else
				{
					CPrintToChat_Ex(i, 0, true, "%s%s: %s", tag, signUser, buffer);
				}
			}
		}
	}
}

/**
 * Displays usage of an admin command to users depending on the 
 * setting of the sm_show_activity cvar. All users receive a message 
 * in their chat text.
 *
 * @param adminName        Admin's name.
 * @param adminId          Admin's AdminId.
 * @param author           Author's index.
 * @param tag              Tag to prepend to the message.
 * @param format           Formatting rules.
 * @param ...              Variable number of format parameters.
 * @error                  Invalid author index, author not connected.
 */
stock void CShowActivityAdmin_Ex(const char[] adminName, AdminId adminId, int author, const char[] tag, const char[] format, any ...)
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
					CPrintToChat_Ex(i, author, true, "%s%s: %s", tag, adminName, buffer);
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
					CPrintToChat_Ex(i, author, true, "%s%s: %s", tag, adminName, buffer);
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
 * @param buffer        The string.
 * @param maxlen        The maximum length of the string.
 * @return              First free index in the string.
 */
stock int CPreFormat(char[] buffer, int maxLen)
{
	if (GetEngineVersion() == Engine_CSGO)
	{
		return Format(buffer, maxLen, " \x01%s", buffer);
	}
	
	return Format(buffer, maxLen, "\x01%s", buffer);
}

/**
 * Replaces color tags from a string with actual color values.
 *
 * @param buffer        The string.
 * @param maxLen        The maximum length of the string.
 * @return              Number of cells written.
 */
stock int CFormat(char[] buffer, int maxLen)
{
	int index;
	char newBuffer[MAX_MESSAGE_LENGTH];
	bool isSource2009 = SourceColors_IsSource2009();
	
	for (int i = 0; buffer[i] && i < maxLen; i++)
	{
		if (buffer[i] == '{' && !strncmp(buffer[i + 1], "color:", 6, false))
		{
			int pos;
			char color[MAX_MESSAGE_LENGTH];
			
			for (int j = i + 7; buffer[j] && j < maxLen; j++)
			{
				if (buffer[j] == '}')
				{
					break;
				}
				
				color[pos++] = buffer[j];
			}
			
			if (pos && i + pos < maxLen)
			{
				if (buffer[i + 7] == '#' && isSource2009)
				{
					if (i + 8 < maxLen)
					{
						if (pos == 7)
						{
							index += FormatEx(newBuffer[index], sizeof(newBuffer) - index, "\x07%s", color[1]);
						}
						else if (pos == 9)
						{
							index += FormatEx(newBuffer[index], sizeof(newBuffer) - index, "\x08%s", color[1]);
						}
						
						i += pos + 7;
						continue;
					}
				}
				else
				{					
					int len = SourceColors_GetColor(newBuffer[index], sizeof(newBuffer) - index, color, isSource2009);
					if (len)
					{
						index += len;
					}
					
					i += pos + 7;
					continue;
				}
			}
		}
		
		newBuffer[index] = buffer[i];
		index++;
	}
	
	return strcopy(buffer, maxLen, newBuffer);
}

/**
 * Removes color tags from a string.
 *
 * @param buffer        The string.
 * @param maxLen        The maximum length of the string.
 * @return              The new size of the string.
 */
stock int CRemoveTags(char[] buffer, int maxLen)
{
	int index;
	char newBuffer[MAX_MESSAGE_LENGTH];
	bool isSource2009 = SourceColors_IsSource2009();
	
	for (int i = 0; buffer[i] && i < maxLen; i++)
	{
		if (buffer[i] == '{' && !strncmp(buffer[i + 1], "color:", 6, false))
		{
			int pos;
			char color[MAX_MESSAGE_LENGTH];
			
			for (int j = i + 7; buffer[j] && j < maxLen; j++)
			{
				if (buffer[j] == '}')
				{
					break;
				}
				
				color[pos++] = buffer[j];
			}
			
			if (pos && i + pos < maxLen)
			{
				if (buffer[i + 7] == '#' && isSource2009)
				{
					if (i + 8 < maxLen)
					{
						i += pos + 7;
						continue;
					}
				}
				else
				{
					i += pos + 7;
					continue;
				}
			}
		}
		
		newBuffer[index] = buffer[i];
		index++;
	}
	
	return strcopy(buffer, maxLen, newBuffer);
}

/**
 * Removes colors from a string.
 *
 * @param buffer        The string.
 * @param maxLen        The maximum length of the string.
 * @return              The new size of the string.
 */
stock int CRemoveColors(char[] buffer, int maxLen)
{
	int index;
	char newBuffer[MAX_MESSAGE_LENGTH];
	
	for (int i = 0; buffer[i] && i < maxLen; i++)
	{
		if (buffer[i] >= 0x01 && buffer[i] <= 0x10)
		{
			continue;
		}
		
		newBuffer[index] = buffer[i];
		index++;
	}
	
	return strcopy(buffer, maxLen, newBuffer);
}

void SourceColors_SendMessage(int client, const char[] message, int author = -1, bool chatMessage = false)
{
	if (author == -1)
	{
		author = client;
	}
	
	Handle userMsg = StartMessageOne("SayText2", client, USERMSG_RELIABLE | USERMSG_BLOCKHOOKS);
	if (userMsg)
	{
		if (GetFeatureStatus(FeatureType_Native, "GetUserMessageType") == FeatureStatus_Available 
			&& GetUserMessageType() == UM_Protobuf)
		{
			PbSetInt(userMsg, "ent_idx", author);
			PbSetBool(userMsg, "chat", chatMessage);
			PbSetString(userMsg, "msg_name", message);
			PbAddString(userMsg, "params", "");
			PbAddString(userMsg, "params", "");
			PbAddString(userMsg, "params", "");
			PbAddString(userMsg, "params", "");
		}
		else
		{
			BfWriteByte(userMsg, author);
			BfWriteByte(userMsg, chatMessage);
			BfWriteString(userMsg, message);
		}
		
		EndMessage();
	}
	else
	{
		char buffer[MAX_MESSAGE_LENGTH];
		strcopy(buffer, sizeof(buffer), message);

		if (GetEngineVersion() == Engine_DODS)
		{
			int authorTeam = IsClientInGame(author) ? GetClientTeam(author) : 0;
			switch (authorTeam)
			{
				case 0:
				{
					ReplaceString(buffer, sizeof(buffer), "\x03", "\x01", false);
				}
				
				case 1:
				{
					ReplaceString(buffer, sizeof(buffer), "\x03", "\x07CCCCCC", false);
				}
				
				case 2:
				{
					ReplaceString(buffer, sizeof(buffer), "\x03", "\x074D7942", false);
				}
				
				case 3:
				{
					ReplaceString(buffer, sizeof(buffer), "\x03", "\x07FF4040", false);
				}
			}
		}
		
		PrintToChat(client, "%s", buffer);
	}
}

bool SourceColors_IsSource2009()
{
	EngineVersion engineVersion = GetEngineVersion();
	return (engineVersion == Engine_CSS 
		|| engineVersion == Engine_HL2DM 
		|| engineVersion == Engine_DODS 
		|| engineVersion == Engine_TF2);
}

int SourceColors_GetColor(char[] colorHex, int maxLen, const char[] colorTag, bool isSource2009)
{
	if (isSource2009)
	{
		if (colorTag[0] == 'd')
		{
			if (StrEqual(colorTag, "default", false))
			{
				return strcopy(colorHex, maxLen, "\x01");
			}
		}
		else if (colorTag[0] == 't')
		{
			if (StrEqual(colorTag, "team", false))
			{
				return strcopy(colorHex, maxLen, "\x03");
			}
		}
	}
	else
	{
		if (colorTag[0] == 'b')
		{
			if (StrEqual(colorTag, "blue", false))
			{
				return strcopy(colorHex, maxLen, "\x0B");
			}
			else if (StrEqual(colorTag, "bluegrey", false))
			{
				return strcopy(colorHex, maxLen, "\x0A");
			}
		}
		else if (colorTag[0] == 'd')
		{
			if (StrEqual(colorTag, "darkblue", false))
			{
				return strcopy(colorHex, maxLen, "\x0C");
			}
			else if (StrEqual(colorTag, "darkred", false))
			{
				return strcopy(colorHex, maxLen, "\x02");
			}
			else if (StrEqual(colorTag, "default", false))
			{
				return strcopy(colorHex, maxLen, "\x01");
			}
		}
		else if (colorTag[0] == 'g')
		{
			if (StrEqual(colorTag, "green", false))
			{
				return strcopy(colorHex, maxLen, "\x04");
			}
			else if (StrEqual(colorTag, "grey", false))
			{
				return strcopy(colorHex, maxLen, "\x08");
			}
			else if (StrEqual(colorTag, "grey2", false))
			{
				return strcopy(colorHex, maxLen, "\x0D");
			}
		}
		else if (colorTag[0] == 'l')
		{
			if (StrEqual(colorTag, "lightgreen", false))
			{
				return strcopy(colorHex, maxLen, "\x05");
			}
			else if (StrEqual(colorTag, "lightred", false))
			{
				return strcopy(colorHex, maxLen, "\x0F");
			}
			else if (StrEqual(colorTag, "lime", false))
			{
				return strcopy(colorHex, maxLen, "\x06");
			}
		}
		else if (colorTag[0] == 'o')
		{
			if (StrEqual(colorTag, "orange", false))
			{
				return strcopy(colorHex, maxLen, "\x10");
			}
			else if (StrEqual(colorTag, "orchid", false))
			{
				return strcopy(colorHex, maxLen, "\x0E");
			}
		}
		else if (colorTag[0] == 'r')
		{
			if (StrEqual(colorTag, "red", false))
			{
				return strcopy(colorHex, maxLen, "\x07");
			}
		}
		else if (colorTag[0] == 't')
		{
			if (StrEqual(colorTag, "team", false))
			{
				return strcopy(colorHex, maxLen, "\x03");
			}
		}
		else if (colorTag[0] == 'y')
		{
			if (StrEqual(colorTag, "yellow", false))
			{
				return strcopy(colorHex, maxLen, "\x09");
			}
		}
	}
	
	return 0;
}
