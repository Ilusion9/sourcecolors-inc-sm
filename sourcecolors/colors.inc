#if defined _colors_included
 #endinput
#endif
#define _colors_included
 
ColorInfo g_MultiColors[] = {
	{ "default",      "\x01" },
	{ "team",         "\x03" },
	{ "red",          "\x07FF4040" },
	{ "blue",         "\x0799CCFF" },
	{ "green",        "\x073EFF3E" },
	{ "white",        "\x07FFFFFF" },
	{ "yellow",       "\x07FFFF00" },
	{ "purple",       "\x07800080" },
	{ "orange",       "\x07FFA500" },
	{ "lime",         "\x0700FF00" },
	{ "grey",         "\x07CCCCCC" },
	{ "black",        "\x07000000" }
};

stock void C_SendMessage(int client, const char[] message, int author = 0)
{
	bool chatMessage = true;
	if (!author)
	{
		chatMessage = false;
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
		PbSetBool(buf, "chat", chatMessage);
		PbSetString(buf, "msg_name", message);
		PbAddString(buf, "params", "");
		PbAddString(buf, "params", "");
		PbAddString(buf, "params", "");
		PbAddString(buf, "params", "");
	}
	else
	{
		BfWriteByte(buf, author); // Message author
		BfWriteByte(buf, chatMessage); // Chat message
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
