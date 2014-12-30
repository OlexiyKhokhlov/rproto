//-------------------------------------------------------------------
//  Base Objects for Service Solutions (BOSS)
//  www.t-boss.ru
//
//  Created:     01.03.2014
//  mail:        boss@t-boss.ru
//
//  Copyright (C) 2014 t-Boss 
//-------------------------------------------------------------------

#ifndef __BOSS_PLUGIN_MODULE_H__
#define __BOSS_PLUGIN_MODULE_H__

#include "co_class_set.h"
#include "factory_tools.h"
#include "../core/module.h"
#include "../common/iservice_locator.h"

namespace Boss
{

  namespace Private
  {

    namespace
    {

      RefObjPtr<IServiceLocator>& GetServiceLocatorHolder()
      {
        static RefObjPtr<IServiceLocator> Ret;
        return Ret;
      }
      
    }
    
    RefObjPtr<IServiceLocator> GetServiceLocator()
    {
      return GetServiceLocatorHolder();
    }
    
    void SetServiceLocator(IServiceLocator *locator)
    {
      GetServiceLocatorHolder() = locator;
    }

  }

}

#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_DLL
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllexport))
    #else
      #define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllimport))
    #else
      #define DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define DLL_PUBLIC __attribute__ ((visibility ("default")))
    #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define DLL_PUBLIC
    #define DLL_LOCAL
  #endif
#endif

#ifdef __GNUC__
  #define BOSS_PLUGIN_EXPORT extern "C" DLL_PUBLIC
#elif _MSC_VER
  #define BOSS_PLUGIN_EXPORT extern "C" __declspec(dllexport)
#else
  #error BOSS_PLUGIN_EXPORT not implemented
#endif

#define BOSS_DECLARE_MODULE_ENTRY_POINT(service_id_, exported_co_classes_) \
  namespace Boss \
  { \
    namespace Private \
    { \
      typedef exported_co_classes_ ModuleExportedCoClasses; \
    } \
  } \
  BOSS_PLUGIN_EXPORT \
  Boss::RetCode BossGetServiceLocator(Boss::IServiceLocator **locator) \
  { \
    if (!locator || *locator) \
      return Boss::Status::InvalidArgument; \
    try \
    { \
      return !(*locator = Boss::Private::GetServiceLocator().Get()) ? \
        Boss::Status::NotFound : Boss::Status::Ok; \
    } \
    catch (std::exception const &) \
    { \
    } \
    return Boss::Status::Fail; \
  } \
  BOSS_PLUGIN_EXPORT \
  Boss::RetCode BossSetServiceLocator(Boss::IServiceLocator *locator) \
  { \
    try \
    { \
      Boss::Private::SetServiceLocator(locator); \
      return Boss::Status::Ok; \
    } \
    catch (std::exception const &) \
    { \
    } \
    return Boss::Status::Fail; \
  } \
  BOSS_PLUGIN_EXPORT \
  Boss::RetCode BossGetServiceId(Boss::ServiceId *serviceId) \
  { \
    if (!serviceId) \
      return Boss::Status::InvalidArgument; \
    *serviceId = Boss::Crc32(service_id_, sizeof(service_id_) - 1); \
    return Boss::Status::Ok; \
  } \
  BOSS_PLUGIN_EXPORT \
  Boss::RetCode BossCreateObject(Boss::ClassId clsId, Boss::IBase **inst) \
  { \
    if (!inst) \
      return Boss::Status::InvalidArgument; \
    try \
    { \
      return Boss::CoClassSet<Boss::Private::ModuleExportedCoClasses>::CreateObject(clsId).QueryInterface(inst); \
    } \
    catch (std::exception const &) \
    { \
      return Boss::Status::Fail; \
    } \
    return Boss::Status::Fail; \
  } \
  BOSS_PLUGIN_EXPORT \
  Boss::RetCode BossGetClassCount(Boss::UInt *count) \
  { \
    if (!count) \
      return Boss::Status::InvalidArgument; \
    try \
    { \
      *count = Boss::CoClassSet<Boss::Private::ModuleExportedCoClasses>::GetClassCount(); \
    } \
    catch (std::exception const &) \
    { \
      return Boss::Status::Fail; \
    } \
    return Boss::Status::Ok; \
  } \
  BOSS_PLUGIN_EXPORT \
  Boss::RetCode BossGetClassId(Boss::UInt index, Boss::ClassId *clsId) \
  { \
    if (!clsId) \
      return Boss::Status::InvalidArgument; \
    try \
    { \
      *clsId = Boss::CoClassSet<Boss::Private::ModuleExportedCoClasses>::GetId(index); \
    } \
    catch (std::exception const &) \
    { \
      return Boss::Status::Fail; \
    } \
    return Boss::Status::Ok; \
  } \
  BOSS_PLUGIN_EXPORT \
  Boss::RetCode BossGetRefCount(Boss::UInt *refs) \
  { \
    if (!refs) \
      return Boss::Status::InvalidArgument; \
    try \
    { \
      *refs = Boss::Private::ModuleCounterImpl::GetCounter(); \
    } \
    catch (std::exception const &) \
    { \
      return Boss::Status::Fail; \
    } \
    return Boss::Status::Ok; \
  }

#endif  // !__BOSS_PLUGIN_MODULE_H__
