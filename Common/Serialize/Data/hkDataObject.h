/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_DATA_OBJECT_H
#define HK_DATA_OBJECT_H

#include <Common/Base/Container/StringMap/hkStorageStringMap.h>
#include <Common/Serialize/TypeManager/hkTypeManager.h>

#include <Common/Serialize/Data/hkDataObjectDeclarations.h>
#include <Common/Serialize/Data/hkDataObjectImpl.h>

	/// This class wraps and handles data values stored in hkDataObject.
class hkDataObject_Value
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SERIALIZE, hkDataObject_Value);
		typedef hkDataObject_MemberHandle MemberHandle;
		typedef hkDataObject_Type Type;

			/// Assign 'l' to value.
		void operator=(const hkDataObject_Value& l);
			/// Assign 32-bit integer to value.
		void operator=(int i);
			/// Assign 64-bit integer to value.
		void operator=(hkInt64 i);
			/// Assign 32-bit float to value.
		void operator=(hkReal r);
			/// Assign bool to value.
		void operator=(bool b);
			/// Assign 16-bit float to value.
		void operator=(hkHalf r);
			/// Assign c-style string to value.
		void operator=(const char* s);
			/// Assign array or tuple to value.
		void operator=(const hkDataArray& l);
			/// Assign object to value.
		void operator=(const hkDataObject& o);
			/// Assign object to value.
		void operator=(const hkDataObjectImpl* o);
			/// Assign HK_NULL object
		void setNull();

			/// Get value as 32-bit integer.
		int asInt() const;
			/// Get value as 64-bit integer.
		hkInt64 asInt64() const;
			/// Get value as 32-bit float.
		hkReal asReal() const;
			/// Get value as c-style string.
		const char* asString() const;
			/// Get value as array or tuple.
		hkDataArray asArray() const;
			/// Get value as object.
		hkDataObject asObject() const;
			/// Get value as array of floats, e.g., hkVector4, hkMatrix4.
			/// 'n' indicates the number of floats you expect to get, e.g. 4, 8, 12 or 16.
		const hkReal* asVec(int n) const;

			/// Returns true if this value on this object has been set
		HK_FORCE_INLINE hkBool32 isSet() const;
			/// Returns if valid
		HK_FORCE_INLINE hkBool32 isValid() const { return m_impl != HK_NULL; }

			/// Get value type.
		Type getType() const;

		HK_FORCE_INLINE void getMemberInfo(hkDataClass_MemberInfo& infoOut) const;

		// Used internally.
		void setVec(const hkReal* r, int n);
#				define HK_VALUE_ACCESS2(HKTYPE,TYPE) \
			void operator=(const HKTYPE& v) \
			{ this->setVec(reinterpret_cast<const hkReal*>(&v), sizeof(HKTYPE)/sizeof(hkReal)); } \
			const HKTYPE& as##TYPE() const \
			{ return *reinterpret_cast<const HKTYPE*>(asVec(sizeof(HKTYPE)/sizeof(hkReal))); }
#				define HK_VALUE_ACCESS(TYPE) HK_VALUE_ACCESS2(hk##TYPE,TYPE)
		HK_VALUE_ACCESS(Vector4)
		HK_VALUE_ACCESS(Quaternion)
		HK_VALUE_ACCESS(Matrix3)
		HK_VALUE_ACCESS(Rotation)
		HK_VALUE_ACCESS(QsTransform)
		HK_VALUE_ACCESS(Matrix4)
		HK_VALUE_ACCESS(Transform)
#undef			HK_VALUE_ACCESS2
#undef			HK_VALUE_ACCESS

		friend class hkDataObjectImpl;
		hkDataObject_Value(hkDataObjectImpl* impl, MemberHandle handle) : m_impl(impl), m_handle(handle) { }
		hkDataObjectImpl* m_impl;
		MemberHandle m_handle;
};

	/// The hkDataObject class is a public accessor to reflected data
	/// managed by the private hkDataObjectImpl class.
	/// It may only contain data defined by hkDataClass.
	/// The class implements the Python-alike object data access.
