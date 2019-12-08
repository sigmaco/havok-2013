/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_FILESYSTEM
#define HK_FILESYSTEM

#include <Common/Base/Container/String/hkStringBuf.h>

class hkStreamReader;
class hkStreamWriter;

	/// Interface for hkStreamReader/hkStreamWriter creation and filesystem browsing.
	/// When streams and archives are given a resource to open by name, they
	/// ask the FileSystem to open it for them. The user may wish to
	/// replace the default factory with one which reads from packed files
	/// or searches in several locations for instance.
	/// \note Most methods which take a filename string as a parameter pass it
	/// to the filesystem singleton to actually open a stream. To handle I/O errors
	/// gracefully you will generally have to implement this interface or bypass it
	/// completely by using methods which accept streams or in memory buffers directly.
class hkFileSystem : public hkReferencedObject, public hkSingleton<hkFileSystem>
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);

		enum AccessMode
		{
			ACCESS_READ = 1,
			ACCESS_WRITE = 2,
		};

		enum Result
		{
			RESULT_OK = 0, ///< Success
			RESULT_ERROR, ///< Unspecified error
			RESULT_NOT_IMPLEMENTED, ///< Method is not implemented
		};

		enum OpenFlags
		{
				/// The file is buffered. This makes peek() available and takes care of any platform-specific
				/// alignment and block size requirements.
			OPEN_BUFFERED = 1,
				/// Truncate the file if it exists. Without this flag, the content (if any) is not
				/// truncated. In either case, the initial file offset will always be zero, so a seek is
				/// required to append data.
			OPEN_TRUNCATE = 2,	
				/// Default read mode
			OPEN_DEFAULT_READ = OPEN_BUFFERED,
				/// Default write mode
			OPEN_DEFAULT_WRITE = OPEN_BUFFERED | OPEN_TRUNCATE,
		};

			/// Platform independent timestamp that can be used to reference points in time.
			/// Stores timestamp in nanoseconds that have passed since
			/// 1970-01-01T00:00:00.000 UTC (Unix time in nanoseconds).
			/// Can represent valid ranges in (1970-01-01T00:00:00.000 UTC, 2554-07-21T23:34:33 UTC].
		struct TimeStamp
		{
			public:

				enum { TIMESTAMP_UNAVAILABLE=0 };

				TimeStamp() : m_time(TIMESTAMP_UNAVAILABLE) {}
				TimeStamp(hkUint64 nsSinceEpoch) : m_time(nsSinceEpoch) {}

				HK_FORCE_INLINE hkBool32 operator==(const TimeStamp& rhs) const {return m_time == rhs.m_time;}
				HK_FORCE_INLINE hkBool32 operator<(const TimeStamp& rhs) const {return m_time < rhs.m_time;}
				HK_FORCE_INLINE hkBool32 operator>(const TimeStamp& rhs) const {return m_time > rhs.m_time;}

					/// Sets the timestamp to the given Unix time in nanoseconds.
				void set(hkUint64 nsSinceEpoch);

					/// Returns the nanoseconds passed since Unix epoch.
				hkUint64 get() const;

					/// Returns whether the stored time is valid.
					/// Invalid values are returned by file systems that do not support timestamps.
				hkBool isValid() const;
		
			private:

				hkUint64 m_time;
		};

			/// Represents a file or directory in a filesystem.
		struct Entry
		{
			public:

				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkFileSystem::Entry);

				Entry() : m_fs(0), m_mtime(), m_size(-1), m_flags(0) {}

				enum FlagValues
				{
					F_ISFILE = 1, ///< Regular file
					F_ISDIR = 2, ///< Folder type
					F_ISUNKNOWN = 4, ///< Unrecognised type (e.g. link, device)
				};

					///
				typedef hkFlags<FlagValues, hkUint32> Flags;

				hkBool32 isDir() const { return m_flags.get(F_ISDIR); }
				hkBool32 isFile() const { return m_flags.get(F_ISFILE); }
				const char* getPath() const { return m_path; }
				const char* getName() const;
				TimeStamp getMtime() const { return m_mtime; }
				hkInt64 getSize() const { return m_size; }

				void setPath( hkFileSystem* fs, const char* path );
				void setMtime(TimeStamp mt) { m_mtime = mt; }
				void setSize(hkInt64 s) { m_size = s; }
				void setFlags(Flags f) { m_flags = f; }
				void setAll( hkFileSystem* fs, const char* fullPath, Flags flags, TimeStamp mt, hkInt64 sz );
				
				hkRefNew<hkStreamReader> openReader(OpenFlags flags=OPEN_DEFAULT_READ) const;
				hkRefNew<hkStreamWriter> openWriter(OpenFlags flags=OPEN_DEFAULT_WRITE) const;

			private:

				hkFileSystem* m_fs;	///< The filesystem this entry belongs to.
				hkStringPtr m_path; ///< Path to the entry including the name.
				TimeStamp m_mtime;	///< Last modified time.
				hkInt64 m_size;		///< Number of bytes in this entry or -1 if unknown.
				Flags m_flags;		///< Flags (isdir, isfile etc)
		};

			/// Returns a stream reader for file 'name' or null if unable.
		virtual hkRefNew<hkStreamReader> openReader(const char* name, OpenFlags flags=OPEN_DEFAULT_READ) = 0;

			/// Returns a stream reader for file 'name' or null if unable.
		virtual hkRefNew<hkStreamWriter> openWriter(const char* name, OpenFlags flags=OPEN_DEFAULT_WRITE) = 0;

			/// Remove the given path.
		virtual Result remove(const char* path) { return RESULT_NOT_IMPLEMENTED; }

			/// Create a folder with the given name.
		virtual Result mkdir(const char* path) { return RESULT_NOT_IMPLEMENTED; }

			/// Look up a single named path, returns true if an entry exists.
		virtual Result stat( const char* path, Entry& entryOut ) = 0;

			/// Interface to iterate over the entries in a filesystem tree.
		class Iterator
		{
			public:

				HK_DECLARE_PLACEMENT_ALLOCATOR();

					/// Construct an iterator at the given folder name.
				Iterator(hkFileSystem* fs, const char* folder, const char* wildcard=HK_NULL);

					/// Attempt to advance to the next entry.
					/// Return true if there is an entry or return false if there are no more entries.
				bool advance();

					/// Access the current entry. This is only valid after a call to advance() returns true.
				const Entry& current() const { return m_entry; }

					/// Recurse into the given path when the current iterator is exhausted.
				void recurseInto(const char* path)
				{
					m_todo.pushBack(path);
				}

					/// Return true if the name matches the wildcard and is not "." nor "..".
					/// A null wildcard is considered to match everything.
				static bool nameAcceptable(const char* name, const char* wildcard);

					// Internal interface for filesystem
				struct Impl : public hkReferencedObject
				{
					HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_STREAM);
					virtual bool advance(Entry& e) = 0;
				};

			private:

				hkRefPtr<hkFileSystem> m_fs;
				const char* m_wildcard;
				hkRefPtr<Impl> m_impl;
				Entry m_entry;
				hkArray<hkStringPtr> m_todo;
		};

			// Internal function used by Iterator. Use the Iterator class instead.
		virtual hkRefNew<Iterator::Impl> createIterator( const char* top, const char* wildcard ) = 0;

	public:

		struct DirectoryListing
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkFileSystem::DirectoryListing);

			DirectoryListing(hkMemoryAllocator* alloc, const char* top=HK_NULL)
				: m_fs(HK_NULL), m_top(top)
			{
				m_entries.reserve(32);
			}

			void clear()
			{
				m_entries.clear();
			}

			void addEntry(const Entry& ent) 
			{
				HK_ASSERT(0x76231193, m_fs);
				m_entries.pushBack(ent);
			}

			void addDirectory(const char* name) 
			{
				HK_ASSERT(0x5d400f6f, m_fs);
				m_entries.expandOne().setAll( m_fs, hkStringBuf(m_top.cString()).pathAppend(name), Entry::F_ISDIR, TimeStamp(), 0);
			}

				/// adds a copy of name to the file names list.
				/// Also stores the last modified time stamp (default 0).
			void addFile(const char* name, TimeStamp timeModified, hkInt64 size=-1) 
			{
				HK_ASSERT(0x7a9590f9, m_fs);
				m_entries.expandOne().setAll(m_fs, hkStringBuf(m_top.cString()).pathAppend(name), Entry::F_ISFILE, timeModified, size);
			}

			const hkArrayBase<Entry>& getEntries() const
			{
				return m_entries;
			}

			void setFs( hkFileSystem* fs ) { m_fs = fs; }

			hkBool isEmpty() const { return m_entries.isEmpty(); }

		private:

			hkArray<Entry> m_entries;
			hkFileSystem* m_fs;
			hkStringPtr m_top;
		}; // DirectoryListing
		
			/// Deprecated: use Iterator instead.
			/// List all the directories and files in the "path" directory, returns HK_FAILURE if the path is not valid.
		hkResult listDirectory(const char* basePath, DirectoryListing& listingOut);

	protected:

		hkStreamReader* _handleFlags(hkStreamReader* sr, OpenFlags flags);
		hkStreamWriter* _handleFlags(hkStreamWriter* sw, OpenFlags flags);
};


#endif //HK_FILESYSTEM

/*
 * Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20130718)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2013
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available at www.havok.com/tryhavok.
 * 
 */
