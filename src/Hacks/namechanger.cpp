#include "namechanger.h"

int NameChanger::changes = -1;
NC_Type NameChanger::type = NC_NORMAL;

void NameChanger::BeginFrame(float frameTime)
{
	if (!engine->IsInGame())
		return;

	if (changes == -1)
		return;

	long currentTime_ms = Util::GetEpochTime();
	static long timeStamp = currentTime_ms;

	if (currentTime_ms - timeStamp < 150)
		return;

	timeStamp = currentTime_ms;
	changes++;

	if (changes >= 5)
	{
		/*
			\x01 WHITE
			\x02 RED
			\x03 PURPLE
			\x04 GREEN
			\x05 LIGHT GREEN
			\x06 TURQUOISE
			\x07 LIGHT RED
			\x08 GRAY
			\x09 YELLOW
			\x0A GRAY
			\x0B LIGHT BLUE
			\x0C GRAY (PURPLE FOR SPEC)
			\x0D BLUE
			\x0E PINK
			\x0F DARK ORANGE
			\x10 ORANGE
		*/

		switch (NameChanger::type)
		{
			case NC_NORMAL:
				SetName(Util::PadStringRight("\230AIMTUX.NET", strlen("\230AIMTUX.NET") + RandomInt(10, 50)));
				break;
			case NC_RAINBOW:
				SetName(Util::PadStringRight(" \x01\x0B\x07""A""\x08""I""\x09""M""\x0A""T""\x0B""U""\x0C""X""\x0D"".""\x0E""N""\x0F""E""\x10""T", strlen(" \x01\x0B\x07""A""\x08""I""\x09""M""\x0A""T""\x0B""U""\x0C""X""\x0D"".""\x0E""N""\x0F""E""\x10""T") + RandomInt(10, 50)));
				break;
			case NC_SOLID:
				SetName(Util::PadStringRight(" \x01\x0B\x07""AIMTUX.NET", strlen(" \x01\x0B\x07""AIMTUX.NET") + RandomInt(1, 5)));
				break;
		}
		changes = -1;

		return;
	}

	SetName(Util::PadStringRight("AIMTUX.NET", strlen("AIMTUX.NET") + changes));
}

void NameChanger::SetName(const char* name)
{
	ConVar* cvar_name = cvar->FindVar("name");
	*(int*)((uintptr_t)&cvar_name->fnChangeCallback + 0x15) = 0;
	cvar_name->SetValue(name);
}
