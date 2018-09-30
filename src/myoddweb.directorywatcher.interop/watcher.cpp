// myoddweb.directorywatcher.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "watcher.h"
#include "Importer.h"

namespace myoddweb
{
  namespace directorywatcher
  {
    namespace Interop
    {
      Watcher::Watcher() : _coreWatcher( nullptr )
      {
        _coreWatcher = (CoreWatcher*)Importer(IID_IWatcher1);
      }

      Watcher::~Watcher()
      {
        this->!Watcher();
      }

      Watcher::!Watcher()
      {
        delete _coreWatcher;
      }
    }
  }
}