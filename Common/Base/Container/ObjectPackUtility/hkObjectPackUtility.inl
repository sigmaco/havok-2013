/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Container/ObjectPackUtility/hkObjectPackUtility.h>
#include <Common/Base/Reflection/hkClass.h>


template <class ContainingObject>
hkObjectPackUtility<ContainingObject>::hkObjectPackUtility(const ContainingObject& object) : m_copyFromObject(&object), m_newObject(HK_NULL)
{
	HK_ASSERT2(0x2be1f83a, &object, "hkObjectPackUtility object is NULL");
}


template <class ContainingObject>
template<typename ArrayType>
hkResult hkObjectPackUtility<ContainingObject>::addPackedArray(const hkArray<ArrayType>& array)
{
	ArrayMember localMember;
	localMember.m_pointer = (void*)&array;
	localMember.m_objectSize = hkSizeOf(ArrayType);
	m_arrayMembers.pushBack(localMember);
	return HK_SUCCESS;
}

template <class ContainingObject>
template<typename ArrayType>
hkResult hkObjectPackUtility<ContainingObject>::addArrayNotOwned(const hkArray<ArrayType>& array)
{
	//HK_ASSERT2(0x47be0cf1, m_newObject, "markArrayNotOwned can only be called after getFinishedObject");

	//const int arrayOffset = reinterpret_cast<const char*>(&array) - reinterpret_cast<const char*>(m_copyFromObject);
	//hkArray<ArrayType>& newArray = *reinterpret_cast<hkArray<ArrayType>*>(reinterpret_cast<char *>(m_newObject) + arrayOffset);

	//newArray._setDataUnchecked(newArray.begin(), newArray.getSize(), newArray.getCapacityAndFlags() | array.DONT_DEALLOCATE_FLAG);
	//return HK_SUCCESS;

	HK_ASSERT2(0x47be0cf1, false, "This method shouldn't be called anymore");
	return HK_FAILURE;
}

template <class ContainingObject>
template<typename ArrayType>
hkResult hkObjectPackUtility<ContainingObject>::stealArrayContents(hkArray<ArrayType>& array)
{
	ArrayMember localMember;
	localMember.m_pointer = (void*)&array;
	localMember.m_objectSize = 0x80000000;
	m_arrayMembers.pushBack(localMember);
	return HK_SUCCESS;
}

template <class ContainingObject>
template<typename ArrayType>
bool hkObjectPackUtility<ContainingObject>::isAlreadyPacked(hkArray<ArrayType>& array)
{
	const int arrayOffset = int(reinterpret_cast<const char*>(array.begin()) - reinterpret_cast<const char*>(m_copyFromObject));
	return (arrayOffset > 0) && (arrayOffset < m_copyFromObject->getAllocatedSize());
}

