/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE hkDataClass::hkDataClass( hkDataClassImpl* impl )
	: m_impl(impl)
{
}

HK_FORCE_INLINE hkDataClass::~hkDataClass()
{
}

HK_FORCE_INLINE hkBool32 hkDataClass::isNull() const
{
	return m_impl == HK_NULL;
}

HK_FORCE_INLINE const char* hkDataClass::getName() const
{
	return m_impl->getName();
}
HK_FORCE_INLINE int hkDataClass::getVersion() const
{
	return m_impl->getVersion();
}
HK_FORCE_INLINE hkDataClass hkDataClass::getParent() const
{
	return m_impl->getParent();
}

HK_FORCE_INLINE const hkDataWorld* hkDataClass::getWorld() const
{
	return m_impl->getWorld();
}
HK_FORCE_INLINE hkBool hkDataClass::isSuperClass(const hkDataClass& k) const
{
	return m_impl->isSuperClass(k.getImplementation());
}

HK_FORCE_INLINE int hkDataClass::getNumDeclaredMembers() const
{
	return m_impl->getNumDeclaredMembers();
}
HK_FORCE_INLINE int hkDataClass::getDeclaredMemberIndexByName(const char* name) const
{
	return m_impl->getDeclaredMemberIndexByName(name);
}

HK_FORCE_INLINE void hkDataClass::getDeclaredMemberInfo(int i, hkDataClass::MemberInfo& info) const
{
	m_impl->getDeclaredMemberInfo(i,info);
}
HK_FORCE_INLINE void hkDataClass::getMemberInfo(int i, hkDataClass::MemberInfo& info) const
{
	m_impl->getMemberInfo(i,info);
}

HK_FORCE_INLINE int hkDataClass::getNumMembers() const
{
	return m_impl->getNumMembers();
}
HK_FORCE_INLINE int hkDataClass::getMemberIndexByName(const char* name) const
{
	return m_impl->getMemberIndexByName(name);
}

HK_FORCE_INLINE void hkDataClass::getAllMemberInfo(hkArrayBase<hkDataClass::MemberInfo>& members) const
{
	m_impl->getAllMemberInfo(members);
} 

//////////////////////////////////////////////////////////////////////////
// Forwarding Object Methods
//////////////////////////////////////////////////////////////////////////
HK_FORCE_INLINE hkDataObject::hkDataObject()
	: m_impl(HK_NULL)
{
}

HK_FORCE_INLINE hkDataObject::hkDataObject(hkDataObjectImpl* i)
	: m_impl(i)
{
	if( m_impl )
	{
		m_impl->addExternalReference();
	}
}

HK_FORCE_INLINE hkDataObject::hkDataObject(const hkDataObject& o)
	: m_impl(o.m_impl)
{
	if( m_impl )
	{
		m_impl->addExternalReference();
	}
}

HK_FORCE_INLINE void hkDataObject::operator=(const hkDataObject& o)
{
	if( o.m_impl)
	{
		o.m_impl->addExternalReference();
	}
	if( m_impl )
	{
		m_impl->removeExternalReference();
	}
	m_impl = o.m_impl;
}

HK_FORCE_INLINE bool hkDataObject::operator==(const hkDataObject& o)
{
	Handle h = getHandle();
	Handle oh = o.getHandle();
	return h.p0 == oh.p0 && h.p1 == oh.p1;
}

HK_FORCE_INLINE bool hkDataObject::operator!=(const hkDataObject& o)
{
	return !(*this == o);
}

HK_FORCE_INLINE hkDataObject::~hkDataObject()
{
	if( m_impl )
	{
		m_impl->removeExternalReference();
	}
}

HK_FORCE_INLINE hkDataObject::Handle hkDataObject::getHandle() const
{
	hkDataObject::Handle h = {0,0};
	return m_impl ? m_impl->getHandle() : h; //TODO
}


HK_FORCE_INLINE const hkDataClass hkDataObject::getClass() const
{
	return hkDataClass( const_cast<hkDataClassImpl*>(m_impl->getClass()) );
}

HK_FORCE_INLINE hkDataObject::Value hkDataObject::operator[](const char* name)
{
	return m_impl->accessByName(name);
}

HK_FORCE_INLINE const hkDataObject::Value hkDataObject::operator[](const char* name) const
{
	return m_impl->accessByName(name);
}

HK_FORCE_INLINE hkDataObject::Iterator hkDataObject::getMemberIterator() const
{
	return m_impl->getMemberIterator();
}
HK_FORCE_INLINE hkBool32 hkDataObject::isValid(Iterator it) const
{
	return m_impl->isValid(it);
}
HK_FORCE_INLINE hkDataObject::Iterator hkDataObject::getNextMember(Iterator it) const
{
	return m_impl->getNextMember(it);
}
HK_FORCE_INLINE const char* hkDataObject::getMemberName(Iterator it) const
{
	return m_impl->getMemberName(it);
}
HK_FORCE_INLINE const hkDataObject::Value hkDataObject::getMemberValue(Iterator it) const
{
	return m_impl->getMemberValue(it);
}

