/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_TYPE_MANAGER_H
#define HK_TYPE_MANAGER_H

#include <Common/Base/Container/PointerMultiMap/hkPointerMultiMap.h>
#include <Common/Base/Container/StringMap/hkStorageStringMap.h>
#include <Common/Base/Memory/Allocator/FreeList/hkFreeList.h>
#include <Common/Base/Container/SubString/hkSubString.h>

struct hkLegacyType
{
	public:
		enum Type
		{
				/// Not reflected.
			TYPE_VOID = 0,

				/// Byte, signed or unsigned 8-bit integer, used only in arrays and tuples
			TYPE_BYTE,
				/// Signed or unsigned 8/16/32/64-bit integer.
			TYPE_INT,
				/// 32-bit float.
			TYPE_REAL,
				/// Fixed array of 4 TYPE_REAL (e.g., hkVector, hkQuaternion).
			TYPE_VEC_4,
				/// Fixed array of 8 TYPE_REAL.
			TYPE_VEC_8,
				/// Fixed array of 12 TYPE_REAL (e.g., hkMatrix3, hkQsTransform, hkRotation).
			TYPE_VEC_12,
				/// Fixed array of 16 TYPE_REAL (e.g., hkTransform, hkMatrix4).
			TYPE_VEC_16,
				/// hkDataObject.
			TYPE_OBJECT,
				/// hkDataObject (embedded struct data).
			TYPE_STRUCT,
				/// C-style string.
			TYPE_CSTRING,
				/// The number of basic hkDataObject types.
			TYPE_NUM_BASIC_TYPES,
				/// Mask for the basic hkDataObject types.
			TYPE_MASK_BASIC_TYPES = 0xf,

				/// Bit indicating an array of the basic type data.
			TYPE_ARRAY = 0x10, // per object size array
				/// Array of TYPE_BYTE.
			TYPE_ARRAY_BYTE = TYPE_ARRAY | TYPE_BYTE,
				/// Array of TYPE_INT.
			TYPE_ARRAY_INT = TYPE_ARRAY | TYPE_INT,
				/// Array of TYPE_REAL.
			TYPE_ARRAY_REAL = TYPE_ARRAY | TYPE_REAL,
				/// Array of TYPE_VEC_4.
			TYPE_ARRAY_VEC_4 = TYPE_ARRAY | TYPE_VEC_4,
				/// Array of TYPE_VEC_8.
			TYPE_ARRAY_VEC_8 = TYPE_ARRAY | TYPE_VEC_8,
				/// Array of TYPE_VEC_12.
			TYPE_ARRAY_VEC_12 = TYPE_ARRAY | TYPE_VEC_12,
				/// Array of TYPE_VEC_16.
			TYPE_ARRAY_VEC_16 = TYPE_ARRAY | TYPE_VEC_16,
				/// Array of TYPE_OBJECT.
			TYPE_ARRAY_OBJECT = TYPE_ARRAY | TYPE_OBJECT,
				/// Array of TYPE_STRUCT.
			TYPE_ARRAY_STRUCT = TYPE_ARRAY | TYPE_STRUCT,
				/// Array of TYPE_CSTRING.
			TYPE_ARRAY_CSTRING = TYPE_ARRAY | TYPE_CSTRING,

				/// Bit indicating a tuple of the basic type data.
			TYPE_TUPLE = 0x20, // fixed size array, size is per class
				/// Tuple of TYPE_BYTE.
			TYPE_TUPLE_BYTE = TYPE_TUPLE | TYPE_BYTE,
				/// Tuple of TYPE_INT.
			TYPE_TUPLE_INT = TYPE_TUPLE | TYPE_INT,
				/// Tuple of TYPE_REAL.
			TYPE_TUPLE_REAL = TYPE_TUPLE | TYPE_REAL,
				/// Tuple of TYPE_VEC_4.
			TYPE_TUPLE_VEC_4 = TYPE_TUPLE | TYPE_VEC_4,
				/// Tuple of TYPE_VEC_8.
			TYPE_TUPLE_VEC_8 = TYPE_TUPLE | TYPE_VEC_8,
				/// Tuple of TYPE_VEC_12.
			TYPE_TUPLE_VEC_12 = TYPE_TUPLE | TYPE_VEC_12,
				/// Tuple of TYPE_VEC_16.
			TYPE_TUPLE_VEC_16 = TYPE_TUPLE | TYPE_VEC_16,
				/// Tuple of TYPE_OBJECT.
			TYPE_TUPLE_OBJECT = TYPE_TUPLE | TYPE_OBJECT,
				/// Tuple of TYPE_STRUCT.
			TYPE_TUPLE_STRUCT = TYPE_TUPLE | TYPE_STRUCT,
				/// Tuple of TYPE_CSTRING.
			TYPE_TUPLE_CSTRING = TYPE_TUPLE | TYPE_CSTRING,
		};
};


