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

#include "../smile_features.h"
#ifdef WITH_DECAWEAVE

#include <map>
#include <vector>
#include "../Application.h"
#include "deca_device_api.h"

namespace std {

template <>
struct hash<std::pair<uint8_t, uint16_t>>
{
  std::size_t operator()(const std::pair<uint8_t, uint16_t>& key)
  {
    const uint32_t value = (key.first << 16) | key.second;
    return std::hash<uint32_t>{}(value);
  }
};

}  // namespace std

namespace smile {
namespace decaweave {

extern "C" {

extern int readfromspi(uint16 headerLength, const uint8* headerBuffer, uint32 readlength, uint8* readBuffer);

}  // extern "C"

class Application : public smile::Application
{
  friend int readfromspi(uint16 headerLength, const uint8* headerBuffer, uint32 readlength, uint8* readBuffer);
  friend class CurrentApplicationGuard;

 private:
  enum class Operation
  {
    READ,
    WRITE,
  };

  using RegisterFile = uint8_t;
  using RegisterFileMap = std::map<std::pair<uint8_t, uint8_t>, std::vector<uint8_t>>;

 public:
  Application();
  Application(const Application& source) = delete;
  Application(Application&& source) = delete;
  ~Application() = default;

  Application& operator=(const Application& source) = delete;
  Application& operator=(Application&& source) = delete;

 protected:
  void initialize(int stage) override;

 private:
  static unsigned int generateDecaLibIndex();

  void handleIncommingMessage(cMessage* message) override final;

  int decodeTransaction(uint16_t headerLength, const uint8_t* headerBuffer, uint32_t readlength, uint8_t* readBuffer);

  int readRegisterFile(const std::pair<uint8_t, uint16_t>& registerFileWithSubaddress, uint32_t readlength,
                       uint8_t* readBuffer);

  unsigned int getDecaLibIndex() const;

  const unsigned int decaLibIndex;
  RegisterFileMap registerFiles;
};

}  // namespace decaweave
}  // namespace smile

#endif  // WITH_DECAWEAVE
