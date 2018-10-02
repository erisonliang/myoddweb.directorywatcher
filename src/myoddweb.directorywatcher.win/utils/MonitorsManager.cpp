#include "MonitorsManager.h"
#include "Lock.h"
#include "../monitors/MonitorReadDirectoryChanges.h"

MonitorsManager* MonitorsManager::_instance = nullptr;
std::recursive_mutex MonitorsManager::_lock;

MonitorsManager::MonitorsManager()
{
  // initialize random seed:
  // The downcast (and potential data loss) doesn't matter 
  // since we're only using it to seed the RNG
  srand( static_cast<unsigned int>(time(nullptr)));
}

MonitorsManager::~MonitorsManager()
{
}

MonitorsManager* MonitorsManager::Instance()
{
  if( nullptr != _instance )
  {
    return _instance;
  }

  // lock
  auto guard = Lock(_lock);

  // check again
  if (nullptr != _instance)
  {
    return _instance;
  }

  // create a new instance
  _instance = new MonitorsManager();

  // return the instance.
  return _instance;
}

/**
 * Start a monitor
 */
__int64 MonitorsManager::Start(const wchar_t* path, bool recursive)
{
  const auto monitor = Instance()->CreateAndStart( path, recursive );
  return monitor->Id();
}

bool MonitorsManager::Stop(__int64 id)
{
  auto guard = Lock(_lock);

  // if we do not have an instance... then we have nothing.
  if( _instance == nullptr )
  {
    return false;
  }

  // try and remove it.
  auto result = Instance()->Remove(id);

  // delete our instance if we are the last one
  if( Instance()->_monitors.empty() )
  {
    delete _instance;
    _instance = nullptr;
  }
  return result;
}

/**
 * Try and get an usued id
 */
__int64 MonitorsManager::GetId() const
{
  return (static_cast<__int64>(rand()) << (sizeof(int) * 8)) | rand();
}

/***
 * Create a monitor instance and add it to the list.
 * Return the value.
 */
Monitor* MonitorsManager::CreateAndStart( const std::wstring& path, bool recursive )
{
  auto guard = Lock(_lock);

  for (;;)
  {
    auto id = GetId();
    if (_monitors.find(id) != _monitors.end())
    {
      // get another id.
      continue;
    }

    //const auto monitor = new Monitor( id );
    const auto monitor = new MonitorReadDirectoryChanges(id, path, recursive );

    monitor->Start();

    _monitors[monitor->Id()] = monitor;
    return monitor;
  }
}

/**
 * Stop and remove a monitor
 */
bool MonitorsManager::Remove(__int64 id)
{
  try
  {
    auto guard = Lock(_lock);
    const auto monitor = _monitors.find(id);
    if (monitor == _monitors.end())
    {
      // does not exist.
      return false;
    }

    // stop everything
    monitor->second->Stop();

    // delete it
    delete monitor->second;

    // remove it
    _monitors.erase(monitor);

    // we are done
    return true;
  }
  catch(...)
  {
    return false;
  }
}