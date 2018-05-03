/*
    Clock Synchronization Simulation in OMNet++
    Copyright (C) 2012 Jens Steinhauser

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#pragma once

//#include "hardwareclock.h"
#include <omnetpp.h>

namespace smile {
namespace steinhauser_clock {

class SteinhauserClock;

/// \brief Base class for classes that want to schedule events at hardware time.
class HardwareClockClient : public omnetpp::cSimpleModule
{
  /// Hardware clock to use in 'scheduleAtHWtime()'.
  SteinhauserClock* _clock;

  /// Calls 'scheduleAt' in the context of the HardwareClockClient object
  /// (calls Enter_Method_Silent()).
  ///
  /// \param realtime	The simulation time when to schedule the message.
  /// \param msg	The message to schedule. The ownership of the message is
  /// 		take()n in the function.
  void scheduleAtInObject(const omnetpp::simtime_t realtime, omnetpp::cMessage* msg);

 protected:
  /// Sets the hardware clock to use in 'scheduleAtHWtime()'.
  void setHardwareClock(SteinhauserClock* clock);

 public:
  /// Schedules a message at hardware time.
  ///
  /// The hardware clock whose time is used has to be set with
  /// 'setHardwareClock()' prior to calling this function.
  /// Because the message is scheduled internally through the
  /// objects 'scheduleAt' function, it's really a self message
  /// (and msg->isSelfMessage() can be used).
  ///
  /// \param hwtime	The hardware time when to schedule the message.
  /// \param msg	The message to schedule.
  void scheduleAtHWtime(const omnetpp::simtime_t& hwtime, omnetpp::cMessage* msg);

  omnetpp::simtime_t getHWtime() const;

  HardwareClockClient();

  // needs access to 'scheduleAtInObject'
  friend class SteinhauserClock;
};

}  // namespace steinhauser_clock
}  // namespace smile
