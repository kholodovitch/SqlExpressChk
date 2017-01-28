#include "stdafx.h"

struct Version
{
	Version(const wchar_t* versionStr)
	{
		major = minor = revision = build = 0;
		swscanf(versionStr, L"%d.%d.%d.%d", &major, &minor, &revision, &build);
	}

	int compare(const Version &otherVersion)
	{
		if(major != otherVersion.major)
			return major < otherVersion.major ? -1 : 1;
		if(minor != otherVersion.minor)
			return minor < otherVersion.minor ? -1 : 1;
		if(revision != otherVersion.revision)
			return revision < otherVersion.revision ? -1 : 1;
		if(build != otherVersion.build)
			return build < otherVersion.build ? -1 : 1;
		return 0;
	}

	bool operator<(const Version &otherVersion)
	{
		return compare(otherVersion) < 0;
	}

	bool operator>(const Version &otherVersion)
	{
		return compare(otherVersion) > 0;
	}

	int major, minor, revision, build;
};