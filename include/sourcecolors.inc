#if defined _sourcecolors_included
    #endinput
#endif
#define _sourcecolors_included

#define SOURCECOLORS_AUTHOR_RECEIVER        -1

#define SOURCECOLORS_MAX_CHAT_ID               32767
#define SOURCECOLORS_MAX_MESSAGE_LENGTH        256

int SOURCECOLORS_CHAT_MESSAGE_ID;
int SOURCECOLORS_CHAT_PARAM_AUTHOR_ID;
int SOURCECOLORS_CHAT_PARAM_MESSAGE_ID;

/**
 * Retrieves the chat parameters for the following message (sent by a function from this library).
 * 
 * @param author        Author's index (0 = server, SOURCECOLORS_AUTHOR_RECEIVER if the author is the receiver).
 * @return              True if the chat parameters are set for the following message, false otherwise.
 */
stock bool CGetChatTextParams(int& author)
{
	int paramId = SOURCECOLORS_CHAT_MESSAGE_ID + 1;
	if (paramId > SOURCECOLORS_MAX_CHAT_ID)
	{
		paramId = 1;
	}
	
	return SourceColors_GetChatTextParams(paramId, author);
}

/**
 * Sets the chat parameters for the following message (sent by a function from this library).
 * 
 * @param author        Author's index (0 = server, SOURCECOLORS_AUTHOR_RECEIVER to set the receiver as the author).
 * @error               Invalid author index or author not connected.
 */
stock void CSetChatTextParams(int author)
{
	if (author && author != SOURCECOLORS_AUTHOR_RECEIVER)
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
	
	if (author && author != SOURCECOLORS_AUTHOR_RECEIVER)
	{
		SOURCECOLORS_CHAT_PARAM_AUTHOR_ID = GetClientUserId(author);
	}
	else
	{
		SOURCECOLORS_CHAT_PARAM_AUTHOR_ID = author;
	}
	
	SOURCECOLORS_CHAT_PARAM_MESSAGE_ID = SOURCECOLORS_CHAT_MESSAGE_ID + 1;
	if (SOURCECOLORS_CHAT_PARAM_MESSAGE_ID > SOURCECOLORS_MAX_CHAT_ID)
	{
		SOURCECOLORS_CHAT_PARAM_MESSAGE_ID = 1;
	}
}

/**
 * Resets the chat parameters for the following message (sent by a function from this library).
 */
stock void CResetChatTextParams()
{
	SOURCECOLORS_CHAT_PARAM_MESSAGE_ID = 0;
}

/**
 * Prints a message to a specific client in the chat area.
 * 
 * @param client        Client's index.
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 * @error               Invalid client index or client not connected.
 */
stock void CPrintToChat(int client, const char[] format, any ...)
{
	SOURCECOLORS_CHAT_MESSAGE_ID++;
	if (SOURCECOLORS_CHAT_MESSAGE_ID > SOURCECOLORS_MAX_CHAT_ID)
	{
		SOURCECOLORS_CHAT_MESSAGE_ID = 1;
	}
	
	if (client < 1 || client > MaxClients)
	{
		ThrowError("Invalid client index %d", client);
	}
	
	if (!IsClientConnected(client))
	{
		ThrowError("Client %d is not connected", client);
	}
	
	int author = SOURCECOLORS_AUTHOR_RECEIVER;
	char buffer[SOURCECOLORS_MAX_MESSAGE_LENGTH];
	
	SourceColors_GetChatTextParams(SOURCECOLORS_CHAT_MESSAGE_ID, author);
	
	SetGlobalTransTarget(client);
	VFormat(buffer, sizeof(buffer), format, 3);
	
	SourceColors_PrintToChat(client, author, " \x01%s", buffer);
}