class hkDataObject
{
	public:
		typedef hkDataObject_Type Type;
		typedef hkDataObject_MemberHandle MemberHandle;
		typedef hkDataObject_Iterator Iterator;
		typedef hkDataObject_Value Value;
		typedef hkDataObject_Handle Handle;
		
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SERIALIZE, hkDataObject);

			/// Null constructor
		hkDataObject();
			/// Constructor - instantiates a temporary public wrapper
			/// using the private hkDataObjectImpl.
		hkDataObject( hkDataObjectImpl* impl );
			/// Constructor - instantiates a temporary public wrapper
			/// using the hkDataObjectImpl shared by the given 'o'.
		hkDataObject( const hkDataObject& o );

			/// Assign a temporary wrapper using the hkDataObjectImpl shared by the given 'o'.
		void operator=( const hkDataObject& o );
			/// Return true if hkDataObjects are the same.
		bool operator==( const hkDataObject& o );
			/// Return true if hkDataObjects are different.
		bool operator!=( const hkDataObject& o );

			/// Destructor.
		~hkDataObject();


			/// Get value of class member named 'name'.
		Value operator[](const char* name);
			/// Get const value of class member named 'name'.
		const Value operator[](const char* name) const;

			/// Get object's handle.
		Handle getHandle() const;
			/// Get object's implementation.
		hkDataObjectImpl* getImplementation() { return m_impl; }
			/// Get object's const implementation.
		const hkDataObjectImpl* getImplementation() const { return m_impl; }

			/// Get object's class.
		const hkDataClass getClass() const;
			/// Is the object null.
		hkBool32 isNull() const;

			/// Get class member iterator.
		Iterator getMemberIterator() const;
			/// Is the iterator valid.
		hkBool32 isValid(Iterator i) const;
			/// Get next iterator.
		Iterator getNextMember(Iterator i) const;
			/// Get member value by iterator.
		const Value getMemberValue(Iterator i) const;
			/// Get member name by iterator.
		const char* getMemberName(Iterator i) const;

			/// Return true if object stores value of class member named 'name'.
		hkBool32 hasMember(const char* name) const;

			/// Get all of the values in the same order as the members from the class
		void getAllMemberHandles(hkArrayBase<MemberHandle>& handles) const;

		void destroy();

	private:

		hkDataObjectImpl* m_impl;
};

struct hkStridedBasicArray;


	/// This class wraps and handles data value of hkDataArray items.
class hkDataArray_Value
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SERIALIZE, hkDataArray_Value);

		typedef hkDataObject_Type Type;

			/// Assign object value 'l' to value.
		void operator=(const hkDataObject::Value& l);
			/// Assign array value 'l' to value.
		void operator=(const hkDataArray_Value& l);
			/// Assign 32-bit integer to value.
		void operator=(int i);
			/// Assign 64-bit integer to value.
		void operator=(hkInt64 i);
			/// Assign 32-bit float to value.
		void operator=(hkReal r);
			/// Assign 16-bit float to value.
		void operator=(hkHalf r);
			/// Assign array or a tuple to value.
		void operator=(const hkDataArray& l);
			/// Assign object to value.
		void operator=(const hkDataObject& o);
			/// Assign c-style string to value.
		void operator=(const char* s);
			/// Same as assigning an empty hkDataObject
		void setNull();

			/// Get value as 32-bit integer. If the internal representation
			/// is 64-bit it will be truncated
		int asInt() const;
			/// Get value as 64-bit integer.
		hkInt64 asInt64() const;
			/// Get value as 32-bit float.
		hkReal asReal() const;
			/// Get value as object.
		hkDataObject asObject() const;
			/// Get value as array or tuple.
		hkDataArray asArray() const;
			/// Get value as c-style string.
		const char* asString() const;
			/// Get value as array of floats, e.g., hkVector4, hkMatrix4.
			/// 'n' indicates the number of floats you expect to get, e.g. 4, 8, 12 or 16.
		const hkReal* asVec(int n) const;

			/// Clear the value.
		void clear();

			/// Get the value type.
		Type getType() const;

		// Used internally.
		void setVec(const hkReal* r, int nreal);
