/*
 * IFileSystem.cpp
 *	Implementation of static methods of IFileSystem which have platform dependies
 *  Created on: Aug 7, 2012
 *      Author: gregorytkach
 */

#include "io/IFileSystem.h"

namespace irrgame
{
	namespace io
	{
		//! Converts a relative path to an absolute (unique) path, resolving symbolic links if required
		//! Platform dependies
		/** \param filename Possibly relative file or directory name to query.
		 \result Absolute filename which points to the same file. */
		path IFileSystem::getAbsolutePath(const path& filename)
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
					return IFileSystem::flattenFilename(tmp);
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

