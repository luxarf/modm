/*
 * Copyright (c) 2020, Philipp Graf
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#include <modm/board.hpp>
#include <modm/platform.hpp>

int
main() {
  // initialize board
  Board::initialize();
  Board::LedD13::setOutput();

  // define the memory the dma should iterate over
  std::array<uint16_t, 10> srcAr = {
    0, 1000, 2000, 3000, 4000,
    5000, 6000, 7000, 8000, 9000
  };

  // initialize the dma
  using dma1 = modm::platform::DmaController<1>;
  dma1::enable();
  using dmaHal = modm::platform::DmaHal<1>;
  using channel5 = modm::platform::DmaChannelHal<dmaHal::Channel::Channel5, dmaHal::CHANNEL_BASE>;
  channel5::configure(dmaHal::DataTransferDirection::MemoryToPeripheral,
      dmaHal::MemoryDataSize::Bit16,
      dmaHal::PeripheralDataSize::Bit16,
      dmaHal::MemoryIncrementMode::Increment,
      dmaHal::PeripheralIncrementMode::Fixed,
      dmaHal::Priority::Medium,
      dmaHal::CircularMode::Enabled);
  channel5::setMemoryAddress(srcAr.data());
  channel5::setDataLength(srcAr.size());

  // initialize the timer
  // connect timer and dma
  while (true) {
  }

  return 0;
}
