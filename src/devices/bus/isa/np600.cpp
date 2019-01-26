// license:BSD-3-Clause
// copyright-holders:AJR
/*********************************************************************

    InterLan NP600 Intelligent Protocol Processor

*********************************************************************/

#include "emu.h"
#include "np600.h"

#include "cpu/i86/i186.h"
//#include "machine/i82586.h"

DEFINE_DEVICE_TYPE(NP600A3, np600a3_device, "np600a3", "InterLan NP600A-3 Intelligent Protocol Processor")

np600a3_device::np600a3_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock)
	: device_t(mconfig, NP600A3, tag, owner, clock)
	, device_isa16_card_interface(mconfig, *this)
	, m_npcpu(*this, "npcpu")
{
}

void np600a3_device::device_start()
{
}

void np600a3_device::mem_map(address_map &map)
{
	map(0x00000, 0x7ffff).ram(); // GM71256-12 x16
	map(0xfc000, 0xfffff).rom().region("npcpu", 0);
}

void np600a3_device::device_add_mconfig(machine_config &config)
{
	I80186(config, m_npcpu, 16_MHz_XTAL);
	m_npcpu->set_addrmap(AS_PROGRAM, &np600a3_device::mem_map);

	//I82586(config, "enet", 20_MHz_XTAL);
}

ROM_START(np600a3)
	ROM_REGION(0x4000, "npcpu", 0)
	ROM_LOAD16_BYTE("258-0032-00_rev_ba.u38", 0x0000, 0x2000, CRC(84ccb317) SHA1(3ecc8e265336f5d3b0f276f18dd1b7001778f2c3))
	ROM_LOAD16_BYTE("258-0033-00_rev_ba.u39", 0x0001, 0x2000, CRC(0e0f726c) SHA1(520773e235a826438b025381cd3861df86d4965d))

	// Undumped small devices (mostly or all PLDs):
	// 258-0037-00 REV AA (U17, 20 pins)
	// 258-0027-01 REV AB (U20, 20 pins)
	// 020701079BFA (U29, 16 pins)
	// 258-0031-00 REV AC (U34, PAL20xx, 24 pins)
	// 258-0030-00 REV AA (U36, 20 pins)
	// 258-0028-01 REV AA (U44, 20 pins)
	// 258-0029-01 REV AA (U46, 20 pins)
	// 258-0089-00 REV AA (U48, 20 pins)
ROM_END

const tiny_rom_entry *np600a3_device::device_rom_region() const
{
	return ROM_NAME(np600a3);
}
