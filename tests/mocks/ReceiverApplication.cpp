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

#include <cassert>

#include "ReceiverApplication.h"

namespace smile {
namespace mocks {

Define_Module(ReceiverApplication);

void ReceiverApplication::handleReceptionCompleted(std::unique_ptr<inet::MACFrameBase> frame,
                                                   const omnetpp::SimTime& clockTimestamp)
{
  const auto& sourceAddress = frame->getSrcAddr();
  const auto& destinationAddress = frame->getDestAddr();
  EV_DETAIL << "TEST: Received MAC frame from " << sourceAddress.str() << " addressed to " << destinationAddress.str()
            << endl;
}

}  // namespace mocks
}  // namespace smile
