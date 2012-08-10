// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_FILE_SYSTEM_H_INCLUDED__
#define __C_FILE_SYSTEM_H_INCLUDED__

#include "io/IFileSystem.h"

#include "core/irrArray.h"

namespace irrgame
{
	namespace io
	{

//		class CZipReader;
//		class CPakReader;
//		class CMountPointReader;

		/*!
		 FileSystem which uses normal files and one zipfile
		 */
		class CFileSystem: public IFileSystem
		{
			public:

				//! Default constructor
//				CFileSystem();

				//! destructor
//				virtual ~CFileSystem();

//				//! Adds an archive to the file system.
//				virtual bool addFileArchive(const io::path& filename,
//						bool ignoreCase = true, bool ignorePaths = true,
//						E_FILE_ARCHIVE_TYPE archiveType = EFAT_UNKNOWN,
//						const core::stringc& password = "");
//
//				//! move the hirarchy of the filesystem. moves sourceIndex relative up or down
//				virtual bool moveFileArchive(u32 sourceIndex, s32 relative);
//
//				//! Adds an external archive loader to the engine.
//				virtual void addArchiveLoader(IArchiveLoader* loader);
//
//				//! gets the file archive count
//				virtual u32 getFileArchiveCount() const;
//
//				//! gets an archive
//				virtual IFileArchive* getFileArchive(u32 index);
//
//				//! removes an archive from the file system.
//				virtual bool removeFileArchive(u32 index);
//
//				//! removes an archive from the file system.
//				virtual bool removeFileArchive(const io::path& filename);
//
//				//! Returns the string of the current working directory
//				virtual const io::path& getWorkingDirectory();
//
//				//! Changes the current Working Directory to the string given.
//				//! The string is operating system dependent. Under Windows it will look
//				//! like this: "drive:\directory\sudirectory\"
//				virtual bool changeWorkingDirectoryTo(
//						const io::path& newDirectory);
//
//				//! Converts a relative path to an absolute (unique) path, resolving symbolic links
//				virtual io::path getAbsolutePath(
//						const io::path& filename) const;
//
//				//! Returns the directory a file is located in.
//				/** \param filename: The file to get the directory from */
//				virtual io::path getFileDir(const io::path& filename) const;
//
//				//! Returns the base part of a filename, i.e. the name without the directory
//				//! part. If no directory is prefixed, the full name is returned.
//				/** \param filename: The file to get the basename from */
//				virtual io::path getFileBasename(const io::path& filename,
//						bool keepExtension = true) const;
//
//
//				virtual EFileSystemType setFileListSystem(
//						EFileSystemType listType);
//
//				//! Creates a list of files and directories in the current working directory
//				//! and returns it.
//				virtual IFileList* createFileList();
//
//				//! Creates an empty filelist
//				virtual IFileList* createEmptyFileList(const io::path& path,
//						bool ignoreCase, bool ignorePaths);
//
//				//! determines if a file exists and would be able to be opened.
//				virtual bool existFile(const io::path& filename) const;
//
//				//! Creates a XML Reader from a file.
//				virtual IXMLReaderUTF8* createXMLReaderUTF8(
//						const io::path& filename);
//
//				//! Creates a XML Reader from a file.
//				virtual IXMLReaderUTF8* createXMLReaderUTF8(IReadFile* file);
//
//				//! Creates a XML Writer from a file.
//				virtual IXMLWriter* createXMLWriter(const io::path& filename);
//
//				//! Creates a XML Writer from a file.
//				virtual IXMLWriter* createXMLWriter(IWriteFile* file);
//
////				//! Creates a new empty collection of attributes, usable for serialization and more.
////				virtual IAttributes* createEmptyAttributes(
////						video::IVideoDriver* driver);
//
			private:
//


		};

	} // end namespace irr
} // end namespace io

#endif