#				define HK_VALUE_ACCESS2(HKTYPE,TYPE) \
			void operator=(const HKTYPE& v) \
				{ this->setVec(reinterpret_cast<const hkReal*>(&v), sizeof(HKTYPE)/sizeof(hkReal)); } \
			const HKTYPE& as##TYPE() const \
				{ return *reinterpret_cast<const HKTYPE*>(asVec(sizeof(HKTYPE)/sizeof(hkReal))); }
#				define HK_VALUE_ACCESS(TYPE) HK_VALUE_ACCESS2(hk##TYPE,TYPE)
		HK_VALUE_ACCESS(Vector4)
		HK_VALUE_ACCESS(Quaternion)
		HK_VALUE_ACCESS(Matrix3)
		HK_VALUE_ACCESS(Rotation)
		HK_VALUE_ACCESS(QsTransform)
		HK_VALUE_ACCESS(Matrix4)
		HK_VALUE_ACCESS(Transform)
#undef			HK_VALUE_ACCESS2
#undef			HK_VALUE_ACCESS

	private:

		friend class hkDataArray;
		hkDataArray_Value(hkDataArrayImpl* impl, int idx) : m_impl(impl), m_index(idx) {}
		hkDataArrayImpl* m_impl;
		int m_index;
};


	/// The hkDataArray is a public accessor to a reflected array of data.
class hkDataArray
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SERIALIZE, hkDataArray);

		typedef hkDataObject::Type Type;
		typedef hkDataArray_Value Value;

			/// Constructor - instantiates a temporary public wrapper
			/// using the private hkDataArrayImpl.
		explicit hkDataArray( hkDataArrayImpl* i );
			/// Constructor - instantiates a temporary public wrapper
			/// using the hkDataArrayImpl shared by the given 'a'.
		hkDataArray(const hkDataArray& a);
			/// Assign a temporary wrapper using the hkDataArrayImpl shared by the given 'a'.
		void operator=(const hkDataArray& a);
			/// Destructor.
		~hkDataArray();

			/// 
		hkResult asStridedBasicArray(hkStridedBasicArray& arrOut) const;

			/// Clear array. Size set to 0.
		void clear();
			/// Get array size.
		int getSize() const;
			/// Reserve array capacity.
		void reserve(int n);
			/// Set array size.
 		void setSize(int n);
			/// Get the size of the internal storage type.
			/// This may be less than the size suggested by getType()
		int getUnderlyingIntegerSize() const;
			/// Get value of i'th array item.
	  	Value operator[](int i);
			/// Get const value of i'th array item.
  		const Value operator[](int i) const;
			/// Get array item type.
		Type getType() const;
			/// Get array item class.
		hkDataClass getClass() const;
			/// Get data slice of class member named 'name' from object items in array.
		hkDataArray swizzleObjectMember(const char* name) const;

			/// Set array size to 'n' and initialize the array items with values from 'a'.
		void setAll(const hkBool* a, int n);
			/// Set array size to 'n' and initialize the array items with values from 'a'.
		void setAll(const char* a, int n);
			/// Set array size to 'n' and initialize the array items with values from 'a'.
		void setAll(const hkInt8* a, int n);
			/// Set array size to 'n' and initialize the array items with values from 'a'.
		void setAll(const hkUint8* a, int n);
			/// Set array size to 'n' and initialize the array items with values from 'a'.
		void setAll(const hkInt16* a, int n);
			/// Set array size to 'n' and initialize the array items with values from 'a'.
		void setAll(const hkUint16* a, int n);
			/// Set array size to 'n' and initialize the array items with values from 'a'.
		void setAll(const hkInt32* a, int n);
			/// Set array size to 'n' and initialize the array items with values from 'a'.
		void setAll(const hkUint32* a, int n);
			/// Set array size to 'n' and initialize the array items with values from 'a'.
		void setAll(const hkInt64* a, int n);
			/// Set array size to 'n' and initialize the array items with values from 'a'.
		void setAll(const hkUint64* a, int n);
			/// Set array size to 'n' and initialize the array items with values from 'a'.
		void setAll(const hkReal* a, int n);
			/// Set array size to 'n' and initialize the array items with values from 'a'.
		void setAll(const hkHalf* a, int n);

			/// Get the world the array belongs to
		hkDataWorld* getWorld() const;

			/// Get array's implementation.
		hkDataArrayImpl* getImplementation() { return m_impl; }
			/// Get array's const implementation.
		const hkDataArrayImpl* getImplementation() const { return m_impl; }

	private:

		hkDataArrayImpl* m_impl;
};

	/// This class defines reflection information for any reflected type.
	/// Unlike hkClass it defines reflection for class data members only.