HK_FORCE_INLINE hkBool32 hkDataObject::hasMember(const char* name) const
{
	return m_impl->hasMember(name);
}

HK_FORCE_INLINE void hkDataObject::destroy()
{
	return m_impl->destroy();
}

HK_FORCE_INLINE hkBool32 hkDataObject::isNull() const
{
	return m_impl == HK_NULL;
}

HK_FORCE_INLINE void hkDataObject::getAllMemberHandles(hkArrayBase<hkDataObject::MemberHandle>& handles) const
{
	return m_impl->getAllMemberHandles(handles);
}

//////////////////////////////////////////////////////////////////////////
// Object Value Methods
//////////////////////////////////////////////////////////////////////////

HK_FORCE_INLINE hkInt64 hkDataObject_Value::asInt64() const
{
	HK_ASSERT(0x5deaf30, m_impl != HK_NULL);
	return m_impl->asInt(m_handle);
}

HK_FORCE_INLINE int hkDataObject_Value::asInt() const
{
	return (int)asInt64();
}

HK_FORCE_INLINE hkDataArray hkDataObject_Value::asArray() const
{
	HK_ASSERT(0x5deaf31, m_impl != HK_NULL);
	return hkDataArray(m_impl->asArray(m_handle));
}

HK_FORCE_INLINE const hkReal* hkDataObject_Value::asVec(int n) const
{
	HK_ASSERT(0x5deaf32, m_impl != HK_NULL);
	return m_impl->asVec(m_handle, n);
}

HK_FORCE_INLINE const char* hkDataObject_Value::asString() const
{
	HK_ASSERT(0x5deaf33, m_impl != HK_NULL);
 	return m_impl->asString(m_handle);
}

HK_FORCE_INLINE hkDataObject hkDataObject_Value::asObject() const
{
	HK_ASSERT(0x5deaf34, m_impl != HK_NULL);
	return hkDataObject( m_impl->asObject(m_handle) );
}

HK_FORCE_INLINE hkReal hkDataObject_Value::asReal() const
{
	HK_ASSERT(0x5deaf35, m_impl != HK_NULL);
	return m_impl->asReal(m_handle);
}

HK_FORCE_INLINE void hkDataObject_Value::operator=(const hkDataObject_Value& v)
{
	m_impl->assign(m_handle, v);
}
HK_FORCE_INLINE void hkDataObject_Value::operator=(int i)
{
	HK_ASSERT(0x5deaf36, m_impl != HK_NULL);
	m_impl->assign(m_handle, i);
}
HK_FORCE_INLINE void hkDataObject_Value::operator=(const hkDataObjectImpl* o)
{
	m_impl->assign(m_handle, const_cast<hkDataObjectImpl*>(o) );
}
HK_FORCE_INLINE void hkDataObject_Value::operator=(const hkDataObject& o)
{
	m_impl->assign(m_handle, const_cast<hkDataObject&>(o).getImplementation() );
}

HK_FORCE_INLINE void hkDataObject_Value::setNull()
{
	m_impl->assign(m_handle, HK_NULL);
}

HK_FORCE_INLINE void hkDataObject_Value::operator=(const class hkDataArray& a)
{
	m_impl->assign(m_handle, const_cast<hkDataArray&>(a).getImplementation() );
}
HK_FORCE_INLINE void hkDataObject_Value::operator=(hkInt64 i)
{
	m_impl->assign(m_handle, i);
}
HK_FORCE_INLINE void hkDataObject_Value::operator=(hkReal r)
{
	m_impl->assign(m_handle, r);
}
HK_FORCE_INLINE void hkDataObject_Value::operator=(hkHalf r)
{
	m_impl->assign(m_handle, r);
}
HK_FORCE_INLINE void hkDataObject_Value::operator=(bool b)
{
	m_impl->assign(m_handle, hkInt64(b));
}
HK_FORCE_INLINE void hkDataObject_Value::setVec(const hkReal* r, int n)
{
	m_impl->assign(m_handle, r, n);
}
HK_FORCE_INLINE void hkDataObject_Value::operator=(const char* s)
{
	m_impl->assign(m_handle, s);
}

HK_FORCE_INLINE hkBool32 hkDataObject_Value::isSet() const
{
	return m_impl && m_impl->isSet(m_handle);
}

HK_FORCE_INLINE void hkDataObject_Value::getMemberInfo(hkDataClass::MemberInfo& infoOut) const 
{
	return m_impl->getMemberInfo(m_handle, infoOut);
}

//////////////////////////////////////////////////////////////////////////
// Array Methods
//////////////////////////////////////////////////////////////////////////

HK_FORCE_INLINE hkDataArray::hkDataArray(hkDataArrayImpl* i)
	: m_impl(i)
{
	if( m_impl )
	{
		m_impl->addExternalReference();
	}
}

HK_FORCE_INLINE hkDataArray::~hkDataArray()
{
	if( m_impl )
	{
		m_impl->removeExternalReference();
	}
}

HK_FORCE_INLINE hkDataWorld* hkDataArray::getWorld() const
{ 
	return m_impl ? m_impl->getWorld() : HK_NULL; 
}

