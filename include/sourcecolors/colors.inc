#if defined _colors_included
 #endinput
#endif
#define _colors_included

stock void C_SendMessage(int client, const char[] message, int author = -1, bool chatMessage = false)
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
		PrintToChat(client, "%s", message);
	}
}

stock int C_Format(char[] message, int maxlen)
{
	int index = 0;
	char color[MAX_MESSAGE_LENGTH];
	char buffer[MAX_MESSAGE_LENGTH];
	
	for (int i = 0; message[i] && i < maxlen; i++)
	{
		if (message[i] == '{' && message[i + 1] == '$')
		{
			int pos = FindCharInString(message[i + 2], '}');
			if (pos != -1)
			{
				strcopy(color, pos + 1, message[i + 2]);
				int newIndex = C_GetColor(buffer[index], sizeof(buffer) - index, color);
				
				if (newIndex)
				{
					index += newIndex;
					i += pos + 2;
					continue;
				}
			}
		}
		
		buffer[index] = message[i];
		index++;
	}

	return Format(message, maxlen, buffer);
}

stock int C_RemoveTags(char[] message, int maxlen)
{
	int index = 0;
	char color[MAX_MESSAGE_LENGTH];
	char buffer[MAX_MESSAGE_LENGTH];

	for (int i = 0; message[i] && i < maxlen; i++)
	{
		if (message[i] == '{' && message[i + 1] == '$')
		{
			int pos = FindCharInString(message[i + 2], '}');
			if (pos != -1)
			{
				strcopy(color, pos + 1, message[i + 2]);
				if (C_IsValidColor(color))
				{
					i += (pos + 2);
					continue;
				}
			}
		}
		
		buffer[index] = message[i];
		index++;
	}

	return Format(message, maxlen, buffer);
}

stock int C_RemoveColors(char[] message, int maxlen)
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

stock int C_GetColor(char[] colorHex, int colorHexLen, const char[] colorTag)
{
	if (colorTag[0] == 'b')
	{
		if (StrEqual(colorTag, "blue", false))
		{
			return Format(colorHex, colorHexLen, "\x0B");
		}
		else if (StrEqual(colorTag, "bluegrey", false))
		{
			return Format(colorHex, colorHexLen, "\x0A");
		}
	}
	else if (colorTag[0] == 'd')
	{
		if (StrEqual(colorTag, "darkblue", false))
		{
			return Format(colorHex, colorHexLen, "\x0C");
		}
		else if (StrEqual(colorTag, "darkred", false))
		{
			return Format(colorHex, colorHexLen, "\x02");
		}
		else if (StrEqual(colorTag, "default", false))
		{
			return Format(colorHex, colorHexLen, "\x01");
		}
	}
	else if (colorTag[0] == 'g')
	{
		if (StrEqual(colorTag, "green", false))
		{
			return Format(colorHex, colorHexLen, "\x04");
		}
		else if (StrEqual(colorTag, "grey", false))
		{
			return Format(colorHex, colorHexLen, "\x08");
		}
		else if (StrEqual(colorTag, "grey2", false))
		{
			return Format(colorHex, colorHexLen, "\x0D");
		}
	}
	else if (colorTag[0] == 'l')
	{
		if (StrEqual(colorTag, "lightgreen", false))
		{
			return Format(colorHex, colorHexLen, "\x05");
		}
		else if (StrEqual(colorTag, "lightred", false))
		{
			return Format(colorHex, colorHexLen, "\x0F");
		}
		else if (StrEqual(colorTag, "lime", false))
		{
			return Format(colorHex, colorHexLen, "\x06");
		}
	}
	else if (colorTag[0] == 'o')
	{
		if (StrEqual(colorTag, "orange", false))
		{
			return Format(colorHex, colorHexLen, "\x10");
		}
		else if (StrEqual(colorTag, "orchid", false))
		{
			return Format(colorHex, colorHexLen, "\x0E");
		}
	}
	else if (colorTag[0] == 'r')
	{
		if (StrEqual(colorTag, "red", false))
		{
			return Format(colorHex, colorHexLen, "\x07");
		}
	}
	else if (colorTag[0] == 't')
	{
		if (StrEqual(colorTag, "team", false))
		{
			return Format(colorHex, colorHexLen, "\x03");
		}
	}
	else if (colorTag[0] == 'y')
	{
		if (StrEqual(colorTag, "yellow", false))
		{
			return Format(colorHex, colorHexLen, "\x09");
		}
	}
	
	return 0;
}

stock bool C_IsValidColor(const char[] colorTag)
{
	if (colorTag[0] == 'b')
	{
		if (StrEqual(colorTag, "blue", false)
			|| StrEqual(colorTag, "bluegrey", false))
		{
			return true;
		}
	}
	else if (colorTag[0] == 'd')
	{
		if (StrEqual(colorTag, "darkblue", false)
			|| StrEqual(colorTag, "darkred", false)
			|| StrEqual(colorTag, "default", false))
		{
			return true;
		}
	}
	else if (colorTag[0] == 'g')
	{
		if (StrEqual(colorTag, "green", false)
			|| StrEqual(colorTag, "grey", false)
			|| StrEqual(colorTag, "grey2", false))
		{
			return true;
		}
	}
	else if (colorTag[0] == 'l')
	{
		if (StrEqual(colorTag, "lightgreen", false)
			|| StrEqual(colorTag, "lightred", false)
			|| StrEqual(colorTag, "lime", false))
		{
			return true;
		}
	}
	else if (colorTag[0] == 'o')
	{
		if (StrEqual(colorTag, "orange", false)
			|| StrEqual(colorTag, "orchid", false))
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
	else if (colorTag[0] == 'y')
	{
		if (StrEqual(colorTag, "yellow", false))
		{
			return true;
		}
	}
	
	return false;
}