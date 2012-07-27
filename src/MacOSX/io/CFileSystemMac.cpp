/*
 * CFileSystemMac.cpp
 *
 *  Created on: Jul 26, 2012
 *      Author: gregorytkach
 */
#include "CFileSystemMac.h"
namespace irrgame
{
	namespace io
	{
		//! Default constructor
		CFileSystemMac::CFileSystemMac()
		{

		}

		//! Destructor
		CFileSystemMac::~CFileSystemMac()
		{

		}

		//TODO: create unit test
		//! Converts a relative path to an absolute (unique) path, resolving symbolic links
		io::path CFileSystemMac::getAbsolutePath(const io::path& filename) const
		{
			c8* p = 0;
			c8 fpath[4096];
			fpath[0] = 0;
			p = realpath(filename.c_str(), fpath);

			if (!p)
			{
				// content in fpath is unclear at this point
				if (!fpath[0]) // seems like fpath wasn't altered, use our best guess
				{
					io::path tmp(filename);
					return flattenFilename(tmp);
				}
				else
					return io::path(fpath);
			}

			if (filename[filename.size() - 1] == '/')
				return io::path(p) + "/";
			else
				return io::path(p);
		}
	}
}