class hkDataClass
{
	public:
		
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SERIALIZE, hkDataClass);

		typedef hkDataClass_MemberInfo MemberInfo;

			/// This structure contains all the information needed to construct a hkDataClass object.
		struct Cinfo
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkDataClass::Cinfo);
				/// This structure contains all the information needed to construct
				/// a member of hkDataClass.
			struct Member
			{
				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkDataClass::Cinfo::Member);
				void set( const char* n, hkDataObject::Type t)
				{
					name = n; 
					type = t;
				}
				const char* name;
				hkDataObject::Type type;
				const void *valuePtr;
			};
			const char* name;
			int version;
			const char* parent;
			hkArray<Member> members;
		};
	
	public:

			/// Constructor - instantiates a temporary public wrapper
			/// using the private hkDataClassImpl.
		hkDataClass( hkDataClassImpl* impl );
			/// Destructor.
		~hkDataClass();

			/// Is the class null.
		hkBool32 isNull() const;
			/// Get class name.
		const char* getName() const;
			/// Get class version.
		int getVersion() const;
			/// Get class parent.
		hkDataClass getParent() const;

			/// Get the world the class belongs to.
		const hkDataWorld* getWorld() const;
			/// Is this a parent class of class k.
		hkBool isSuperClass(const hkDataClass& k) const;

			/// Get the number of members declared in this class (not including parent class members).
		int getNumDeclaredMembers() const;
			/// Get the i'th member declared in this class (not including parent class members).
		void getDeclaredMemberInfo(int i, MemberInfo& info) const;
			/// Get the index of declared member named 'name' or -1 if not found.
		int getDeclaredMemberIndexByName(const char* name) const;
			/// Get all declared members (not including parent class members).
		void getAllDeclaredMemberInfo( hkArrayBase<MemberInfo>& minfo ) const;

			/// Get the number of members in this class (including parent class members).
		int getNumMembers() const;
			/// Get the i'th member (including parent class members).
		void getMemberInfo(int i, MemberInfo& info) const;
			/// Get the index of member named 'name' or -1 if not found.
		int getMemberIndexByName(const char* name) const;
			/// Get all members (including parent class members).
		void getAllMemberInfo( hkArrayBase<MemberInfo>& minfo ) const;

			/// Get the const private implementation of the class.
		const hkDataClassImpl* getImplementation() const { return m_impl; }
			/// Get the private implementation of the class.
		hkDataClassImpl* getImplementation() { return m_impl; }

			/// Get a construction info from this object.
		void getCinfo( Cinfo& infoOut ) const;

	private:

		hkDataClassImpl* m_impl;
};


	/// This is an abstract class which defines interfaces to implement a container,
	/// and to store and manage reflected data defined by hkDataClass and represented
	/// by hkDataObject and hkDataArray.
