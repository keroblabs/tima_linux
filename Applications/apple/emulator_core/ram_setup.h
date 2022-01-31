#define IO_SPACE    NULL

static const address_map_t ram_map[] =
{
    memory_map_pg0,  memory_map_pg0,        // 0x0000 - 0x1FF
    
    memory_map_normal, memory_map_normal,   // 0x0200 - 0x3FF
    
    memory_map_lores, memory_map_lores, memory_map_lores, memory_map_lores,         // 0x0400 - 0x07FF
    memory_map_lores2, memory_map_lores2, memory_map_lores2, memory_map_lores2,     // 0x0800 - 0x0BFF
    
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,     // 0x0C00 - 0x1FFF
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    
    memory_map_hires, memory_map_hires, memory_map_hires, memory_map_hires,         // 0x2000 - 0x3FFF
    memory_map_hires, memory_map_hires, memory_map_hires, memory_map_hires,
    memory_map_hires, memory_map_hires, memory_map_hires, memory_map_hires,
    memory_map_hires, memory_map_hires, memory_map_hires, memory_map_hires,
    memory_map_hires, memory_map_hires, memory_map_hires, memory_map_hires,
    memory_map_hires, memory_map_hires, memory_map_hires, memory_map_hires,
    memory_map_hires, memory_map_hires, memory_map_hires, memory_map_hires,
    memory_map_hires, memory_map_hires, memory_map_hires, memory_map_hires,

    memory_map_hires2, memory_map_hires2, memory_map_hires2, memory_map_hires2,     // 0x4000 - 0x5FFF
    memory_map_hires2, memory_map_hires2, memory_map_hires2, memory_map_hires2,
    memory_map_hires2, memory_map_hires2, memory_map_hires2, memory_map_hires2,
    memory_map_hires2, memory_map_hires2, memory_map_hires2, memory_map_hires2,
    memory_map_hires2, memory_map_hires2, memory_map_hires2, memory_map_hires2,
    memory_map_hires2, memory_map_hires2, memory_map_hires2, memory_map_hires2,
    memory_map_hires2, memory_map_hires2, memory_map_hires2, memory_map_hires2,
    memory_map_hires2, memory_map_hires2, memory_map_hires2, memory_map_hires2,

    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,     // 0x6000 - 0xBFFF
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    memory_map_normal, memory_map_normal, memory_map_normal, memory_map_normal,
    
    IO_SPACE,                                                                       // 0xC0xx
                      memory_map_iosel, memory_map_iosel, memory_map_iosel,         // 0xC100 - 0xC7FF
    memory_map_iosel, memory_map_iosel, memory_map_iosel, memory_map_iosel,
    
    memory_map_iostb, memory_map_iostb, memory_map_iostb, memory_map_iostb,         // 0xC800 - 0xCFFF
    memory_map_iostb, memory_map_iostb, memory_map_iostb, memory_map_iostb,
    
    memory_map_rom_0, memory_map_rom_0, memory_map_rom_0, memory_map_rom_0,         // 0xD000 - 0xDFFF
    memory_map_rom_0, memory_map_rom_0, memory_map_rom_0, memory_map_rom_0,
    memory_map_rom_0, memory_map_rom_0, memory_map_rom_0, memory_map_rom_0,
    memory_map_rom_0, memory_map_rom_0, memory_map_rom_0, memory_map_rom_0,
    
    memory_map_rom_1, memory_map_rom_1, memory_map_rom_1, memory_map_rom_1,         // 0xC000 - 0xFFFF
    memory_map_rom_1, memory_map_rom_1, memory_map_rom_1, memory_map_rom_1,
    memory_map_rom_1, memory_map_rom_1, memory_map_rom_1, memory_map_rom_1,
    memory_map_rom_1, memory_map_rom_1, memory_map_rom_1, memory_map_rom_1,
    memory_map_rom_1, memory_map_rom_1, memory_map_rom_1, memory_map_rom_1,
    memory_map_rom_1, memory_map_rom_1, memory_map_rom_1, memory_map_rom_1,
    memory_map_rom_1, memory_map_rom_1, memory_map_rom_1, memory_map_rom_1,
    memory_map_rom_1, memory_map_rom_1, memory_map_rom_1, memory_map_rom_1,
};