/**
 * Prints a message to all clients in the chat area.
 * 
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 */
stock void CPrintToChatAll(const char[] format, any ...)
{
	SOURCECOLORS_CHAT_MESSAGE_ID++;
	if (SOURCECOLORS_CHAT_MESSAGE_ID > SOURCECOLORS_MAX_CHAT_ID)
	{
		SOURCECOLORS_CHAT_MESSAGE_ID = 1;
	}
	
	int author = SOURCECOLORS_AUTHOR_RECEIVER;
	char buffer[SOURCECOLORS_MAX_MESSAGE_LENGTH];
	
	SourceColors_GetChatTextParams(SOURCECOLORS_CHAT_MESSAGE_ID, author);
	
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientConnected(i) || IsFakeClient(i))
		{
			continue;
		}
		
		SetGlobalTransTarget(i);
		VFormat(buffer, sizeof(buffer), format, 2);
		
		SourceColors_PrintToChat(i, author, " \x01%s", buffer);
	}
}

/**
 * Replies to a command.
 * 
 * @param client        Client's index (0 = server).
 * @param format        Formatting rules.
 * @param ...           Variable number of format parameters.
 * @error               Invalid client index or client not connected.
 */
stock void CReplyToCommand(int client, const char[] format, any ...)
{
	SOURCECOLORS_CHAT_MESSAGE_ID++;
	if (SOURCECOLORS_CHAT_MESSAGE_ID > SOURCECOLORS_MAX_CHAT_ID)
	{
		SOURCECOLORS_CHAT_MESSAGE_ID = 1;
	}
	
	int author = SOURCECOLORS_AUTHOR_RECEIVER;
	char buffer[SOURCECOLORS_MAX_MESSAGE_LENGTH];
	
	SourceColors_GetChatTextParams(SOURCECOLORS_CHAT_MESSAGE_ID, author);
	
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
		VFormat(buffer, sizeof(buffer), format, 3);
		
		if (GetCmdReplySource() == SM_REPLY_TO_CONSOLE)
		{
			SourceColors_PrintToConsole(client, buffer);
		}
		else
		{
			SourceColors_PrintToChat(client, author, " \x01%s", buffer);
		}
	}
	else
	{
		SetGlobalTransTarget(client);
		VFormat(buffer, sizeof(buffer), format, 3);
		
		SourceColors_PrintToConsole(client, buffer);
	}
}

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
stock void CShowActivity(int client, const char[] tag, const char[] format, any ...)
{
	SOURCECOLORS_CHAT_MESSAGE_ID++;
	if (SOURCECOLORS_CHAT_MESSAGE_ID > SOURCECOLORS_MAX_CHAT_ID)
	{
		SOURCECOLORS_CHAT_MESSAGE_ID = 1;
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
	}
	
	int author = SOURCECOLORS_AUTHOR_RECEIVER;
	
	char name[MAX_NAME_LENGTH];
	char buffer[SOURCECOLORS_MAX_MESSAGE_LENGTH];
	
	SourceColors_GetChatTextParams(SOURCECOLORS_CHAT_MESSAGE_ID, author);
	
	SetGlobalTransTarget(client);
	VFormat(buffer, sizeof(buffer), format, 4);
	
	if (client)
	{
		SourceColors_PrintToChat(client, author, " \x01%s%s", tag, buffer);
	}
	
	SourceColors_PrintToConsole(client, "%s%s", tag, buffer);
	
	for (int i = 1; i <= MaxClients; i++)
	{
		if (i == client 
			|| !IsClientConnected(i) 
			|| !FormatActivitySource(client, i, name, sizeof(name)))
		{
			continue;
		}
		
		SetGlobalTransTarget(i);
		VFormat(buffer, sizeof(buffer), format, 4);
		
		SourceColors_PrintToChat(i, author, " \x01%s%s: %s", tag, name, buffer);
	}
}

/**
 * Formats a string by replacing color tags with color values.
 * 
 * @param buffer           Destination string buffer.
 * @param maxlength        Maximum length of the string buffer.
 * @return                 The number of characters written.
 */