class hkDataWorld : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);

			/// Create a new class from the cinfo.
		virtual hkDataClassImpl* newClass(const hkDataClass::Cinfo& cinfo) = 0;

			/// Create a new object of the given type in the world.
			/// The 'klass' must belong to the world when instantiating hkDataObject.
		virtual hkDataObjectImpl* newObject(const hkDataClass& klass, bool createdDuringPatching = false) const = 0;

			/// Create a new array as a member of obj.
			/// The 'obj' must belong to the world when instantiating hkDataArray.
		virtual hkDataArrayImpl* newArray(hkDataObject& obj, hkDataObject::MemberHandle handle, const hkDataClass::MemberInfo& minfo) const = 0;

			/// hkDataWorld supported types.
		enum DataWorldType
		{
				/// Native type. hkDataWorld contains wrapped native
				/// object and hkClass pointers that are represented
				/// by hkDataObject and hkDataClass respectively.
				/// See hkDataWorldNative for details.
			TYPE_NATIVE,

				/// Dictionary type. hkDataWorld contains instances of
				/// hkDataObject described by hkDataClass.
				/// See hkDataWorldDict for details.
			TYPE_DICTIONARY
		};

			/// Get world type.
		virtual hkEnum<DataWorldType, hkInt32> getType() const = 0;
			/// Get top level object from the world.
			/// By default, the first created hkDataObject is the top level object.
		virtual hkDataObject getContents() const = 0;
			/// Find all the registered classes in the world.
		virtual void findAllClasses(hkArray<hkDataClassImpl*>::Temp& classesOut) const = 0;
			/// Find the registered hkDataClass in the world by name.
		virtual hkDataClassImpl* findClass(const char* name) const = 0;
			/// Find the hkDataObject in the world by the object handle.
		virtual hkDataObject findObject(const hkDataObject::Handle& handle) const = 0;

			/// Get the type manager
		virtual hkTypeManager& getTypeManager() = 0;

		// Mutate class info

			/// Rename a class in this world.
		virtual void renameClass(hkDataClass& klass, const char* newName);
			/// Remove a class in this world.
		virtual void removeClass(hkDataClass& klass);

			/// Set new version for the given class in this world.
		virtual void setClassVersion(hkDataClass& klass, int newVersion);
			/// Set new parent for the given class in this world.
		virtual void setClassParent(hkDataClass& klass, hkDataClass& parent);

			/// Add new member to the given class in this world.
		virtual void addClassMember(hkDataClass& klass, const char* name, hkDataObject::Type type, const void* valuePtr);

			/// Set the default value for a member of a given class in the world.
		virtual void setClassMemberDefault(hkDataClass& klass, const char* name, const void* valuePtr);
			/// Rename specified member of the given class in this world.
		virtual void renameClassMember(hkDataClass& klass, const char* oldName, const char* newName);
			/// Remove specified member from the given class in this world.
		virtual void removeClassMember(hkDataClass& klass, const char* name);
			/// Find all objects in the class hierarchy of the given base class name.
		virtual void findObjectsByBaseClass(const char* baseClassName, hkArray<hkDataObjectImpl*>::Temp& objectsOut) const;
			/// Find all objects of the given specific class name only.
		virtual void findObjectsByExactClass(const char* className, hkArray<hkDataObjectImpl*>::Temp& objectsOut) const;
			/// Cast object type to the given class in this world.
		virtual void castObject(hkDataObject& obj, const hkDataClass& newClass);

			/// Create and register a new dictionary class based on the class named 'name' from another world.
		virtual hkDataClassImpl* copyClassFromWorld(const char* name, const hkDataWorld& worldFrom); 

			/// Add a class member using a type expression, and a default value
		void addClassMemberTypeExpression(hkDataClass& klass, const char* name, const char* expr, const char* className, const void* valuePtr);
};

template <>
struct hkMapOperations<hkDataObject::Handle>
{
	inline static unsigned hash( const hkDataObject::Handle& key, unsigned mod )
	{
		return unsigned((hkUlong(key.p0) >> 4) * 2654435761U) & mod;
	}
	inline static void invalidate( hkDataObject::Handle& key )
	{
		key.p0 = (void*)hkUlong(-1);
	}
	inline static hkBool32 isValid( hkDataObject::Handle& key )
	{
		return key.p0 != (void*)hkUlong(-1);
	}
	inline static hkBool32 equal( const hkDataObject::Handle& key0, const hkDataObject::Handle& key1 )
	{
		return key0.p0 == key1.p0 && key0.p1 == key1.p1;
	}
};

#include <Common/Serialize/Data/hkDataObject.inl>

#endif // HK_DATA_OBJECT_H

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
