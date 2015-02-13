/*
  NESIZER
  Entry point 

  (c) Johan Fjeldtvedt

  Contains the main function, which sets up the various subsystems and transfers
  control to a task handler.
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/delay.h>
#include "task.h"
#include "apu.h"
#include "2a03_io.h"
#include "leds.h"
#include "lfo.h"
#include "envelope.h"
#include "timing.h"
#include "modulation.h"
#include "input.h"
#include "ui.h"
#include "memory.h"
#include "bus.h"
#include "patch.h"
#include "ui_sequencer.h"
#include "sample.h"
#include "midi.h"
#include "midi_io.h"
#include "portamento.h"

int main() 
{
    // Set up low level systems:
    bus_setup();
    io_setup();
    input_setup();
    memory_setup();
    timer_setup();
    midi_io_setup();

    // Set up APU channels:
    sq1_setup();
    sq2_setup();
    tri_setup();
    noise_setup();
    dmc_setup();

    patch_load(0);
    
    // Register task handlers:
    task_add(&apu_dmc_update_handler, 1);
    task_add(&midi_io_handler, 5);
    task_add(&apu_update_handler, 10);
    task_add(&lfo_update_handler, 10);
    task_add(&envelope_update_handler, 10);
    task_add(&portamento_handler, 10);
    task_add(&midi_handler, 10);
    task_add(&mod_calculate, 10);
    task_add(&mod_apply, 10);
    task_add(&leds_refresh, 20); // 20
    task_add(&input_refresh, 80);
    task_add(&sequence_handler, 80);
    task_add(&ui_handler, 80);
    task_add(&ui_leds_handler, 80);

    task_manager();
       
}
