/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_VARIANT_DATA_UTIL_H
#define HK_VARIANT_DATA_UTIL_H

#include <Common/Serialize/Data/hkDataObject.h>
#include <Common/Base/Reflection/hkClassMember.h>

struct hkStridedBasicArray
{
	hkClassMember::Type m_type;	///< The type of the member (can only be a basic type: integer, bool, half, float, double)
	int m_tupleSize;			///< The tuple size (1 if not a tuple)
	void* m_data;					///< Pointer to first element in array
	int m_size;					///< Total number of elements
	int m_stride;					///< Amount of bytes between data elements

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkStridedBasicArray );
};

class hkVtableClassRegistry;
class hkClassNameRegistry;
class hkTypeInfoRegistry;

/// hkVariantDataUtil provides functionality to simplify the access of memory as interpreted by 
/// type information. 
/// 
/// Havok's type system, as defined in hkMemoryClass, can represent many different types. For example
/// there is a type for each possible kind of integer. It can be tedious to work out what the exact type
/// of a piece of memory is when all that is required is to set it or read it as an int. The util 
/// provides methods so you can access any underlying integral type as an int, and internally 
/// the util will perform the appropriate conversion. 
///
/// The other area of functionality is the creation and destruction of arrays of types. There are two
/// styles of array function: one which works on blocks of memory interpreted as arrays, and another which 
/// allows the interpretation of a piece of memory that holds an hkArray-derived type.
///
/// There is some functionality revolving around 'finish'ing. During serialization a piece of memory may need 
/// to be turned into an object of some type. The serialization can fill in data about the members, but can't for 
/// example fill in the vtable/s. Finishing runs a specialized constructor which fills in such details. It may also
/// invoke some other construction. It is worth noting though that 'finishing' assumes that serialized data members
/// are set and valid; trying to 'finish' a raw piece of memory to construct an object of some type could cause 
/// undefined behavior.
struct hkVariantDataUtil
{

		/// Get the value of type stored at 'data' as a hkReal
	static hkReal HK_CALL getReal(hkClassMember::Type type, const void* data);
		/// Set the type stored at data with the hkReal value
	static void HK_CALL setReal(hkClassMember::Type type, void* data, hkReal value);

		/// Set from a half value
	static void HK_CALL setHalf(hkClassMember::Type type, void* data, hkHalf value);

		/// Get an int value being held at data location
	static hkInt64 HK_CALL getInt(hkClassMember::Type type, const void* data);
		/// Get an int value - which has both a type and subtype (handles enums correctly)
	static hkInt64 HK_CALL getInt(hkClassMember::Type type, hkClassMember::Type subType, const void* data);

		/// Set an int at data location
	static void HK_CALL setInt(hkClassMember::Type type, void* data, hkInt64 value);
		/// Set an int at data location using both type and subType (handles enums correctly)
	static void HK_CALL setInt(hkClassMember::Type type, hkClassMember::Type subType, void* data, hkInt64 value);

		/// Get the string of 'type' held at location 'data'
	static const char* HK_CALL getString(hkClassMember::Type type, const void* data );
		/// Set the string of 'type' at the location 'data'
	static void HK_CALL setString(hkClassMember::Type type, void* data, const char* value );

		/// Returns true if the type needs construction 
	static hkBool HK_CALL needsConstruction(const hkTypeInfoRegistry* infoReg, hkClassMember& mem);

		/// Create a new instance of class 'cls' in the location 'data'
	static void HK_CALL newInstance(const hkClass& cls, void* data);
		/// Delete the instance of class 'cls' at location 'data'
	static void HK_CALL deleteInstance(const hkTypeInfoRegistry* infoReg, const hkClass& cls, void* data);
		/// 'finish' an object 
	static void HK_CALL finishObject(const hkTypeInfoRegistry* infoReg, const hkClass& cls, void* data);
	static void HK_CALL finishObjectWithoutTracker(const hkTypeInfoRegistry* infoReg, const hkClass& cls, void* data);

		/// Construct an array of structs of type 'cls', 'size' members in memory starting from 'array' and with a stride of 'stride'
	static void HK_CALL newArray(const hkTypeInfoRegistry* infoReg, const hkClass& cls, void* array, int size, int stride);
		/// Construct an array of type 'type', 'size' elements, in the memory starting from 'array' and with a stride of 'stride'
	static void HK_CALL newArray(const hkTypeInfoRegistry* infoReg, hkClassMember::Type type, const hkClass* cls, void* array, int size, int stride);
		/// Call the finish function on an array of structs of type 'cls'
	static void HK_CALL finishObjectArray(const hkTypeInfoRegistry* infoReg, const hkClass& cls, void* array, int size, int stride);

