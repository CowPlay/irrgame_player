//// Copyright (C) 2002-2009 Nikolaus Gebhardt
//// This file is part of the "Irrlicht Engine".
//// For conditions of distribution and use, see copyright notice in irrlicht.h
//
//#include "CFileSystemStub.h"
//#include "./io/IReadFile.h"
//#include "./io/IWriteFile.h"
//#include "./io/IXMLReader.h"
//#include "./io/IXMLWriter.h"
////#include "CZipReader.h"
////#include "CMountPointReader.h"
////#include "CPakReader.h"
////#include "CNPKReader.h"
////#include "CTarReader.h"
//#include "./io/IFileList.h"
//#include "stdio.h"
////#include "os.h"
////#include "CAttributes.h"
//
////#if defined (_IRR_WINDOWS_API_)
////#if !defined ( _WIN32_WCE )
////#include <direct.h> // for _chdir
////#include <io.h> // for _access
////#endif
////#else
////#if (defined(_IRR_POSIX_API_) || defined(_IRR_OSX_PLATFORM_) || defined(_IRR_ANDROID_PLATEFORM_))
////#include <stdio.h>
////#include <stdlib.h>
////#include <string.h>
////#include <limits.h>
////#include <sys/types.h>
////#include <dirent.h>
////#include <sys/stat.h>
////#include <unistd.h>
////#endif
////#endif
//
#include "CFileSystem.h"
namespace irrgame
{
	namespace io
	{
		//! Default constructor
//		CFileSystem::CFileSystem()
//		{
//#ifdef DEBUG
//			setDebugName("CFileSystemStub");
//#endif
//
////			setFileListSystem (FILESYSTEM_NATIVE);
//			//! reset current working directory
//			getWorkingDirectory();
//
//#ifdef __IRR_COMPILE_WITH_ZIP_ARCHIVE_LOADER_
//			ArchiveLoader.push_back(new CArchiveLoaderZIP(this));
//#endif
//
//#ifdef __IRR_COMPILE_WITH_MOUNT_ARCHIVE_LOADER_
//			ArchiveLoader.push_back(new CArchiveLoaderMount(this));
//#endif
//
//#ifdef __IRR_COMPILE_WITH_PAK_ARCHIVE_LOADER_
//			ArchiveLoader.push_back(new CArchiveLoaderPAK(this));
//#endif
//
//#ifdef __IRR_COMPILE_WITH_NPK_ARCHIVE_LOADER_
//			ArchiveLoader.push_back(new CArchiveLoaderNPK(this));
//#endif
//
//#ifdef __IRR_COMPILE_WITH_TAR_ARCHIVE_LOADER_
//			ArchiveLoader.push_back(new CArchiveLoaderTAR(this));
//#endif
//		}

		//! Destructor
//		CFileSystem::~CFileSystem()
//		{
////			u32 i;
////
////			for (i = 0; i < FileArchives.size(); ++i)
////			{
////				FileArchives[i]->drop();
////			}
////
////			for (i = 0; i < ArchiveLoader.size(); ++i)
////			{
////				ArchiveLoader[i]->drop();
////			}
//		}

		//! IFileSystem creator. Internal function. Please do not use.
//		IFileSystem* createFileSystem()
//		{
//			return new CFileSystem;
//		}
	}
}

//
//

//

//

//

//