class hkTypeManager : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SERIALIZE);
		
		/* Vec sizes can just be encoded as tuples. Vec4 is typle4 real. */
		/* Structs/Objects from old set up. Object is a pointer to a object, struct is just an object */

		enum SubType
		{
			SUB_TYPE_INVALID,			///< Invalid type
			SUB_TYPE_VOID,				///< 
			SUB_TYPE_BYTE,
			SUB_TYPE_REAL,					
			SUB_TYPE_INT ,					
			SUB_TYPE_CSTRING,			///< C style string 
			//SUB_TYPE_VARIANT,			///< hkVariant
			SUB_TYPE_CLASS,				///< A class (followed by class name, and terminated by ;)
			SUB_TYPE_POINTER,			///< Pointer to 
			SUB_TYPE_ARRAY,				///< Has a dynamic size
			SUB_TYPE_TUPLE,				///< Has a fixed size (followed by the size as an int and enclosed by a ]
			SUB_TYPE_COUNT_OF,
		};

		struct Type
		{
			friend class hkTypeManager;
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SERIALIZE, Type);

				/// Return true if this is a class
			HK_FORCE_INLINE hkBool isClass() const { return m_subType == SUB_TYPE_CLASS; }
				/// Return true if this is a tuple
			HK_FORCE_INLINE hkBool isTuple() const { return m_subType == SUB_TYPE_TUPLE; }
				/// Return true if this is a vec (every vec is a tuple, but not every tuple is a vec)
			HK_FORCE_INLINE hkBool isVec() const
				{ 
					return ( isTuple() &&
					         m_parent->isReal() &&
					         ( m_extra.m_size == 4 ||
					           m_extra.m_size == 8 ||
				               m_extra.m_size == 12 ||
				               m_extra.m_size == 16 ) );
				}
				/// Return true if it's an array
			HK_FORCE_INLINE hkBool isArray() const { return m_subType == SUB_TYPE_ARRAY; }
				/// True if type is void
			HK_FORCE_INLINE hkBool isVoid() const { return m_subType == SUB_TYPE_VOID; }
				/// True if it's a pointer
			HK_FORCE_INLINE hkBool isPointer() const { return m_subType == SUB_TYPE_POINTER; }
				/// True if an int
			HK_FORCE_INLINE hkBool isInt() const { return m_subType == SUB_TYPE_INT; }
				/// True if a byte
			HK_FORCE_INLINE hkBool isByte() const { return m_subType == SUB_TYPE_BYTE; }
				/// True if it's a real
			HK_FORCE_INLINE hkBool isReal() const { return m_subType == SUB_TYPE_REAL; }
				/// True if Cstring
			HK_FORCE_INLINE hkBool isCstring() const { return m_subType == SUB_TYPE_CSTRING; }
				/// Returns true if it's the class with name specified
			hkBool isClass(char* name) const { return isClass() && hkString::strCmp(getTypeName(), name) == 0; }
				/// Returns true if it's a class pointer
			HK_FORCE_INLINE hkBool isClassPointer() const { return isPointer() && getParent()->isClass(); }

				/// Returns true if a type is valid
			HK_FORCE_INLINE hkBool isValid() const { return m_subType != SUB_TYPE_INVALID; }
				/// True if terminal
			HK_FORCE_INLINE hkBool isTerminal() const { return m_parent == HK_NULL; }
				/// Find the terminal
			Type* findTerminal();
				/// Get the parent
			HK_FORCE_INLINE Type* getParent() const { return m_parent; }
				/// If this is a tuple it returns the size otherwise returns -1.
			int getTupleSize() const;
				/// Get the type name. Returns an HK_NULL if type doesn't support name.
			const char* getTypeName() const;
				/// Get the type
			HK_FORCE_INLINE SubType getSubType() const { return m_subType; }
				/// Calculate hash
			hkUint32 calcHash() const;
				/// Write as text out to stream
			void asText(hkOstream& stream) const;
				/// As text
			hkStringPtr asString() const;

				/// Returns if equal even if the other type is from another world
			hkBool isEqual(const Type* type) const;

				/// Write type out as text
			static void HK_CALL asText(const Type* type, hkOstream& stream);

				/// Gets the whole type path, from type - to the root
			static void HK_CALL getTypePath(Type* type, hkArray<Type*>& types);

			protected:
			static hkUint32 HK_CALL _calcHash(const Type* type);
			/// Returns true if equal (normally a pointer comparison works, but this will test equality, assuming 
			/// parents can match). Only works with types created on this manager.
			hkBool _equals(const Type& rhs) const;
			/// Determines if two types are the same even if they belong to different managers
			static hkBool HK_CALL _isEqual(const Type* a, const Type* b);


			SubType m_subType;			///< The sub type
			Type* m_parent;				///< The parent to this (HK_NULL if terminal)
			union
			{
				const char* m_name;
				int m_size;
			} m_extra;
		};

			/// Add a terminal type
		Type* addClass(const char* clsName);
			/// Rename a class type
		void renameClass(const char* clsName, const char* newName);
			/// Find all of the types using the class (including the class itself)
		void findTypesUsingClass(Type* clsType, hkArray<Type*>& types);
			/// Remove a class type
		void removeClass(Type* clsType);
			/// Add a class
		Type* getClass(const char* clsName) const;

			/// Returns true if the type is owned by this manager
		hkBool isOwned(Type* type) const;

			/// Creates a copy of the type (which is potentially owned by a different manager)
		Type* copyType(Type* type);

			/// Takes a type, and changes the terminal class type
		Type* replaceClass(Type* type, const char* name);

			/// Homogenous class has no name (it's to represent types that are dynamically classed when loaded)
		Type* getHomogenousClass() const { return m_homogenousClass; }

			/// Any types that were invalidated (say by destroying a class), are not removed but become invalidated.
			/// This is helpful because it means there aren't dangling pointers, but it does waste memory.
			/// Calling this method will cause any invalidated types to be removed.
		void garbageCollect();

			/// Get void
		Type* getVoid() const { return m_builtInTypes[SUB_TYPE_VOID]; }
			/// Get byte
		Type* getByte() const { return m_builtInTypes[SUB_TYPE_BYTE]; }
			/// Get real type
		Type* getReal() const { return m_builtInTypes[SUB_TYPE_REAL]; }
			/// Get Cstring type
		Type* getCstringType() const { return m_builtInTypes[SUB_TYPE_CSTRING]; }
			/// Get the int type
		Type* getIntType() const { return m_builtInTypes[SUB_TYPE_INT]; }

			/// Get a builtin/basic type (returns HK_NULL if not possible)
		Type* getSubType(SubType type) const { return m_builtInTypes[type]; }

			/// Make a pointer to the type
		Type* makePointer(Type* type);
			/// Make an array of the type
		Type* makeArray(Type* type);
			/// Make a tuple of the type. Tuple is like an array - just of a fixed size.
		Type* makeTuple(Type* type, int tupleSize);

			/// Makes built in array	
		Type* makeArray(SubType subType);

			/// Get a pointer to a class
		Type* getClassPointer(const char* name);

			/// Returns a type which has some properties of typeIn, but with the parent passed in.
			/// To be meaningful typeIn cannot be a terminal (as terminals don't have parents!)
		Type* replaceParent(Type* typeIn, Type* parent);

			/// Takes a type and replaces the terminal type with newTerminal
		Type* replaceTerminal(Type* typeIn, Type* newTerminal);

			/// Parse a type
		Type* parseTypeExpression(const char* typeExpression);
			/// Append type expression
		static void HK_CALL appendTypeExpression(const Type* type, hkOstream& stream);

			/// Get a type from a legacy type
		Type* getType(hkLegacyType::Type type, const char* className, int numTupleSize);

			/// Return a legacy type only for 'terminal' types (ones which don't need tuple/array modifiers). Returns the class name 
			/// if there is one in classNameOut, or HK_NULL if none
		static hkLegacyType::Type HK_CALL getTerminalLegacyType(Type* type, const char** classNameOut);
			/// Return type as legacy type
		static hkLegacyType::Type HK_CALL getLegacyType(Type* type, const char** className, int& numTupleOut);

			/// Ctor
		hkTypeManager();
			/// Dtor
		~hkTypeManager();

	public:
		Type* _addBuiltIn(SubType subType) ;
		Type* _addType(const Type& type);
		static hkBool HK_CALL _isValidClassName(const char* name);
		static hkSubString HK_CALL _findClass(const char* expr);

		Type* m_homogenousClass;
		Type* m_builtInTypes[SUB_TYPE_COUNT_OF];

			/// Maps a class name to a type
		hkStorageStringMap<Type*> m_classMap;
			/// Maps a type hash to types
		hkPointerMultiMap<hkUint32, Type*> m_typeMultiMap;

		hkFreeList m_typeFreeList;
};


#endif // LOADER_H

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
