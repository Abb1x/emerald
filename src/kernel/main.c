#include <arch/arch.h>
#include <arch/cpuid.h>
#include <devices/pit.h>
#include <emerald/debug.h>
#include <emerald/log.h>
#include <emerald/macros.h>
#include <main.h>
#include <devices/apic.h>

void kernel_splash()
{

    log("------------------------------------------------");
    log("   __                     __ __ __                  ");
    log(" |  |--.-----.----.--.--|  |  |__.--.--.--------.  ");
    log(" |  _  |  -__|   _|  |  |  |  |  |  |  |        |  ");
    log(" |_____|_____|__| |___  |__|__|__|_____|__|__|__|  ");
    log("                |_____|");
    log("Compiled on {a} {a}", __DATE__, __TIME__);
    log("Using x86_64-elf-gcc ({a})", __VERSION__);
    log("------------------------------------------------");
}


void kmain(MAYBE_UNUSED struct stivale2_struct *stivale2_struct)
{
    com_initialize(COM1);

    arch_initialize_descriptors();

    arch_initialize_memory(stivale2_struct);

    pit_initialize(1000);

    kernel_splash();

    log("Usable memory: {m}mb\t Usable pages: {i}", get_usable_pages() * PAGE_SIZE, get_usable_pages());

    log("CPU vendor: {a}", cpuid_get_vendor());
    
    acpi_initialize(stivale2_struct);
    apic_timer_initialize();

    while (true)
    {
        asm_hlt();
    }
}
