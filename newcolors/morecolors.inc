#if defined _more_colors_included
 #endinput
#endif
#define _more_colors_included

ColorInfo g_MultiColors[] = {
	{ "default", 		"\x01" },
	{ "team", 		"\x03" },
	{ "red", 			"\x07FF4040" },
	{ "blue", 		"\x0799CCFF" },
	{ "green", 		"\x073EFF3E" },
	{ "white", 		"\x07FFFFFF" },
	{ "yellow", 		"\x07FFFF00" },
	{ "purple", 		"\x07800080" },
	{ "orange", 		"\x07FFA500" },
	{ "lime", 		"\x0700FF00" },
	{ "grey", 		"\x07CCCCCC" },
	{ "black", 		"\x07000000" }
};

char g_DodsTeamColors[] = {
	"\x01",
	"\x07CCCCCC",
	"\x074D7942",
	"\x07FF4040"
};

stock void MC_SendMessage(int client, const char[] message, int author = 0)
{
	if (!author)
	{
		author = client;
	}
	
	if (GetUserMessageId("SayText2") == INVALID_MESSAGE_ID)
	{
		char buffer[MAX_MESSAGE_LENGTH];
		strcopy(buffer, sizeof(buffer), message);

		if (GetEngineVersion() == Engine_DODS)
		{
			char color[64];
			int authorTeam = GetClientTeam(author);
			
			Format(color, sizeof(color), "\x07%s", g_DodsTeamColors[authorTeam]);
			ReplaceString(buffer, sizeof(buffer), "\x03", color, false);
		}
		
		PrintToChat(client, "%s", buffer);
		return;
	}
	
	Handle buf = StartMessageOne("SayText2", client, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS);
	if (GetFeatureStatus(FeatureType_Native, "GetUserMessageType") == FeatureStatus_Available && GetUserMessageType() == UM_Protobuf)
	{
		PbSetInt(buf, "ent_idx", author);
		PbSetBool(buf, "chat", true);
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

stock void MC_Format(char[] message, int maxlen)
{
	int buffer_index = 0;
	char buffer[MAX_MESSAGE_LENGTH];

	for (int i = 0; i < maxlen && message[i] != '\0'; i++)
	{
		if (message[i] == '{')
		{
			if (message[i + 1] == '#')
			{
				int j = i + 2;
				char color[6];
				
				for (int icolor = 0; icolor < 6; icolor++)
				{
					color[icolor] = message[j];
					j++;
				}
				
				if (message[j] == '}')
				{
					Regex exp = new Regex("^([A-F0-9])+$");
					int matches = exp.Match(color);
					delete exp;
				
					if (matches > 0)
					{
						buffer_index += Format(buffer[buffer_index], sizeof(buffer) - buffer_index, "\x07%s", color);
						i = j;
						continue;
					}
				}
			}
			else if (message[i + 1] == '$')
			{
				char color[MAX_MESSAGE_LENGTH];
				strcopy(color, sizeof(color), message[i + 2]);
				int pos = FindCharInString(color, '}');
				
				if (pos != -1)
				{
					color[pos] = 0;
					
					int newIndex = MC_GetColor(buffer[buffer_index], sizeof(buffer) - buffer_index, color);
					if (newIndex)
					{
						buffer_index += newIndex;
						i += pos + 2;
						continue;
					}
				}
			}
		}
		
		buffer[buffer_index] = message[i];
		buffer_index++;
	}

	strcopy(message, maxlen, buffer);
}

stock int MC_GetColor(char[] colorHex, int colorHexLen, const char[] colorTag)
{
	for (int i = 0; i < sizeof(g_MultiColors); i++)
	{
		if (StrEqual(colorTag, g_MultiColors[i].colorTag, false))
		{
			return Format(colorHex, colorHexLen, "%s", g_MultiColors[i].colorHex);
		}
	}
	
	return 0;
}