stock int CFormat(char[] buffer, int maxlength)
{
	int j;
	int len;
	
	char color[SOURCECOLORS_MAX_MESSAGE_LENGTH];
	char newBuffer[SOURCECOLORS_MAX_MESSAGE_LENGTH];
	
	for (int i = 0; buffer[i] && j < maxlength; i++)
	{
		if (!strncmp(buffer[i], "{color:", 7, true) 
			&& (len = FindCharInString(buffer[i + 7], '}')) != -1)
		{
			strcopy(color, len + 1, buffer[i + 7]);
			TrimString(color);
			
			i += len + 7;
			
			if ((len = CGetColor(color, newBuffer[j], sizeof(newBuffer) - j - 1)))
			{
				j += len;
			}
		}
		else
		{
			newBuffer[j] = buffer[i];
			j++;
		}
	}
	
	return strcopy(buffer, maxlength, newBuffer);
}

/**
 * Removes color tags from a string.
 * 
 * @param buffer           Destination string buffer.
 * @param maxlength        Maximum length of the string buffer.
 * @return                 The number of characters written.
 */
stock int CRemoveTags(char[] buffer, int maxlength)
{
	int j;
	int len;
	
	char newBuffer[SOURCECOLORS_MAX_MESSAGE_LENGTH];
	
	for (int i = 0; buffer[i] && j < maxlength; i++)
	{
		if (!strncmp(buffer[i], "{color:", 7, true) 
			&& (len = FindCharInString(buffer[i + 7], '}')) != -1)
		{
			i += len + 7;
		}
		else
		{
			newBuffer[j] = buffer[i];
			j++;
		}
	}
	
	return strcopy(buffer, maxlength, newBuffer);
}

/**
 * Retrieves a color's value from a color's tag value.
 * 
 * @param color            Color's tag value.
 * @param buffer           Buffer to store the color's value.
 * @param maxlength        Maximum length of the buffer.
 * @return                 The number of characters written.
 */
stock int CGetColor(const char[] color, char[] buffer, int maxlength)
{
	int len;
	EngineVersion engineVersion = GetEngineVersion();
	
	bool canUseHexColors = (engineVersion == Engine_CSS 
		|| engineVersion == Engine_HL2DM 
		|| engineVersion == Engine_DODS 
		|| engineVersion == Engine_TF2 
		|| engineVersion == Engine_SDK2013);
	
	if (canUseHexColors)
	{
		len = SourceColors_GetColorFromHex(color, buffer, maxlength);
		if (len)
		{
			return len;
		}
		
		len = SourceColors_GetColorFromRGB(color, buffer, maxlength);
		if (len)
		{
			return len;
		}
	}
	
	StringMap map = new StringMap();
	
	map.SetString("default", "\x01");
	map.SetString("team", "\x03");
	
	if (canUseHexColors)
	{
		map.SetString("black", "\x07000000");
		map.SetString("blue", "\x070000FF");
		map.SetString("bronze", "\x07CD7F32");
		map.SetString("brown", "\x07A52A2A");
		map.SetString("coral", "\x07FF7F50");
		map.SetString("crimson", "\x07DC143C");
		map.SetString("cyan", "\x0700FFFF");
		map.SetString("emerald", "\x0750C878");
		map.SetString("gold", "\x07FFD700");
		map.SetString("gray", "\x07808080");
		map.SetString("green", "\x0700FF00");
		map.SetString("grey", "\x07808080");
		map.SetString("lime", "\x07BFFF00");
		map.SetString("magenta", "\x07FF00FF");
		map.SetString("maroon", "\x07800000");
		map.SetString("navy", "\x07000080");
		map.SetString("olive", "\x07808000");
		map.SetString("orange", "\x07FFA500");
		map.SetString("pink", "\x07FFC0CB");
		map.SetString("purple", "\x07800080");
		map.SetString("red", "\x07FF0000");
		map.SetString("silver", "\x07C0C0C0");
		map.SetString("teal", "\x07008080");
		map.SetString("tomato", "\x07FF6347");
		map.SetString("turquoise", "\x0730D5C8");
		map.SetString("white", "\x07FFFFFF");
		map.SetString("yellow", "\x07FFFF00");
		
		if (engineVersion == Engine_CSS)
		{
			map.SetString("team_spec", "\x07CCCCCC");
			map.SetString("team_t", "\x07FF4040");
			map.SetString("team_ct", "\x0799CCFF");
		}
		else if (engineVersion == Engine_DODS)
		{
			map.SetString("team_spec", "\x07CCCCCC");
			map.SetString("team_allies", "\x074D7942");
			map.SetString("team_axis", "\x07FF4040");
		}
		if (engineVersion == Engine_HL2DM || engineVersion == Engine_TF2)
		{
			map.SetString("team_spec", "\x07CCCCCC");
			map.SetString("team_red", "\x07FF4040");
			map.SetString("team_blue", "\x0799CCFF");
		}
	}
	else if (engineVersion == Engine_CSGO)
	{
		map.SetString("blue", "\x0B");
		map.SetString("bluegrey", "\x0A");
		map.SetString("darkblue", "\x0C");
		map.SetString("darkred", "\x02");
		map.SetString("green", "\x04");
		map.SetString("gray", "\x08");
		map.SetString("gray2", "\x0D");
		map.SetString("grey", "\x08");
		map.SetString("grey2", "\x0D");
		map.SetString("lightgreen", "\x05");
		map.SetString("lightred", "\x0F");
		map.SetString("lime", "\x06");
		map.SetString("red", "\x07");
		map.SetString("orange", "\x10");
		map.SetString("purple", "\x0E");
		map.SetString("yellow", "\x09");
	}
	else if (engineVersion == Engine_Left4Dead || engineVersion == Engine_Left4Dead2)
	{
		map.SetString("olive", "\x05");
		map.SetString("orange", "\x04");
	}
	
	map.GetString(color, buffer, maxlength, len);
	delete map;
	
	return len;
}

