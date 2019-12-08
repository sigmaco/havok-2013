/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKSERIALIZE_TUPLE_OF_TUPLE
#define HKSERIALIZE_TUPLE_OF_TUPLE

class hkTypeInfo;

extern const hkClass TupleOfTupleClass;
extern const hkTypeInfo TupleOfTupleTypeInfo;

extern const hkClass TupleOfTupleChildClass;
extern const hkTypeInfo TupleOfTupleChildTypeInfo;

extern const hkClass TupleOfTupleChildChildChildClass;
extern const hkTypeInfo TupleOfTupleChildChildChildTypeInfo;

template <typename T>
static hkBool _equals(const T* a, const T* b, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}

	return true;
}


template <typename T>
static hkBool _equalsA(const hkArray<T>& a, const hkArray<T>& b)
{
	int size = a.getSize();

	if (size != b.getSize())
	{
		return false;
	}
	
	// Had to remove template use of _equals due to CTR
	for (int i = 0; i < size; i++)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}
	
	return true;
}

template <typename T>
static hkBool operator==(const hkArray<T>& a, const hkArray<T>& b)
{
	return _equalsA(a, b);
}

template <typename T>
static hkBool operator!=(const hkArray<T>& a, const hkArray<T>& b)
{
	return !_equalsA(a, b);
}

class TupleOfTuple: public hkReferencedObject
{
public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
	HK_DECLARE_REFLECTION();

	class Child
	{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, Child);
		HK_DECLARE_REFLECTION();

		class ChildChild
		{
		public:
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, ChildChild);
			HK_DECLARE_REFLECTION();

			hkBool operator==(const ChildChild& rhs) const
			{
				return _equalsA(m_nums, rhs.m_nums) 
					&& m_text == rhs.m_text 
					&& _equals(m_tuple, rhs.m_tuple, HK_COUNT_OF(m_tuple)); 
			}
			HK_FORCE_INLINE hkBool operator!=(const ChildChild& rhs) const { return !(*this == rhs); }

			ChildChild() {}
			ChildChild(const hkFinishLoadedObjectFlag& flag):
				m_nums(flag),
				m_text(flag)
			{}

			int m_tuple[4];
			hkArray<int> m_nums;
			hkStringPtr m_text;
		};

		hkBool operator==(const Child& rhs) const { return _equalsA(m_children, rhs.m_children) && _equals(m_tuple, rhs.m_tuple, HK_COUNT_OF(m_tuple)); }
		hkBool operator!=(const Child& rhs) const { return !(*this == rhs); }

		Child() {}
		Child(const hkFinishLoadedObjectFlag& flag):
			m_children(flag)
		{
		}

		hkArray<ChildChild> m_children;
		ChildChild m_tuple[3];
	};

	hkBool operator==(const TupleOfTuple& rhs) const { return _equalsA(m_children, rhs.m_children) && 
		_equals(m_tuple, rhs.m_tuple, HK_COUNT_OF(m_tuple)); }
	hkBool operator!=(const TupleOfTuple& rhs) const { return !(*this == rhs); }

	TupleOfTuple() {}
	TupleOfTuple(const hkFinishLoadedObjectFlag& flag):
		m_children(flag)
	{
	}

	hkArray<Child> m_children;
	Child m_tuple[2];

	// The serialization system cannot handle arrays of arrays like this because they are
	// not expressible in hkClassMember's type system
	//hkArray< hkArray< hkArray<int> > > m_nums;
	// For the same reason you cannot have this...
	//hkArray< hkArray<int> > m_nums;
};

#endif // HKSERIALIZE_TUPLE_OF_TUPLE

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
