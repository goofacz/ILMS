//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#pragma once

#include "inet/physicallayer/contract/packetlevel/IRadio.h"
#include "omnetpp.h"

namespace smile {

class IApplication
{
 public:
  IApplication(const IApplication& source) = delete;
  IApplication(IApplication&& source) = delete;
  virtual ~IApplication() = default;

  IApplication& operator=(const IApplication& source) = delete;
  IApplication& operator=(IApplication&& source) = delete;

  virtual void handleTxStateChanged(inet::physicallayer::IRadio::TransmissionState state) = 0;

  virtual void handleRxStateChanged(inet::physicallayer::IRadio::ReceptionState state) = 0;

 protected:
  IApplication() = default;
};

}  // namespace smile