/**
 * Private function.
 */
stock void SourceColors_PrintToChat(int client, int author, const char[] format, any ...)
{
	if (author == SOURCECOLORS_AUTHOR_RECEIVER)
	{
		author = client;
	}
	
	char buffer[SOURCECOLORS_MAX_MESSAGE_LENGTH];
	VFormat(buffer, sizeof(buffer), format, 4);
	CFormat(buffer, sizeof(buffer));
	
	EngineVersion engineVersion = GetEngineVersion();
	bool canStartWithColor = engineVersion != Engine_CSGO;
	
	Handle userMessage = StartMessageOne("SayText2", client, USERMSG_RELIABLE | USERMSG_BLOCKHOOKS);
	if (userMessage)
	{
		if (GetUserMessageType() == UM_Protobuf)
		{
			PbSetInt(userMessage, "ent_idx", author);
			PbSetBool(userMessage, "chat", false);
			PbSetString(userMessage, "msg_name", buffer[view_as<int>(canStartWithColor)]);
			PbAddString(userMessage, "params", "");
			PbAddString(userMessage, "params", "");
			PbAddString(userMessage, "params", "");
			PbAddString(userMessage, "params", "");
		}
		else
		{
			BfWriteByte(userMessage, author);
			BfWriteByte(userMessage, false);
			BfWriteString(userMessage, buffer[view_as<int>(canStartWithColor)]);
		}
		
		EndMessage();
	}
	else
	{
		if (engineVersion == Engine_DODS)
		{
			int team = author && IsClientInGame(author) ? GetClientTeam(author) : 0;
			char colors[][] = {"\x04", "\x07CCCCCC", "\x074D7942", "\x07FF4040"};
			
			ReplaceString(buffer, sizeof(buffer), "\x03", colors[team], true);
		}
		
		PrintToChat(client, buffer[view_as<int>(canStartWithColor)]);
	}
}

/**
 * Private function.
 */