//
//		//! Adds an external archive loader to the engine.
//		void CFileSystemStub::addArchiveLoader(IArchiveLoader* loader)
//		{
//			if (!loader)
//				return;
//
//			loader->grab();
//			ArchiveLoader.push_back(loader);
//		}
//
//		//! move the hirarchy of the filesystem. moves sourceIndex relative up or down
//		bool CFileSystemStub::moveFileArchive(u32 sourceIndex, s32 relative)
//		{
//			bool r = false;
//			const s32 dest = (s32) sourceIndex + relative;
//			const s32 dir = relative < 0 ? -1 : 1;
//			const s32 sourceEnd = ((s32) FileArchives.size()) - 1;
//			IFileArchive *t;
//
//			for (s32 s = (s32) sourceIndex; s != dest; s += dir)
//			{
//				if (s < 0 || s > sourceEnd || s + dir < 0
//						|| s + dir > sourceEnd)
//					continue;
//
//				t = FileArchives[s + dir];
//				FileArchives[s + dir] = FileArchives[s];
//				FileArchives[s] = t;
//				r = true;
//			}
//			return r;
//		}
//
//		//! Adds an archive to the file system.
//		bool CFileSystemStub::addFileArchive(const io::path& filename,
//				bool ignoreCase, bool ignorePaths,
//				E_FILE_ARCHIVE_TYPE archiveType, const core::stringc& password)
//		{
//			IFileArchive* archive = 0;
//			bool ret = false;
//			u32 i;
//
//			// check if the archive was already loaded
//			for (i = 0; i < FileArchives.size(); ++i)
//			{
//				if (getAbsolutePath(filename)
//						== FileArchives[i]->getFileList()->getPath())
//				{
//					if (password.size())
//						FileArchives[i]->Password = password;
//					return true;
//				}
//			}
//
//			// do we know what type it should be?
//			if (archiveType == EFAT_UNKNOWN || archiveType == EFAT_FOLDER)
//			{
//				// try to load archive based on file name
//				for (i = 0; i < ArchiveLoader.size(); ++i)
//				{
//					if (ArchiveLoader[i]->isALoadableFileFormat(filename))
//					{
//						archive = ArchiveLoader[i]->createArchive(filename,
//								ignoreCase, ignorePaths);
//						if (archive)
//							break;
//					}
//				}
//
//				// try to load archive based on content
//				if (!archive)
//				{
//					io::IReadFile* file = createAndOpenFile(filename);
//					if (file)
//					{
//						for (i = 0; i < ArchiveLoader.size(); ++i)
//						{
//							file->seek(0);
//							if (ArchiveLoader[i]->isALoadableFileFormat(file))
//							{
//								file->seek(0);
//								archive = ArchiveLoader[i]->createArchive(file,
//										ignoreCase, ignorePaths);
//								if (archive)
//									break;
//							}
//						}
//						file->drop();
//					}
//				}
//			}
//			else
//			{
//				// try to open archive based on archive loader type
//
//				io::IReadFile* file = 0;
//
//				for (i = 0; i < ArchiveLoader.size(); ++i)
//				{
//					if (ArchiveLoader[i]->isALoadableFileFormat(archiveType))
//					{
//						// attempt to open file
//						if (!file)
//							file = createAndOpenFile(filename);
//
//						// is the file open?
//						if (file)
//						{
//							// attempt to open archive
//							file->seek(0);
//							if (ArchiveLoader[i]->isALoadableFileFormat(file))
//							{
//								file->seek(0);
//								archive = ArchiveLoader[i]->createArchive(file,
//										ignoreCase, ignorePaths);
//								if (archive)
//									break;
//							}
//						}
//						else
//						{
//							// couldn't open file
//							break;
//						}
//					}
//				}
//
//				// if open, close the file
//				if (file)
//					file->drop();
//			}
//
//			if (archive)
//			{
//				FileArchives.push_back(archive);
//				if (password.size())
//					archive->Password = password;
//				ret = true;
//			}
//			else
//			{
//				//TODO uncomment and implement
////				os::Printer::log("Could not create archive for", filename,
////						ELL_ERROR);
//			}
//
//			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
//			return ret;
//		}
//
//		//! removes an archive from the file system.
//		bool CFileSystemStub::removeFileArchive(u32 index)
//		{
//			bool ret = false;
//			if (index < FileArchives.size())
//			{
//				FileArchives[index]->drop();
//				FileArchives.erase(index);
//				ret = true;
//			}_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
//			return ret;
//		}
//
//		//! removes an archive from the file system.
//		bool CFileSystemStub::removeFileArchive(const io::path& filename)
//		{
//			for (u32 i = 0; i < FileArchives.size(); ++i)
//			{
//				if (filename == FileArchives[i]->getFileList()->getPath())
//					return removeFileArchive(i);
//			}_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
//			return false;
//		}
//
//		//! gets an archive
//		u32 CFileSystemStub::getFileArchiveCount() const
//		{
//			return FileArchives.size();
//		}
//
//		IFileArchive* CFileSystemStub::getFileArchive(u32 index)
//		{
//			return index < getFileArchiveCount() ? FileArchives[index] : 0;
//		}
//
//
//
//
//
//
//

//
//		//! returns the base part of a filename, i.e. all except for the directory
//		//! part. If no directory path is prefixed, the full name is returned.
//		io::path CFileSystemStub::getFileBasename(const io::path& filename,
//				bool keepExtension) const
//		{
//			// find last forward or backslash
//			s32 lastSlash = filename.findLast('/');
//			const s32 lastBackSlash = filename.findLast('\\');
//			lastSlash = core::max_(lastSlash, lastBackSlash);
//
//			// get number of chars after last dot
//			s32 end = 0;
//			if (!keepExtension)
//			{
//				// take care to search only after last slash to check only for
//				// dots in the filename
//				end = filename.findLast('.');
//				if (end == -1 || end < lastSlash)
//					end = 0;
//				else
//					end = filename.size() - end;
//			}
//
//			if ((u32) lastSlash < filename.size())
//				return filename.subString(lastSlash + 1,
//						filename.size() - lastSlash - 1 - end);
//			else if (end != 0)
//				return filename.subString(0, filename.size() - end);
//			else
//				return filename;
//		}
//

//
//		//! Creates a list of files and directories in the current working directory
//		EFileSystemType CFileSystemStub::setFileListSystem(
//				EFileSystemType listType)
//		{
//			EFileSystemType current = FileSystemType;
//			FileSystemType = listType;
//			return current;
//		}
//
//
//
//		//! Creates an empty filelist
//		IFileList* CFileSystemStub::createEmptyFileList(const io::path& path,
//				bool ignoreCase, bool ignorePaths)
//		{
//			return irrgame::io::createFileList(path, ignoreCase, ignorePaths);
//		}
//
//
//
//
//
//		//! Creates a XML Reader from a file.
//		IXMLReaderUTF8* CFileSystemStub::createXMLReaderUTF8(
//				const io::path& filename)
//		{
//			IReadFile* file = createAndOpenFile(filename);
//			if (!file)
//				return 0;
//
//			IXMLReaderUTF8* reader = irrgame::io::createXMLReaderUTF8(file);
//			file->drop();
//			return reader;
//		}
//
//		//! Creates a XML Reader from a file.
//		IXMLReaderUTF8* CFileSystemStub::createXMLReaderUTF8(IReadFile* file)
//		{
//			if (!file)
//				return 0;
//
//			return irrgame::io::createXMLReaderUTF8(file);
//		}
//
//
//

//
//	}// end namespace irr
//} // end namespace io
//
