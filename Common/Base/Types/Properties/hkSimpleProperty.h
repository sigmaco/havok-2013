/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_PROPERTY_H
#define HK_PROPERTY_H

extern const hkClass hkSimplePropertyValueClass;
extern const hkClass hkSimplePropertyClass;

/// A union of an int and a hkReal, used for the value field of a property
/// Note: pointers will not be serialized properly, to store pointers use hkRefCountedProperties
struct hkSimplePropertyValue
{
	//+version(1)

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkSimplePropertyValue );
	HK_DECLARE_REFLECTION();

	hkUint64 m_data;

	inline hkSimplePropertyValue( const int i );
	inline hkSimplePropertyValue( const hkUint32 i);
	inline hkSimplePropertyValue( const hkReal f );
	inline hkSimplePropertyValue( void* p );
	inline hkSimplePropertyValue( hkUint64 i );
	inline hkSimplePropertyValue( ) { }

	inline void setReal(const hkReal r);
	inline void setInt(const int i);
	inline void setPtr(void* p);
	inline void setUint64(hkUint64 i);

	inline hkReal getReal() const;
	inline int getInt() const;
	inline void* getPtr() const;
	inline hkUint64 getUint64() const;
};

/// A generic propery. An hkSimpleProperty has a type and a value.
/// You can use properties to add additional information to an entity - for instance,
/// for using your own collision filters or flagging certain types of game objects.
/// Note: pointers will not be serialized properly, to store pointers use hkRefCountedProperties
class hkSimpleProperty
{
	//+version(2)

	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkSimpleProperty );
		HK_DECLARE_REFLECTION();

	public:
			/// Default constructor - does nothing
		inline hkSimpleProperty();

			/// Create a property with a key and a hkUint32 value
		inline hkSimpleProperty( hkUint32 key, hkInt32 value );

			/// Create a property with a key and value
		inline hkSimpleProperty( hkUint32 key, hkSimplePropertyValue value );

	public:

			///The property key.
		hkUint32 m_key;

			// Ensure m_value starts at 8 byte offset.
		hkUint32 m_alignmentPadding;	//+nosave

			///The property's value.
		struct hkSimplePropertyValue m_value;

	public:

		hkSimpleProperty( class hkFinishLoadedObjectFlag flag ) { }

	public:

			/// The hash function that converts strings to property keys.
		static void HK_CALL mapStringToKey( const char* string, hkUint32& keyOut );

};

#include <Common/Base/Types/Properties/hkSimpleProperty.inl>

/// Properties between these values are used by Havok demos and sample code.
#define HK_HAVOK_PROPERTIES_START 0x1000
#define HK_HAVOK_PROPERTIES_END 0x2000

// Here is a list of all the properties currently used by the demos and sample code.

// Multiple Worlds
#define HK_PROPERTY_ENTITY_REP_PHANTOM 0x1111

// graphics bridge
#define HK_PROPERTY_DEBUG_DISPLAY_COLOR 0x1130

// the geometry which overrides the default shape view.
// Once the graphics engine has created the object,
// the geometry is deleted and the property removed
#define HK_PROPERTY_OVERRIDE_DEBUG_DISPLAY_GEOMETRY 0x1131

// The volume of a rigid body. This is only used by the fracture demo
#define HK_PROPERTY_RIGID_BODY_VOLUME 0x1132

// The isFracturable property. Attached to bodies which are meant to be fractured.
// This is only used by the fracture demo.
#define HK_PROPERTY_RIGID_BODY_IS_FRACTURABLE 0x1133

// the id used for the graphics bridge. If this property is not preset, the address
// of the collidable will used as an id
#define HK_PROPERTY_DEBUG_DISPLAY_ID 0x1134

// Pointer to a shape which is used by the graphics engine to create a separate display geometry.
// If this pointer is HK_NULL, no graphics shape is created for the Havok demo renderer, however
// the visual debugger will get the original graphics shape.
// This property is cleared and reference to the shape removed upon addition of the body to hkWorld.
#define HK_PROPERTY_DISPLAY_SHAPE 0x1135

// Sames as the normal HK_PROPERTY_OVERRIDE_DEBUG_DISPLAY_GEOMETRY
// except the prop is left in the entity and the geom is not deleted (helps sharing etc)
#define HK_PROPERTY_OVERRIDE_DEBUG_DISPLAY_GEOMETRY_NO_DELETE 0x1136

// If set, this rigid body is used by another object only as a reference object and should be removed from the final physics system
#define HK_PROPERTY_PHYSICS_IS_ONLY_CREATED_AS_A_REFERENCE_OBJECT 0x1137

// Half Stepping Utility
#define HK_PROPERTY_HALF_STEPPER_INDEX 0x1200

// Shape for Local viewer, VDB / external viewers not affected
#define HK_PROPERTY_DISPLAY_PTR 0x1234 

// Shape for the VDB and local viewers, this will affect all viewers
#define HK_PROPERTY_VDB_DISPLAY_PTR 0x1235

// Used to give a body a hash which overrides the one calculated for the shape. (Hashes are used by
// the VDB cache.)
#define HK_PROPERTY_OVERRIDE_SHAPE_HASH 0x1236

// Character controller
#define HK_PROPERTY_CHARACTER_PROXY 0x1300

// Trigger volume
#define HK_PROPERTY_TRIGGER_VOLUME 0x1310

// A pointer to an hkbCharacter used by hkbehavior demos
#define HK_PROPERTY_HKB_CHARACTER 0x1400

// Stored motion type used in Behavior Physics Bridges
#define HK_PROPERTY_STORED_QUALITY_INFO 0x1401

// Stored quality type used in Behavior Physics Bridges
#define HK_PROPERTY_STORED_MOTION_INFO 0x1402

#define HK_PROPERTY_EPHYSICS_BODY 0x1500

#endif // HK_PROPERTY_H

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
