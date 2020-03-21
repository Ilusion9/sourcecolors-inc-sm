#if defined _colors_included
 #endinput
#endif
#define _colors_included
 
ColorInfo g_Colors[] = {
	{ "default", 		"\x01" },
	{ "team", 		"\x03" },
	{ "darkred", 		"\x02" },
	{ "green", 		"\x04" },
	{ "lightgreen", 	"\x05" },
	{ "lime", 		"\x06" },
	{ "red", 			"\x07" },
	{ "grey",			"\x08" },
	{ "yellow", 		"\x09" },
	{ "orange", 		"\x10" },
	{ "bluegrey", 	"\x0A" },
	{ "blue", 		"\x0B" },
	{ "darkblue", 	"\x0C" },
	{ "grey2", 		"\x0D" },
	{ "orchid", 		"\x0E" },
	{ "lightred", 	"\x0F" }
};

stock void C_SendMessage(int client, const char[] message, int author = 0)
{
	if (!author)
	{
		author = client;
	}
	
	if (GetUserMessageId("SayText2") == INVALID_MESSAGE_ID)
	{
		PrintToChat(client, "%s", message);
		return;
	}
	
	Handle buf = StartMessageOne("SayText2", client, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS);
	if (GetFeatureStatus(FeatureType_Native, "GetUserMessageType") == FeatureStatus_Available && GetUserMessageType() == UM_Protobuf)
	{
		PbSetInt(buf, "ent_idx", author);
		PbSetBool(buf, "chat", false);
		PbSetString(buf, "msg_name", message);
		PbAddString(buf, "params", "");
		PbAddString(buf, "params", "");
		PbAddString(buf, "params", "");
		PbAddString(buf, "params", "");
	}
	else
	{
		BfWriteByte(buf, author); // Message author
		BfWriteByte(buf, true); // Chat message
		BfWriteString(buf, message); // Message text
	}
	
	EndMessage();
}

stock void C_Format(char[] message, int maxlen)
{
	int buffer_index = 0;
	char buffer[MAX_MESSAGE_LENGTH];

	for (int i = 0; i < maxlen && message[i] != '\0'; i++)
	{
		if (message[i] == '{' && message[i + 1] == '$')
		{
			char color[MAX_MESSAGE_LENGTH];
			strcopy(color, sizeof(color), message[i + 2]);
			int pos = FindCharInString(color, '}');
			
			if (pos != -1)
			{
				color[pos] = 0;
				
				int newIndex = C_GetColor(buffer[buffer_index], sizeof(buffer) - buffer_index, color);
				if (newIndex)
				{
					buffer_index += newIndex;
					i += pos + 2;
					continue;
				}
			}
		}
		
		buffer[buffer_index] = message[i];
		buffer_index++;
	}

	strcopy(message, maxlen, buffer);
}

stock int C_GetColor(char[] colorHex, int colorHexLen, const char[] colorTag)
{
	for (int i = 0; i < sizeof(g_Colors); i++)
	{
		if (StrEqual(colorTag, g_Colors[i].colorTag, false))
		{
			return Format(colorHex, colorHexLen, "%s", g_Colors[i].colorHex);
		}
	}
	
	return 0;
}
