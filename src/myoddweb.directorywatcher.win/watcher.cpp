//This file is part of Myoddweb.Directorywatcher.
//
//    Myoddweb.Directorywatcher is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Myoddweb.Directorywatcher is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Myoddweb.Directorywatcher.  If not, see<https://www.gnu.org/licenses/gpl-3.0.en.html>.
#include "stdafx.h"
#include "watcher.h"
#include "utils/MonitorsManager.h"

namespace myoddweb
{
  namespace directorywatcher
  {
    /**
     * \brief start a monitor and return a unique id to make sure we can stop it.
     * \param request the request.
     * \return __int64 the unique id.
     */
    __int64 Start(const Request request)
    {
      return MonitorsManager::Start(request);
    }

    /**
     * \brief start a monitor and return a unique id to make sure we can stop it.
     * \param id the id we want to stop monitoring.
     * \return bool success or not.
     */
    bool Stop(const __int64 id )
    {
      return MonitorsManager::Stop(id);
    }
  }
}