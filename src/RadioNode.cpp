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

#include "inet/common/INETDefs.h"
#include "inet/physicallayer/common/packetlevel/Radio.h"
#include "inet/linklayer/base/MACProtocolBase.h"

#include "RadioNode.h"

namespace smile {

Define_Module(RadioNode);

inet::MACAddress RadioNode::getMACAddress() const
{
  const auto mac = check_and_cast<inet::MACProtocolBase*>(getModuleByPath(".nic.mac"));
  const auto& address = mac->par("address");
  return inet::MACAddress(address.stringValue());
}

const inet::Coord& RadioNode::getCurrentPosition() const
{
  return currentPosition;
}

void RadioNode::initialize(int stage)
{
  cModule::initialize(stage);
  if (stage == inet::INITSTAGE_PHYSICAL_ENVIRONMENT_2) {
    auto radio = check_and_cast<inet::physicallayer::Radio*>(getModuleByPath(".nic.radio"));
    radio->subscribe(inet::physicallayer::Radio::transmissionStateChangedSignal, this);
    radio->subscribe(inet::physicallayer::Radio::receptionStateChangedSignal, this);

    auto mobility = check_and_cast<omnetpp::cComponent*>(getModuleByPath(".mobility"));
    mobility->subscribe(inet::IMobility::mobilityStateChangedSignal, this);

    auto iMobility = check_and_cast<inet::IMobility*>(mobility);
    currentPosition = iMobility->getCurrentPosition();
    EV_DETAIL << "Current position: " << currentPosition << endl;

    iApplication = check_and_cast<IApplication*>(getModuleByPath(".application"));
  }
}

void RadioNode::receiveSignal(omnetpp::cComponent*, omnetpp::simsignal_t signalID, long value, omnetpp::cObject*)
{
  if (signalID == inet::physicallayer::Radio::transmissionStateChangedSignal) {
    iApplication->handleTxStateChanged(static_cast<inet::physicallayer::IRadio::TransmissionState>(value));
  }
  else if (signalID == inet::physicallayer::Radio::receptionStateChangedSignal) {
    iApplication->handleRxStateChanged(static_cast<inet::physicallayer::IRadio::ReceptionState>(value));
  }
}

void RadioNode::receiveSignal(omnetpp::cComponent*, omnetpp::simsignal_t signalID, omnetpp::cObject* value,
                              omnetpp::cObject*)
{
  if (signalID == inet::IMobility::mobilityStateChangedSignal) {
    handleMobilityStateChanged(value);
  }
}

int RadioNode::numInitStages() const
{
  return inet::INITSTAGE_LINK_LAYER_2 + 1;
}

void RadioNode::handleMobilityStateChanged(omnetpp::cObject* value)
{
  auto mobility = check_and_cast<inet::IMobility*>(value);
  assert(mobility);
  currentPosition = mobility->getCurrentPosition();
  EV_DETAIL << "Current position: " << currentPosition << endl;
}

}  // namespace smile
