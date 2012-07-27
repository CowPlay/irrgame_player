/*
 * CFileSystemMac.h
 *
 *  Created on: Jul 26, 2012
 *      Author: gregorytkach
 */

#ifndef CFILESYSTEMMAC_H_
#define CFILESYSTEMMAC_H_
#include "./stub/io/CFileSystemStub.h"
namespace irrgame
{
	namespace io
	{
		//! Represents a class which is able to open files from the ordinary file system,
		//! and out of zipfiles, which are able to be added to the filesystem.
		class CFileSystemMac: public CFileSystemStub
		{
			public:
				//! Default constructor
				CFileSystemMac();

				//! Destructor
				~CFileSystemMac();

				//! Converts a relative path to an absolute (unique) path, resolving symbolic links
				io::path getAbsolutePath(const io::path& filename) const;
		};
	}
}

#endif /* CFILESYSTEMMAC_H_ */