HK_FORCE_INLINE hkDataArray_Value hkDataArray::operator[] (int i)
{
	return Value( m_impl, i );
}

HK_FORCE_INLINE const hkDataArray_Value hkDataArray::operator[](int i) const
{
	return Value( m_impl, i );
}

HK_FORCE_INLINE void hkDataArray::clear()
{
	m_impl->clear();
}

HK_FORCE_INLINE void hkDataArray::setSize(int n)
{
	m_impl->setSize(n);
}

HK_FORCE_INLINE void hkDataArray::reserve(int n)
{
	m_impl->reserve(n);
}

HK_FORCE_INLINE int hkDataArray::getSize() const
{
	return m_impl->getSize();
}

HK_FORCE_INLINE hkDataObject::Type hkDataArray::getType() const
{
	return m_impl->getType();
}

//////////////////////////////////////////////////////////////////////////
// Array Value Methods
//////////////////////////////////////////////////////////////////////////

HK_FORCE_INLINE hkDataObject::Type hkDataArray_Value::getType() const
{
	return m_impl->getType();
}

HK_FORCE_INLINE hkDataClass hkDataArray::getClass() const
{
	return const_cast<hkDataClassImpl*>(m_impl->getClass());
}

HK_FORCE_INLINE const hkReal* hkDataArray_Value::asVec(int nreal) const
{
	return m_impl->asVec(m_index);
}

HK_FORCE_INLINE const char* hkDataArray_Value::asString() const
{
	return m_impl->asString(m_index);
}

HK_FORCE_INLINE hkReal hkDataArray_Value::asReal() const
{
	return m_impl->asReal(m_index);
}

HK_FORCE_INLINE int hkDataArray_Value::asInt() const
{
	return (int)m_impl->asInt(m_index);
}

HK_FORCE_INLINE hkInt64 hkDataArray_Value::asInt64() const
{
	return m_impl->asInt64(m_index);
}

HK_FORCE_INLINE hkDataObject hkDataArray_Value::asObject() const
{
	return hkDataObject( const_cast<hkDataObjectImpl*>(m_impl->asObject(m_index)) );
}

HK_FORCE_INLINE hkDataArray hkDataArray_Value::asArray() const
{
	return hkDataArray( const_cast<hkDataArrayImpl*>(m_impl->asArray(m_index)) );
}

HK_FORCE_INLINE void hkDataArray_Value::operator=(const hkDataObject& obj)
{
	m_impl->setObject(m_index, const_cast<hkDataObjectImpl*>(obj.getImplementation()) );
}

HK_FORCE_INLINE void hkDataArray_Value::setNull()
{
	m_impl->setObject(m_index, HK_NULL);
}

HK_FORCE_INLINE void hkDataArray_Value::operator=(hkReal r)
{
	m_impl->setReal(m_index, r);
}

HK_FORCE_INLINE void hkDataArray_Value::operator=(hkHalf r)
{
	m_impl->setHalf(m_index, r);
}

HK_FORCE_INLINE void hkDataArray_Value::setVec(const hkReal* ra, int nreal)
{
	m_impl->setVec(m_index, ra);
}

HK_FORCE_INLINE void hkDataArray_Value::operator=(hkInt64 i)
{
	m_impl->setInt64(m_index, i);
}

HK_FORCE_INLINE void hkDataArray_Value::operator=(int i)
{
	m_impl->setInt(m_index, i);
}

HK_FORCE_INLINE void hkDataArray_Value::operator=(const char* s)
{
	m_impl->setString(m_index, s);
}

//////////////////////////////////////////////////////////////////////////
// Array Methods
//////////////////////////////////////////////////////////////////////////

HK_FORCE_INLINE int hkDataArray::getUnderlyingIntegerSize() const
{
	return m_impl->getUnderlyingIntegerSize();
}


#define SET_ALL(TYPE) \
	HK_FORCE_INLINE void hkDataArray::setAll(const TYPE* t, int n) \
	{ \
		m_impl->setAll(t,n); \
	}
SET_ALL(hkBool)
SET_ALL(char)
SET_ALL(hkInt8)
SET_ALL(hkUint8)
SET_ALL(hkInt16)
SET_ALL(hkUint16)
SET_ALL(hkInt32)
SET_ALL(hkUint32)
SET_ALL(hkInt64)
SET_ALL(hkUint64)
SET_ALL(hkReal)
SET_ALL(hkHalf)
#undef SET_ALL

HK_FORCE_INLINE hkDataArray hkDataArray::swizzleObjectMember(const char* name) const
{
	return hkDataArray( m_impl->swizzleObjectMember( name ) );
}

HK_FORCE_INLINE hkResult hkDataArray::asStridedBasicArray(hkStridedBasicArray& arrOut) const
{
	return m_impl->asStridedBasicArray(arrOut);
}


HK_FORCE_INLINE void hkDataArray::operator=(const hkDataArray& arr)
{
	if (m_impl != arr.m_impl)
	{
		arr.m_impl->addExternalReference();
		m_impl->addExternalReference();
		m_impl = arr.m_impl;
	}
}

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
