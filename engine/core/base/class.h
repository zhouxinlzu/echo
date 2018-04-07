#pragma once

#include "object.h"
#include "variant.h"
#include "engine/core/Util/StringUtil.h"
#include "engine/core/script/lua/luaex.h"

namespace Echo
{
	struct PropertyInfo
	{
		String			m_name;
		Variant::Type	m_type;
		void*			m_getter;
		String			m_setter;
	};
	typedef vector<PropertyInfo>::type PropertyInfos;

	struct ClassInfo
	{
		String			m_parent;
		PropertyInfos	m_propertyInfos;
	};

	struct ObjectFactory
	{
		String		m_name;
		ClassInfo	m_classInfo;

		virtual Object* create() = 0;

		// register property
		void registerProperty(const PropertyInfo& property)
		{
			m_classInfo.m_propertyInfos.push_back(property);
		}

		// get propertys
		const PropertyInfos& getPropertys()
		{
			return m_classInfo.m_propertyInfos;
		}

		// get property value
		virtual const String& getPropertyValue(const Object* classPtr, const String& propertyName) = 0;
	};

	template<typename T>
	struct ObjectFactoryT : public ObjectFactory
	{
		ObjectFactoryT(const String& name, const String& parent)
		{
			// register class to lua
			luaex::LuaEx::instance()->register_class(name.c_str(), parent.c_str());

			m_name = name;
			m_classInfo.m_parent = parent;

			Class::addClass(name, this);
			T::bindMethods();
		}

		virtual Object* create()
		{
			return EchoNew(T);
		}

		// get property value
		virtual const String& getPropertyValue(const Object* classPtr, const String& propertyName)
		{
			const T* realClassPtr = dynamic_cast<const T*>(classPtr);

			int a = 10;

			static String invalid = "";
			return invalid;
		}
	};

	class Class
	{
	public:
		template<typename T>
		static void registerType()
		{
			T::initClassInfo();
		}

		template<typename T>
		static T create(const char* className)
		{
			Object* obj = create(className);
			if (obj)
			{
				return ECHO_DOWN_CAST<T>(obj);
			}

			return nullptr;
		}

		static Object* create(const char* className);

		// add class
		static void addClass(const String& className, ObjectFactory* objFactory);

		// get parent class name
		static bool getParentClass(String& parentClassName, const String& className);

		// get all child class
		static bool getChildClasses(StringArray& childClasses, const String& className);

		// add property
		static bool registerProperty(const String& className, const String& propertyName, const Variant::Type type, void* getter, const String& setter);

		// get propertys
		static const PropertyInfos& getPropertys(const String& className);

		// get property value
		static const String& getPropertyValue(const Object* classPtr, const String& propertyName);

		// set property value
		static bool setPropertyValue(const Object* classPtr, const String& className, const String& propertyValue);
	};
}

#define ECHO_CLASS(m_class, m_parent)												\
public:																				\
	virtual const String& getClassName() const										\
	{																				\
		static String className=#m_class;											\
		return className;															\
	}																				\
																					\
	static void initClassInfo()														\
	{																				\
		static Echo::ObjectFactoryT<m_class> G_OBJECT_FACTORY(#m_class, #m_parent);	\
	}																				\
																					\
private:															

#define CLASS_REGISTER_PROPERTY(m_class, name, type, getter, setter) \
	Echo::Class::registerProperty(#m_class, name, type, getter, setter)