#if defined _more_colors_included
 #endinput
#endif
#define _more_colors_included

stock void MC_SendMessage(int client, const char[] message, int author = -1, bool chatMessage = false)
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

stock int MC_Format(char[] message, int maxlen)
{
	int index = 0;
	char color[MAX_MESSAGE_LENGTH];
	char buffer[MAX_MESSAGE_LENGTH];
	
	for (int i = 0; message[i] && i < maxlen; i++)
	{
		if (message[i] == '{')
		{
			if (message[i + 1] == '#')
			{
				int pos = FindCharInString(message[i + 2], '}');
				if (pos != -1)
				{
					if (pos == 6)
					{
						strcopy(color, pos + 1, message[i + 2]);
						index += Format(buffer[index], sizeof(buffer) - index, "\x07%s", color);
						i += pos + 2;
						continue;
					}
					
					if (pos == 8)
					{
						strcopy(color, pos + 1, message[i + 2]);
						index += Format(buffer[index], sizeof(buffer) - index, "\x08%s", color);
						i += pos + 2;
						continue;
					}
				}
			}
			else if (message[i + 1] == '$')
			{
				int pos = FindCharInString(message[i + 2], '}');
				if (pos != -1)
				{
					strcopy(color, pos + 1, message[i + 2]);
					int newIndex = MC_GetColor(buffer[index], sizeof(buffer) - index, color);
					
					if (newIndex)
					{
						index += newIndex;
						i += pos + 2;
						continue;
					}
				}
			}
		}
		
		buffer[index] = message[i];
		index++;
	}

	return Format(message, maxlen, buffer);
}

stock int MC_RemoveTags(char[] message, int maxlen)
{
	int index = 0;
	char color[MAX_MESSAGE_LENGTH];
	char buffer[MAX_MESSAGE_LENGTH];

	for (int i = 0; message[i] && i < maxlen; i++)
	{
		if (message[i] == '{')
		{
			if (message[i + 1] == '#')
			{
				int pos = FindCharInString(message[i + 2], '}');
				if (pos == 6)
				{
					i += pos + 2;
					continue;
				}
				
				if (pos == 8)
				{
					i += pos + 2;
					continue;
				}
			}
			else if (message[i + 1] == '$')
			{
				int pos = FindCharInString(message[i + 2], '}');
				if (pos != -1)
				{
					strcopy(color, pos + 1, message[i + 2]);
					if (MC_IsValidColor(color))
					{
						i += (pos + 2);
						continue;
					}
				}
			}
		}
		
		buffer[index] = message[i];
		index++;
	}

	return Format(message, maxlen, buffer);
}

stock int MC_RemoveColors(char[] message, int maxlen)
{
	int index = 0;
	char buffer[MAX_MESSAGE_LENGTH];

	for (int i = 0; message[i] && i < maxlen; i++)
	{
		if (message[i] >= 0x01 && message[i] <= 0x10)
		{
			continue;
		}
		
		buffer[index] = message[i];
		index++;
	}

	return Format(message, maxlen, buffer);
}

stock int MC_GetColor(char[] colorHex, int colorHexLen, const char[] colorTag)
{
	if (colorTag[0] == 'b')
	{
		if (StrEqual(colorTag, "black", false))
		{
			return Format(colorHex, colorHexLen, "\x07000000");
		}
		else if (StrEqual(colorTag, "blue", false))
		{
			return Format(colorHex, colorHexLen, "\x0799CCFF");
		}
	}
	else if (colorTag[0] == 'd')
	{
		if (StrEqual(colorTag, "default", false))
		{
			return Format(colorHex, colorHexLen, "\x01");
		}
	}
	else if (colorTag[0] == 'g')
	{
		if (StrEqual(colorTag, "green", false))
		{
			return Format(colorHex, colorHexLen, "\x073EFF3E");
		}
		else if (StrEqual(colorTag, "grey", false))
		{
			return Format(colorHex, colorHexLen, "\x07CCCCCC");
		}
	}
	else if (colorTag[0] == 'l')
	{
		if (StrEqual(colorTag, "lime", false))
		{
			return Format(colorHex, colorHexLen, "\x0700FF00");
		}
	}
	else if (colorTag[0] == 'o')
	{
		if (StrEqual(colorTag, "orange", false))
		{
			return Format(colorHex, colorHexLen, "\x07FFA500");
		}
	}
	else if (colorTag[0] == 'p')
	{
		if (StrEqual(colorTag, "purple", false))
		{
			return Format(colorHex, colorHexLen, "\x07800080");
		}
	}
	else if (colorTag[0] == 'r')
	{
		if (StrEqual(colorTag, "red", false))
		{
			return Format(colorHex, colorHexLen, "\x07FF4040");
		}
	}
	else if (colorTag[0] == 't')
	{
		if (StrEqual(colorTag, "team", false))
		{
			return Format(colorHex, colorHexLen, "\x03");
		}
	}
	else if (colorTag[0] == 'w')
	{
		if (StrEqual(colorTag, "white", false))
		{
			return Format(colorHex, colorHexLen, "\x07FFFFFF");
		}
	}
	else if (colorTag[0] == 'y')
	{
		if (StrEqual(colorTag, "yellow", false))
		{
			return Format(colorHex, colorHexLen, "\x07FFFF00");
		}
	}
	
	return 0;
}

stock bool MC_IsValidColor(const char[] colorTag)
{
	if (colorTag[0] == 'b')
	{
		if (StrEqual(colorTag, "black", false)
			|| StrEqual(colorTag, "blue", false))
		{
			return true;
		}
	}
	else if (colorTag[0] == 'd')
	{
		if (StrEqual(colorTag, "default", false))
		{
			return true;
		}
	}
	else if (colorTag[0] == 'g')
	{
		if (StrEqual(colorTag, "green", false)
			|| StrEqual(colorTag, "grey", false))
		{
			return true;
		}
	}
	else if (colorTag[0] == 'l')
	{
		if (StrEqual(colorTag, "lime", false))
		{
			return true;
		}
	}
	else if (colorTag[0] == 'o')
	{
		if (StrEqual(colorTag, "orange", false))
		{
			return true;
		}
	}
	else if (colorTag[0] == 'p')
	{
		if (StrEqual(colorTag, "purple", false))
		{
			return true;
		}
	}
	else if (colorTag[0] == 'r')
	{
		if (StrEqual(colorTag, "red", false))
		{
			return true;
		}
	}
	else if (colorTag[0] == 't')
	{
		if (StrEqual(colorTag, "team", false))
		{
			return true;
		}
	}
	else if (colorTag[0] == 'w')
	{
		if (StrEqual(colorTag, "white", false))
		{
			return true;
		}
	}
	else if (colorTag[0] == 'y')
	{
		if (StrEqual(colorTag, "yellow", false))
		{
			return true;
		}
	}
	
	return false;
}