// myoddweb.directorywatcher.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "watcher.h"

namespace myoddweb
{
  namespace directorywatcher
  {
    namespace Interop
    {
      Watcher::Watcher()
      {
      }

      Watcher::~Watcher()
      {
        this->!Watcher();
      }

      Watcher::!Watcher()
      {
      }
    }
  }
}