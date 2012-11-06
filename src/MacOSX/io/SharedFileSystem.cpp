/*
 * SharedFileSystem.cpp
 *	Implementation of static methods of SharedFileSystem which have platform dependies
 *  Created on: Aug 7, 2012
 *      Author: gregorytkach
 */
#include "playerCompileConfig.h"

#ifdef COMPILECONFIGMACOSX_H_

#include "io/SharedFileSystem.h"
#include "io/IFileList.h"
#include "io/utils/ioutils.h"

#include <dirent.h>
#include <sys/stat.h>

namespace irrgame
{
	namespace io
	{
		//! Converts a relative path to an absolute (unique) path, resolving symbolic links if required
		//! Platform dependent
		/** \param filename Possibly relative file or directory name to query.
		 \result Absolute filename which points to the same file. */
		core::stringc SharedFileSystem::getAbsolutePath(
				const core::stringc& filename)
		{
			IRR_ASSERT(filename.size() > 0);

			c8* p = 0;
			c8 fpath[4096];
			fpath[0] = 0;
			p = realpath(filename.cStr(), fpath);

			if (!p)
			{
				// content in fpath is unclear at this point
				if (!fpath[0]) // seems like fpath wasn't altered, use our best guess
				{
					core::stringc tmp(filename);
					return flattenFilename(tmp);
				}
				else
				{
					return core::stringc(fpath);
				}
			}

			if (filename[filename.size() - 1] == '/')
				return core::stringc(p) + "/";
			else
				return core::stringc(p);
		}

		//! Returns the string of the current working directory
		//! Platform dependent
		const core::stringc& SharedFileSystem::getWorkingDirectory()
		{
			EFileSystemType type = FileSystemType;

			if (type != FILESYSTEM_NATIVE)
			{
				type = FILESYSTEM_VIRTUAL;
			}
			else
			{
				u32 pathSize = 256;
				char *tmpPath = new char[pathSize];
				while ((pathSize < (1 << 16)) && !(getcwd(tmpPath, pathSize)))
				{
					delete[] tmpPath;
					pathSize *= 2;
					tmpPath = new char[pathSize];
				}
				if (tmpPath)
				{
					WorkingDirectory[FILESYSTEM_NATIVE] = tmpPath;
					delete[] tmpPath;
				}
//				WorkingDirectory[type].validate();
			}

			return WorkingDirectory[type];
		}

		//! Changes the current Working Directory to the given string.
		bool SharedFileSystem::changeWorkingDirectoryTo(
				const core::stringc& value)
		{
			bool success = false;

			if (FileSystemType != FILESYSTEM_NATIVE)
			{
				WorkingDirectory[FILESYSTEM_VIRTUAL] = value;
				flattenFilename(WorkingDirectory[FILESYSTEM_VIRTUAL], "");
				success = 1;
			}
			else
			{
				success = (chdir(value.cStr()) == 0);

				if (success)
					WorkingDirectory[FILESYSTEM_NATIVE] = value;
			}

			return success;
		}

		//! determines if a file exists and would be able to be opened.
		bool SharedFileSystem::existFile(const core::stringc& filename)
		{
			return (access(filename.cStr(), 0) != -1);
		}

		//! Creates a list of files and directories in the current working directory
		IFileList* SharedFileSystem::createFileList()
		{
			IFileList* result = 0;
			core::stringc Path = getWorkingDirectory();
			Path.replace('\\', '/');
			if (Path.lastChar() != '/')
				Path.append('/');

			//! Construct from native filesystem
			if (FileSystemType == FILESYSTEM_NATIVE)
			{
				core::stringc fullPath;

				result = irrgame::io::createFileList(Path, false, false);

				result->addItem(Path + "..", 0, true, 0);

				//! We use the POSIX compliant methods instead of scandir
				DIR* dirHandle = opendir(Path.cStr());
				if (dirHandle)
				{
					struct dirent *dirEntry;
					while ((dirEntry = readdir(dirHandle)))
					{
						u32 size = 0;
						bool isDirectory = false;
						fullPath = Path + dirEntry->d_name;

						if ((strcmp(dirEntry->d_name, ".") == 0)
								|| (strcmp(dirEntry->d_name, "..") == 0))
						{
							continue;
						}
						struct stat buf;
						if (stat(dirEntry->d_name, &buf) == 0)
						{
							size = buf.st_size;
							isDirectory = S_ISDIR(buf.st_mode);
						}

						result->addItem(fullPath, size, isDirectory, 0);
					}
					closedir(dirHandle);
				}
			}
			else
			{
				//! create file list for the virtual filesystem
				result = irrgame::io::createFileList(Path, false, false);

				//! add relative navigation
				SFileListEntry e2;
				SFileListEntry e3;

				//! PWD
				result->addItem(Path + ".", 0, true, 0);

				//! parent
				result->addItem(Path + "..", 0, true, 0);

				//! merge archives
				for (u32 i = 0; i < FileArchives.size(); ++i)
				{
					const IFileList *merge = FileArchives[i]->getFileList();

					for (u32 j = 0; j < merge->getFileCount(); ++j)
					{
						if (ioutils::isInSameDirectory(Path,
								merge->getFullFileName(j)) == 0)
						{
							core::stringc fullPath = merge->getFullFileName(j);
							result->addItem(fullPath, merge->getFileSize(j),
									merge->isDirectory(j), 0);
						}
					}
				}
			}

			if (result)
				result->sort();

			return result;
		}

	}		//end namespace io
}		//end namespace irrgame
#endif /* COMPILECONFIGMACOSX_H_ */

