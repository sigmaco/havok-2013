/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#include <Common/Base/hkBase.h>
#include <Common/Base/Container/String/hkUtf8.h>
#include <wchar.h>

#ifndef WCHAR_MAX
	#error wchar.h should provide WCHAR_MAX
#endif

#if !defined(_MANAGED)
	#error This is only for managed
#endif

#pragma managed(push, on)

	// duplicated from hkUtf8::utf8FromWide for inlining
static inline int hkUtf8_utf8FromWide( char buf[4], wchar_t cp )
{
	if (cp <= 0x007f)
	{
		buf[0] = char(cp);
		return 1;
	}
	else if( cp <= 0x07ff )
	{
		buf[0] = char(0xc0 | (cp>>6));
		buf[1] = char(0x80 | (cp & 0x3f));
		return 2;
	}
#if WCHAR_MAX <= 0xffff // two byte wchar_t
	else
	{
		buf[0] = char(0xe0 | (cp>>12));
		buf[1] = char(0x80 | ((cp>>6) & 0x3f));
		buf[2] = char(0x80 | (cp & 0x3f));
		return 3;
	}
#else // four byte wchar_t
	else if( cp <= 0xffff )
	{
		buf[0] = char(0xe0 | (cp>>12));
		buf[1] = char(0x80 | ((cp>>6) & 0x3f));
		buf[2] = char(0x80 | (cp & 0x3f));
		return 3;
	}
	else if( cp <= 0x001fffff )
	{
		buf[0] = char(0xf0 | (cp>>18));
		buf[1] = char(0x80 | ((cp>>12) & 0x3f));
		buf[2] = char(0x80 | ((cp>>6) & 0x3f));
		buf[3] = char(0x80 | (cp & 0x3f));
		return 4;
	}
	else
	{
		HK_ASSERT(0x79ab8123,0);
		return 0;
	}
 #endif
}

hkUtf8::Utf8FromWide::Utf8FromWide(System::String^ s)
{
	if( s != nullptr )
	{
		// calculate required size
		int nbytes = 0;
		{
			char buf[4];
			for each( System::Char c in s )
			{
				nbytes += utf8FromWide(buf, c);
			}
		}
		// fill values
		m_utf8.setSize( nbytes + 1 );
		char* p = m_utf8.begin();
		for each( System::Char c in s )
		{
			p += utf8FromWide(p, c);
		}
		*p = 0;
	}
}


hkUtf8::WideFromUtf8::operator System::String^() const
{
	if( this->cString() == HK_NULL )
	{
		return nullptr;
	}

	return gcnew System::String( this->cString() );
}

#pragma managed(pop)

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
