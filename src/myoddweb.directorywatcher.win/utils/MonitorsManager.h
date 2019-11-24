// Licensed to Florent Guelfucci under one or more agreements.
// Florent Guelfucci licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.
#pragma once
#include <mutex>
#include <unordered_map>
#include "Request.h"
#include "Event.h"
#include "../monitors/Monitor.h"
#include "../monitors/Callbacks.h"

namespace myoddweb
{
  namespace directorywatcher
  {
    class MonitorsManager
    {
    protected:
      MonitorsManager();
      virtual ~MonitorsManager();

    public:
      /**
       * \brief Start a monitor
       * \param request the request being added.
       * \param callback the callback we will be using
       * \param callbackRateMs how often we want t callback
       * \return the id of the monitor we started
       */
      static long long Start(const Request& request, EventCallback callback, long long callbackRateMs);

      /**
       * \brief Try and remove a monitror by id
       * \param id the id of the monitor we want to stop
       * \return if we managed to remove it or not.
       */
      static bool Stop(long long id);
      
    protected:
      /**
       * \brief Create a monitor and start monitoring, (given the request).
       * \param request contains the information we need to start the monitoring
       * \param callback the callback when we have events.
       * \param callbackRateMs how often we want t callback
       * \return the class item we created.
       */
      Monitor* CreateAndStart(const Request& request, EventCallback callback, long long callbackRateMs);

      /**
       * \brief Create a monitor and add it to our list.
       * \param request the request we are creating the monitor with
       * \return the created monitor.
       */
      Monitor* CreateAndddToList(const Request& request);

      /**
       * \brief stop a monitor and then get rid of it.
       * \paramn id the id we want to delete.
       * \return false if there was a problem or if it does not exist.
       */
      bool StopAndDelete(long long id);

      /**
       * \brief Get a random id
       * We do not check for colisions, it is up to the caller.
       * \return a random id number.
       */
      static long long GetId();

      // The file lock
      static std::recursive_mutex _lock;

      // the singleton
      static MonitorsManager* _instance;
      static MonitorsManager* Instance();

      typedef std::unordered_map<long long, Monitor*> MonitorMap;
      MonitorMap _monitors;
    };
  }
}