stock void SourceColors_PrintToConsole(int client, const char[] format, any ...)
{
	char buffer[SOURCECOLORS_MAX_MESSAGE_LENGTH];
	VFormat(buffer, sizeof(buffer), format, 3);
	
	CRemoveTags(buffer, sizeof(buffer));
	PrintToConsole(client, buffer);
}

/**
 * Private function.
 */
stock bool SourceColors_GetChatTextParams(int paramId, int& author)
{
	if (paramId != SOURCECOLORS_CHAT_PARAM_MESSAGE_ID)
	{
		return false;
	}
	
	if (SOURCECOLORS_CHAT_PARAM_AUTHOR_ID && SOURCECOLORS_CHAT_PARAM_AUTHOR_ID != SOURCECOLORS_AUTHOR_RECEIVER)
	{
		author = GetClientOfUserId(SOURCECOLORS_CHAT_PARAM_AUTHOR_ID);
		if (!author)
		{
			author = SOURCECOLORS_AUTHOR_RECEIVER;
		}
	}
	else
	{
		author = SOURCECOLORS_CHAT_PARAM_AUTHOR_ID;
	}
	
	return true;
}

/**
 * Private function.
 */
stock int SourceColors_GetColorFromHex(const char[] color, char[] buffer, int maxlength)
{
	if (color[0] != '#')
	{
		return 0;
	}
	
	int len = strlen(color);
	if (len != 7 && len != 9)
	{
		return 0;
	}
	
	for (int i = 1; i < len; i++)
	{
		if (IsCharAlpha(color[i]))
		{
			if ((color[i] < 'A' || color[i] > 'F') && (color[i] < 'a' || color[i] > 'f'))
			{
				return 0;
			}
		}
		else if (!IsCharNumeric(color[i]))
		{
			return 0;
		}
	}
	
	if (len == 7)
	{
		return FormatEx(buffer, maxlength, "\x07%s", color[1]);
	}
	else if (len == 9)
	{
		return FormatEx(buffer, maxlength, "\x08%s", color[1]);
	}
	
	return 0;
}

/**
 * Private function.
 */
stock int SourceColors_GetColorFromRGB(const char[] color, char[] buffer, int maxlength)
{
	if (strncmp(color, "rgb", 3, true) 
		|| color[3] != '(' && strncmp(color[3], "a(", 2, true))
	{
		return 0;
	}
	
	int len = strlen(color);
	if (color[len - 1] != ')')
	{
		return 0;
	}
	
	color[len - 1] = 0;
	
	int numBuffers = (color[3] == 'a') ? 4 : 3;
	char buffers[4][SOURCECOLORS_MAX_MESSAGE_LENGTH];
	
	if (ExplodeString(color[numBuffers + 1], ",", buffers, numBuffers, sizeof(buffers[])) != numBuffers)
	{
		return 0;
	}
	
	int rgb[3];
	
	TrimString(buffers[0]);
	TrimString(buffers[1]);
	TrimString(buffers[2]);
	
	if (!StringToIntEx(buffers[0], rgb[0]) || rgb[0] < 0 || rgb[0] > 255 
		|| !StringToIntEx(buffers[1], rgb[1]) || rgb[1] < 0 || rgb[1] > 255 
		|| !StringToIntEx(buffers[2], rgb[2]) || rgb[2] < 0 || rgb[2] > 255)
	{
		return 0;
	}
	
	if (numBuffers == 4)
	{
		float alpha;
		TrimString(buffers[3]);
		
		if (!StringToFloatEx(buffers[3], alpha) || alpha < 0.0 || alpha > 1.0)
		{
			return 0;
		}
		
		if (alpha != 1.0)
		{
			return FormatEx(buffer, maxlength, "\x08%02X%02X%02X%02X", rgb[0], rgb[1], rgb[2], RoundToCeil(alpha * 255.0));
		}
	}
	
	return FormatEx(buffer, maxlength, "\x07%02X%02X%02X", rgb[0], rgb[1], rgb[2]);
}