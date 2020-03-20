#if defined _newcolors_included
    #endinput
#endif
#define _newcolors_included

#include <regex>

#define MAX_MESSAGE_LENGTH 256

enum struct ColorInfo
{
	char colorTag[64];
	char colorHex[64];
}

#include <newcolors/morecolors>
#include <newcolors/colors>

stock void CPrintToChat(int client, const char[] message, any ...)
{
	if (client < 1 || client > MaxClients)
	{
		ThrowError("Invalid client index %d", client);
	}
	
	if (!IsClientInGame(client))
	{
		ThrowError("Client %i is not in game", client);
	}
	
	SetGlobalTransTarget(client);
	
	char buffer[MAX_MESSAGE_LENGTH];
	int buffer_index = CPreFormat(buffer, sizeof(buffer));
	
	VFormat(buffer[buffer_index], sizeof(buffer) - buffer_index, message, 3);
	
	if (IsSource2009())
	{
		MC_Format(buffer[buffer_index], sizeof(buffer) - buffer_index);
		MC_SendMessage(client, buffer);
	}
	else
	{
		C_Format(buffer[buffer_index], sizeof(buffer) - buffer_index);
		PrintToChat(client, buffer);
	}
}

stock void CPrintToChatEx(int client, int author, const char[] message, any ...)
{
	if (client < 1 || client > MaxClients)
	{
		ThrowError("Invalid client index %d", client);
	}
	
	if (author < 1 || author > MaxClients)
	{
		ThrowError("Invalid author index %d", author);
	}
	
	if (!IsClientInGame(client))
	{
		ThrowError("Client %i is not in game", client);
	}
	
	if (!IsClientInGame(author))
	{
		ThrowError("Author %i is not in game", author);
	}
	
	SetGlobalTransTarget(client);
	
	char buffer[MAX_MESSAGE_LENGTH];
	int buffer_index = CPreFormat(buffer, sizeof(buffer));
	
	VFormat(buffer[buffer_index], sizeof(buffer) - buffer_index, message, 3);
	
	if (IsSource2009())
	{
		MC_Format(buffer[buffer_index], sizeof(buffer) - buffer_index);
		MC_SendMessage(client, buffer, author);
	}
	else
	{
		C_Format(buffer[buffer_index], sizeof(buffer) - buffer_index);
		C_SendMessage(client, buffer, author);
	}
}

stock void CPrintToChatAll(const char[] message, any ...)
{
	bool multiColors = IsSource2009();
	char buffer[MAX_MESSAGE_LENGTH];
	
	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && !IsFakeClient(i))
		{
			SetGlobalTransTarget(i);
			int buffer_index = CPreFormat(buffer, sizeof(buffer));

			VFormat(buffer[buffer_index], sizeof(buffer) - buffer_index, message, 2);
			if (multiColors)
			{
				MC_Format(buffer[buffer_index], sizeof(buffer) - buffer_index);
				MC_SendMessage(i, buffer);
			}
			else
			{
				C_Format(buffer[buffer_index], sizeof(buffer) - buffer_index);
				C_SendMessage(i, buffer);
			}
		}
	}
}

stock int CPreFormat(char[] message, int maxlen)
{
	if (GetEngineVersion() == Engine_CSGO)
	{
		return Format(message, maxlen, " ");
	}

	return Format(message, maxlen, "\x01");
}

stock bool IsSource2009()
{
	if (GetEngineVersion() == Engine_CSS || GetEngineVersion() == Engine_HL2DM || GetEngineVersion() == Engine_DODS || GetEngineVersion() == Engine_TF2)
	{
		return true;
	}
	
	return false;
}