template <class ContainingObject>
ContainingObject* hkObjectPackUtility<ContainingObject>::getFinishedObject()
{
	HK_ASSERT2(0x25b7f32f, m_newObject == HK_NULL, "getFinishedObject() can only be called once");
	int totalExtraSize = 0;
	for(int i=0;i<m_arrayMembers.getSize();i++)
	{
		const int stealArray = m_arrayMembers[i].m_objectSize >> 31;
		if (stealArray)
		{
			continue;
		}
		hkArray<char>* array = (hkArray<char>*)m_arrayMembers[i].m_pointer;
		totalExtraSize += HK_NEXT_MULTIPLE_OF(16, m_arrayMembers[i].m_objectSize * array->getSize());
	}

	const int paddedObjectSize	= HK_NEXT_MULTIPLE_OF(16, hkSizeOf(ContainingObject));
	const int allocatedSize		= paddedObjectSize + totalExtraSize;
	HK_ASSERT2(0x1fac4447, (allocatedSize >= 0) && (allocatedSize <= 65536), "Invalid size");
	m_newObject = reinterpret_cast<ContainingObject*>(hkMemHeapBlockAlloc<char>(allocatedSize));
	// Need to set up vtable
	
	new(m_newObject) ContainingObject();

	
	
	
	hkString::memCpy(m_newObject, m_copyFromObject, hkSizeOf(ContainingObject));
	
	m_newObject->m_memSizeAndFlags = hkUint16(allocatedSize);
	m_newObject->m_referenceCount = 1;
	HK_MEMORY_TRACKER_NEW_SIZED_REFOBJECT(ContainingObject, m_newObject, allocatedSize);

	//m_offsetSoFar(0), m_totalExtraSize(HK_NEXT_MULTIPLE_OF(16, totalExtraSize))
	// COPY
	int offsetSoFar = 0;
	for(int i=0;i<m_arrayMembers.getSize();i++)
	{
		const int stealArray = m_arrayMembers[i].m_objectSize >> 31;
		hkArray<char>* array = (hkArray<char>*)m_arrayMembers[i].m_pointer;
		const int arrayOffset = int(reinterpret_cast<const char*>(array) - reinterpret_cast<const char*>(m_copyFromObject));
		if (stealArray)
		{
			hkArray<char>& newArray = *reinterpret_cast<hkArray<char>*>(reinterpret_cast<char *>(m_newObject) + arrayOffset);
			newArray._setDataUnchecked(array->begin(), array->getSize(), array->getCapacityAndFlags());
			array->_setDataUnchecked(HK_NULL, 0, 0);
		}
		else
		{
			HK_ASSERT2(0x3cd21013, (offsetSoFar >= 0) && ((offsetSoFar & 0x0f) == 0), "Invalid internal offset");
			const int sizeToCopy = m_arrayMembers[i].m_objectSize * array->getSize();
			HK_ASSERT2(0x191060bb, (offsetSoFar + sizeToCopy) < 65536, "Array too large or invalid offset");

			char* relocatedArrayPtr = reinterpret_cast<char*>(m_newObject) + paddedObjectSize + offsetSoFar;
			hkString::memCpy(relocatedArrayPtr, array->begin(), sizeToCopy);

			hkArray<char>& newArray = *reinterpret_cast<hkArray<char>*>(reinterpret_cast<char *>(m_newObject) + arrayOffset);

			HK_ASSERT2(0x27fec3e6, (offsetSoFar & 0x0f) == 0, "Invalid internal offset");
			newArray._setDataUnchecked(relocatedArrayPtr, array->getSize(), array->getCapacityAndFlags() | array->DONT_DEALLOCATE_FLAG);

			offsetSoFar = HK_NEXT_MULTIPLE_OF(16, offsetSoFar + sizeToCopy);
			HK_ASSERT2(0x5752e30c, offsetSoFar <= totalExtraSize, "Array overflows allocated object size");
		}
	}

#ifdef HK_DEBUG
	const hkClass& klass = ContainingObject::staticClass();
	int numArrays = checkPackedArrays(klass, 0);
	if (numArrays == 0)
	{
		HK_WARN(0x5752e30f, "The object hasn't got any array members. Make sure the class was reflected or if the object still needs to be packed.");
	}
#endif

	// FINISH
	return m_newObject;
}

//
//	Checks if the packed array members are valid. Returns the total number of array members found.

template <class ContainingObject>
int hkObjectPackUtility<ContainingObject>::checkPackedArrays(const hkClass& baseClass, int baseOffset)
{
	int numArrays = 0;
	const int numMembers = baseClass.getNumMembers();

	for (int mi = 0; mi < numMembers; mi++)
	{
		const hkClassMember& member = baseClass.getMember(mi);
		const hkClassMember::Type memberType = member.getType();

		switch ( memberType )
		{
		case hkClassMember::TYPE_ARRAY:
			{
				numArrays++;

				int arrayOffset = baseOffset + member.getOffset();
				hkArray<char>& newArray = *reinterpret_cast<hkArray<char>*>(reinterpret_cast<char *>(m_newObject) + arrayOffset);
				const hkArray<char>& origArray = *reinterpret_cast<const hkArray<char>*>(reinterpret_cast<const char *>(m_copyFromObject) + arrayOffset);
				if (newArray.begin() == HK_NULL && origArray.begin() == HK_NULL)
				{
					continue;
				}
				HK_ASSERT2(0x5752e30e, newArray.begin() != origArray.begin(), "The packed and the original object point to the same array data. " 
					"Make sure you have packed or stolen contents of all array members.");
		}
			break;

		case hkClassMember::TYPE_STRUCT:
			{
				const hkClass& childClass = member.getStructClass();
				const int memberOffset = member.getOffset();
				numArrays += checkPackedArrays(childClass, baseOffset + memberOffset);
			}
			break;

		default:
			break;
		}
	}

	return numArrays;
}


hkObjectUnpackUtility::hkObjectUnpackUtility(void* object, const void* oldPointer, int totalExtraSize) :
		m_newObject(object), m_oldPointer(hkUlong(oldPointer))
{
}

template<typename ArrayType>
hkResult hkObjectUnpackUtility::patchArray(hkArray<ArrayType>& array)
{
	int arrayOffset = reinterpret_cast<hkUlong>(array.begin()) - m_oldPointer;
	HK_ASSERT2(0x404702e2, (arrayOffset >= 0) && (arrayOffset <= 0xffff), "Invalid array for unpack");
	array._setDataUnchecked(reinterpret_cast<ArrayType*>((char*)m_newObject + arrayOffset), array.getSize(), array.getCapacity() | array.DONT_DEALLOCATE_FLAG);
	HK_ASSERT2(0x171cafac, (hkUlong((char*)m_newObject + arrayOffset) & 0x0f) == 0, "Incorrect alignment");
	return HK_SUCCESS;
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