		/// Delete an array holding structs of type 'cls', starting at address 'array', of 'size' elements and with a stride 'stride'
	static void HK_CALL deleteArray(const hkTypeInfoRegistry* infoReg, const hkClass& cls, void* array, int size, int stride);
		/// Delete an array holding 'type', starting at address 'array', of 'size' elements and with a stride of 'stride'
	static void HK_CALL deleteArray(const hkTypeInfoRegistry* infoReg, hkClassMember::Type type, const hkClass* cls, void* array, int size, int stride);

		/// Clear a hkArray derived type. 
	static void HK_CALL clearArray(const hkTypeInfoRegistry* infoReg, void* arrayIn, hkClassMember::Type type, const hkClass* cls);
		/// Set the hkArray size
	static void* HK_CALL setArraySize(const hkTypeInfoRegistry* infoReg, void* arrayIn, hkClassMember::Type type, const hkClass* cls, int size);
		/// Get the hkArray size
	static int HK_CALL getArraySize(void* arrayIn);
		/// Reserve memory on an hkArray
	static void* HK_CALL reserveArray(void* arrayIn, hkClassMember::Type type, const hkClass* cls, int size);

		/// Calc an element size
	static int HK_CALL calcElementSize(hkClassMember::Type type, const hkClass* cls);

		/// Return the amount of reals that make up the type
	static int HK_CALL calcNumReals(hkClassMember::Type type, int tupleCount);
		/// Set reals 
	static void HK_CALL setReals(hkClassMember::Type type, int tupleSize, const hkReal* src, void* data, int numReals = -1);
		/// Get as reals - need to pass in a buffer, as the data might need to be converted
	static const hkReal* HK_CALL getReals(hkClassMember::Type type, int tupleSize, const void* data, hkArray<hkUint8>& buffer);

	static void HK_CALL setObject(const hkVariant& var, hkClassMember::Type type, void* data);
		/// Get an object (data points to the type in place; i.e. if the type is pointer, data points to the pointer)
	static hkVariant HK_CALL getObject( hkClassMember::Type type, const hkClass* cls, const hkVtableClassRegistry* vtableReg, const hkClassNameRegistry* classReg, const void* data);

		/// Find the most derived class of object
	static const hkClass* HK_CALL findMostDerivedClass(const void* object, const hkVtableClassRegistry* vtable, const hkClassNameRegistry* classReg);
		/// Return object as a variant, using the underlying class and pointer for the type
	static hkVariant HK_CALL getVariantWithMostDerivedClass(const hkClass* klass, const void* object, const hkVtableClassRegistry* vtable, const hkClassNameRegistry* classReg);

		/// Set a pointer. 'cls' defines the pointer type. obj is the pointer to set. If 'isReferenced' is 
		/// set to true the pointer will have addReference called on it if that's appropriate.
	static void setPointer(const hkClass& cls, void* obj, void** dst, hkBool isReferenced = true);

		/// Calculate the size of a 'basic type' (i.e. not array/tuple, etc.). Returns 0 if couldn't determine.
	static hk_size_t HK_CALL calcBasicElementSize(hkClassMember::Type type, const hkClass* klass);
		/// Calculate the size of a type. Returns 0 if couldn't determine.
	static hk_size_t HK_CALL calcElementSize(hkClassMember::Type type, hkClassMember::Type subType, const hkClass* klass, int tupleSize);

		/// Convert type to int32
	static void HK_CALL convertTypeToInt32Array(hkClassMember::Type srcType, const void* srcIn, hkInt32* dst, int size);

		/// Convert an array of hkInt32 into any other integral array type. 
	static void HK_CALL convertInt32ToTypeArray(const hkInt32* src, hkClassMember::Type dstType, void* dstIn, int size);
		/// Convert an array of hkUint32 into any other integral array type
	static void HK_CALL convertUint32ToTypeArray(const hkUint32* src, hkClassMember::Type dstType, void* dstIn, int size);
		/// Convert an array of hkInt64 into any other integal array type
	static void HK_CALL convertInt64ToTypeArray(const hkInt64* src, hkClassMember::Type dstType, void* dstIn, int size);

		/// Convert any integral type to bool array
	static void HK_CALL convertTypeToBoolArray(hkClassMember::Type srcType, const void* srcIn, hkBool* dst, int size);
		/// Convert a bool array to any integral type
	static void convertBoolToTypeArray(const hkBool* src, hkClassMember::Type dstType, void* dstIn, int size);

		/// Convert any integral type to any other integral type
	static void HK_CALL convertTypeToTypeArray(hkClassMember::Type srcType, const void* srcIn, hkClassMember::Type dstType, void* dst, int size);

		/// Do a strided copy from src to the destination
	static void HK_CALL stridedCopy(const void* src, int srcStride, void* dst, int dstStride, int eleSize, int size);

		/// Convert arrays (potentially strided) 
	static void HK_CALL convertArray(const hkStridedBasicArray& src, const hkStridedBasicArray& dst);
};

#endif // HK_VARIANT_DATA_UTIL_H

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
