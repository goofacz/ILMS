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

#include <inet/linklayer/ideal/IdealMacFrame_m.h>
#include <inet/physicallayer/contract/packetlevel/IRadio.h>
#include <omnetpp.h>
#include "ClockDecorator.h"
#include "IRangingNicDriver.h"
#include "IdealRxCompletion_m.h"
#include "IdealTxCompletion_m.h"

namespace smile {

class IdealRangingNicDriver : public ClockDecorator<omnetpp::cSimpleModule>, public IRangingNicDriver
{
 public:
  IdealRangingNicDriver() = default;
  IdealRangingNicDriver(const IdealRangingNicDriver& source) = delete;
  IdealRangingNicDriver(IdealRangingNicDriver&& source) = delete;
  ~IdealRangingNicDriver() = default;

  IdealRangingNicDriver& operator=(const IdealRangingNicDriver& source) = delete;
  IdealRangingNicDriver& operator=(IdealRangingNicDriver&& source) = delete;

  inet::MACAddress getMacAddress() const override;

 protected:
  using ClockDecorator<omnetpp::cSimpleModule>::receiveSignal;

 private:
  void initialize(int stage) override final;

  void handleIncommingMessage(omnetpp::cMessage* newMessage) override final;

  void receiveSignal(omnetpp::cComponent* source, omnetpp::simsignal_t signalID, long value,
                     omnetpp::cObject* details) override final;

  void handleApplicationIn(std::unique_ptr<inet::IdealMacFrame> frame);

  void handleNicIn(std::unique_ptr<inet::IdealMacFrame> frame);

  void handleRadioStateChanged(inet::physicallayer::IRadio::TransmissionState newState);

  void handleRadioStateChanged(inet::physicallayer::IRadio::ReceptionState newState);

  void clearRxCompletion();

  void clearTxCompletion();

  IdealTxCompletion txCompletion;
  IdealRxCompletion rxCompletion;
  std::unique_ptr<inet::IdealMacFrame> txFrame;
  std::unique_ptr<inet::IdealMacFrame> rxFrame;
  inet::physicallayer::IRadio* radio{nullptr};
  cModule* nic{nullptr};
  cModule* mac{nullptr};
};

}  // namespace smile
