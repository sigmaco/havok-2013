/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_SCENE_EXPORT_ERROR_H
#define HK_SCENE_EXPORT_ERROR_H

#include <Common/Base/hkBase.h>
#include <Common/Base/Container/PointerMap/hkPointerMap.h>
#include <Common/Base/Container/String/Deprecated/hkStringOld.h>

	/// An error handler which stores all messages in a log, and allows merging
	/// of the contents of two handlers logs. Extended by the filter manager and
	/// by the individual scene exporters.
class hctSceneExportError : public hkError
{
public:

	hctSceneExportError() : m_indent(0), m_ignoreAll(false) {}
	virtual ~hctSceneExportError() {}
	
		// hkError interface implementation
	
	virtual int message(Message type, int id, const char* description, const char* file, int line);
	
	virtual void	setEnabled( int id, hkBool enabled );
	virtual hkBool	isEnabled( int id );
	virtual void	enableAll();
	
	virtual void sectionBegin(int id, const char* sectionName);
	virtual void sectionEnd();
	
		/// Merge the 'log' of another handler with this one
	void merge( const hctSceneExportError* otherHandler );

	void clearLog();
	virtual void setLogFile( const char* logFileName ) {}
	virtual void setLogVerboseLevel( unsigned int logVerboseLevel ) {}
	virtual void setStdOutput( bool output ) {}

		/// Structure which represents an entry in the log
	struct LogEntry
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_EXPORT, LogEntry );
		Message		m_type;
		int			m_id;
		hkStringOld	m_text;
		bool		m_customColor;
		COLORREF	m_color;
		
		LogEntry(Message type, int id, const char* desc, const char* file, int line);
	};
	
	int numLogEntries() const;
	const LogEntry& getLogEntry(int i) const;

	/// Merge the specified log entry into this one.
	void mergeLogEntry(const LogEntry& logEntry);

protected:

	hkPointerMap<int, int>	m_disabledAssertIds;
	hkArray<LogEntry>	m_log;
	int						m_indent;
	bool					m_ignoreAll;
};

#endif //HK_SCENE_EXPORT_ERROR_H

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
