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
	char buffer[MAX_MESSAGE_LENGTH];
	
	for (int i = 0; message[i] && i < maxlen; i++)
	{
		if (message[i] == '{' && !strncmp(message[i + 1], "color:", 6, false))
		{
			int pos;
			char color[MAX_MESSAGE_LENGTH];
			
			for (int j = i + 7; message[j] && j < maxlen; j++)
			{
				if (message[j] == '}')
				{
					break;
				}
				
				color[pos++] = message[j];
			}
			
			if (pos && i + pos < maxlen)
			{
				int len = C_GetColor(buffer[index], sizeof(buffer) - index, color);
				if (len)
				{
					index += len;
				}
				
				i += pos + 7;
				continue;
			}
		}
		
		buffer[index] = message[i];
		index++;
	}
	
	return strcopy(message, maxlen, buffer);
}

stock int C_RemoveTags(char[] message, int maxlen)
{
	int index = 0;
	char buffer[MAX_MESSAGE_LENGTH];
	
	for (int i = 0; message[i] && i < maxlen; i++)
	{
		if (message[i] == '{' && !strncmp(message[i + 1], "color:", 6, false))
		{
			int pos;
			char color[MAX_MESSAGE_LENGTH];
			
			for (int j = i + 7; message[j] && j < maxlen; j++)
			{
				if (message[j] == '}')
				{
					break;
				}
				
				color[pos++] = message[j];
			}
			
			if (pos && i + pos < maxlen)
			{
				i += pos + 7;
				continue;
			}
		}
		
		buffer[index] = message[i];
		index++;
	}
	
	return strcopy(message, maxlen, buffer);
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

	return strcopy(message, maxlen, buffer);
}

stock int C_GetColor(char[] colorHex, int colorHexLen, const char[] colorTag)
{
	if (colorTag[0] == 'b')
	{
		if (StrEqual(colorTag, "blue", false))
		{
			return strcopy(colorHex, colorHexLen, "\x0B");
		}
		else if (StrEqual(colorTag, "bluegrey", false))
		{
			return strcopy(colorHex, colorHexLen, "\x0A");
		}
	}
	else if (colorTag[0] == 'd')
	{
		if (StrEqual(colorTag, "darkblue", false))
		{
			return strcopy(colorHex, colorHexLen, "\x0C");
		}
		else if (StrEqual(colorTag, "darkred", false))
		{
			return strcopy(colorHex, colorHexLen, "\x02");
		}
		else if (StrEqual(colorTag, "default", false))
		{
			return strcopy(colorHex, colorHexLen, "\x01");
		}
	}
	else if (colorTag[0] == 'g')
	{
		if (StrEqual(colorTag, "green", false))
		{
			return strcopy(colorHex, colorHexLen, "\x04");
		}
		else if (StrEqual(colorTag, "grey", false))
		{
			return strcopy(colorHex, colorHexLen, "\x08");
		}
		else if (StrEqual(colorTag, "grey2", false))
		{
			return strcopy(colorHex, colorHexLen, "\x0D");
		}
	}
	else if (colorTag[0] == 'l')
	{
		if (StrEqual(colorTag, "lightgreen", false))
		{
			return strcopy(colorHex, colorHexLen, "\x05");
		}
		else if (StrEqual(colorTag, "lightred", false))
		{
			return strcopy(colorHex, colorHexLen, "\x0F");
		}
		else if (StrEqual(colorTag, "lime", false))
		{
			return strcopy(colorHex, colorHexLen, "\x06");
		}
	}
	else if (colorTag[0] == 'o')
	{
		if (StrEqual(colorTag, "orange", false))
		{
			return strcopy(colorHex, colorHexLen, "\x10");
		}
		else if (StrEqual(colorTag, "orchid", false))
		{
			return strcopy(colorHex, colorHexLen, "\x0E");
		}
	}
	else if (colorTag[0] == 'r')
	{
		if (StrEqual(colorTag, "red", false))
		{
			return strcopy(colorHex, colorHexLen, "\x07");
		}
	}
	else if (colorTag[0] == 't')
	{
		if (StrEqual(colorTag, "team", false))
		{
			return strcopy(colorHex, colorHexLen, "\x03");
		}
	}
	else if (colorTag[0] == 'y')
	{
		if (StrEqual(colorTag, "yellow", false))
		{
			return strcopy(colorHex, colorHexLen, "\x09");
		}
	}
	
	return 0;
}