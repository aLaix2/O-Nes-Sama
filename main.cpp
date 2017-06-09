#define SDL_MAIN_HANDLED
#define BENCH 0
//define DEBUGGER
#include <stdio.h>
#include "Cartridge/Cartridge.hpp"
#include "CPU.h"
#include "PPU.h"
#include <SDL2/SDL.h>
#include "Debugger/Debugger.h"

std::string getBaseRomName(std::string romFileName);

int main(){
/********************************************************/
/*                   Timing info                        */
/********************************************************/
    #if BENCH == 1
    Logger bench ("Bench.txt");
    #endif
    //Master clock of NES machine.
    int NTSCmasterclock = 21477272;
    //CPU Frequency in Hz
	int cpufreq = NTSCmasterclock / 12;
	//Synchronization freq
	int syncfreq = 60;
	double invsyncfreq = 1.0 / syncfreq;
	double delayFloat = invsyncfreq*1000.0;
	double countDelay = 0.;
    int underrun = 0;
    //Global cycle counter
    int cycles = invsyncfreq * cpufreq;
    int timediff = 0;
    int sleeptime = 0;
    int frameCtr = 0;

/********************************************************/
/*               Modules Declaration                    */
/********************************************************/

    /* ROM / Battery / Save State path names */
    //std::string romFileName   = "games/ppu_vbl_nmi/ppu_vbl_nmi.nes";
    //std::string romFileName   = "games/instr_test-v4/official_only.nes";

    //std::string romFileName   = "games/NROM/Baseball (USA, Europe).nes";
    //std::string romFileName   = "games/NROM/Balloon Fight.nes";
    //std::string romFileName   = "games/GxROM/Super Mario Bros. + Duck Hunt (USA).nes";
    //std::string romFileName   = "games/ColorDreams/Metal Fighter (USA) (Unl).nes";


    //std::string romFileName   = "games/blargg_ppu_tests/sprite_ram.nes";
    //std::string romFileName   = "games/mmc3_test_2/rom_singles/4-scanline_timing.nes";
    //std::string romFileName   = "games/NROM/smb.nes";
    //std::string romFileName   = "games/AxROM/Battletoads (USA).nes";

    //std::string romFileName   = "games/CNROM/Adventure Island.nes";
    //std::string romFileName   = "games/CNROM/Ninja Jajamaru Kun (Japan).nes";
    //std::string romFileName   = "games/CNROM/Urusei Yatsura - Lum no Wedding Bell (Japan).nes";
    //std::string romFileName   = "games/CNROM/AV Pachi Slot (Japan) (Unl).nes";
    //std::string romFileName   = "games/CNROM/Jajamaru no Daibouken (Japan).nes";
    //std::string romFileName   = "games/CNROM/Paperboy (USA).nes";

    //std::string romFileName   = "games/cpu_exec_space/test_cpu_exec_space_apu.nes";
    //std::string romFileName   = "games/cpu_exec_space/test_cpu_exec_space_ppuio.nes";

    //std::string romFileName   = "games/UxROM/Contra.nes";
    //std::string romFileName   = "games/instr_timing/instr_timing.nes";
    //std::string romFileName   = "games/MMC4/Fire Emblem Gaiden (Japan).nes";
    //std::string romFileName   = "games/MMC4/Fire Emblem (Japan).nes";
    //std::string romFileName   = "games/MMC2/Mike Tyson's Punch-Out!! (USA).nes";
    //std::string romFileName   = "games/MMC3/Tiny Toon Adventures (USA).nes";
    //std::string romFileName   = "games/MMC3/Crystalis (USA).nes";
    //std::string romFileName   = "games/blargg_ppu_tests/sprite_ram.nes";
    //std::string romFileName   = "games/MMC3/Mega Man 4 (USA).nes";
    //std::string romFileName   =  "games/branch_timing_tests/2.Backward_Branch.nes";
    //std::string romFileName   =  "games/cpu_timing_test6/cpu_timing_test.nes";

    //std::string romFileName   =  "games/nes-test-roms-master/cpu_dummy_reads/cpu_dummy_reads.nes";
    //std::string romFileName   =  "games/cpu_interrupts_v2/cpu_interrupts.nes";
    //std::string romFileName   =  "games/nes-test-roms-master/cpu_reset/ram_after_reset.nes";
    //std::string romFileName   =  "games/cpu_timing_test6/cpu_timing_test.nes";
    //std::string romFileName   =  "games/nes-test-roms-master/instr_misc/instr_misc.nes";
    //std::string romFileName   =  "games/nes-test-roms-master/nmi_sync/demo_ntsc.nes";
    //std::string romFileName   =  "games/nes-test-roms-master/scanline-a1/scanline.nes";
    //std::string romFileName   =  "games/nes-test-roms-master/window5/colorwin_ntsc.nes";
    //std::string romFileName   =  "games/MMC3/Ninja Gaiden Episode III - The Ancient Ship of Doom (USA).nes";
    //std::string romFileName   =  "games/MMC3/Super C (USA).nes";
    //std::string romFileName   =  "games/MMC3/Super Mario Bros. 3 (USA).nes";
    //std::string romFileName   =  "games/MMC3/Bart vs. the World (USA).nes";


    //std::string romFileName = "games/mmc3_test_2/rom_singles/4-scanline_timing.nes";

    //std::string romFileName   =  "games/Mapper225/64-in-1 (J).nes";
    //std::string romFileName   =  "games/MMC1/Super Mario Bros. + Duck Hunt + World Class Track Meet (USA).nes";

    //std::string romFileName   =  "games/CNROM/B-Wings (J).nes";
    //std::string romFileName   =  "games/NROM/Nim & Nom 24-11-16.nes";

    //std::string romFileName   =  "games/NROM/Kung Fu.nes";
    //std::string romFileName   =  "games/dpcmletterbox.nes";
    //std::string romFileName   =  "games/MMC3/Rollerblade Racer (USA).nes";
    //std::string romFileName   =  "games/MMC3/Startropics (USA).nes";
    //std::string romFileName   =  "games/MMC3/Mickey's Safari in Letterland (USA).nes";
    //std::string romFileName   =  "games/MMC3/Mickey's Adventure in Numberland (USA).nes";
    //std::string romFileName   =  "games/MMC3/Burai Fighter (USA).nes";
    //std::string romFileName   =  "games/MMC3/Incredible Crash Dummies, The (USA).nes";
    //std::string romFileName   =  "games/MMC3/G.I. Joe - A Real American Hero (USA).nes";
    //std::string romFileName   =  "games/MMC3/chuchu.nes";

    //std::string romFileName   = "games/MMC1/Mega Man 2 (U).nes";
    //std::string romFileName   = "games/MMC1/Bill & Ted's Excellent Video Game Adventure (USA).nes";
    //std::string romFileName   = "games/MMC3/Low G Man - The Low Gravity Man (U) [!].nes";



    //std::string romFileName   =  "games/MMC1/bart.nes";
    //std::string romFileName   =  "games/MMC1/Legend of Zelda, The (U).nes";
    //std::string romFileName   =  "games/MMC1/Metroid (USA).nes";
    //std::string romFileName   =  "games/MMC1/Dragon Warrior III (USA).nes";
    //std::string romFileName   =  "games/MMC1/Double Dragon (USA).nes";
    //std::string romFileName   =  "games/MMC1/Kid Icarus - Angel Land Story (USA, Europe).nes";
    //std::string romFileName   =  "games/MMC1/Dragon Warrior IV (USA).nes";
    //std::string romFileName   =  "games/MMC1/Genghis Khan (USA).nes";
    //std::string romFileName   =  "games/MMC1/Romance of the Three Kingdoms (USA).nes";
    //std::string romFileName   =  "games/MMC1/Final Fantasy I & II (Japan).nes";
    //std::string romFileName   =  "C:/Users/Federico Gimeno/Desktop/6502_1.2.11/Nes_Practice/nes_basics.nes";

    //std::string romFileName   =  "games/Camerica/Micro Machines (USA) (Unl).nes";
    //std::string romFileName   =  "games/Camerica/Fire Hawk (USA) (Unl).nes";
    //std::string romFileName   =  "games/Camerica/MiG 29 - Soviet Fighter (Camerica) [!].nes";

    //std::string romFileName   =  "games/MMC5/Laser Invasion (U) [!].nes";
    //std::string romFileName   =  "games/MMC5/Uncharted Waters (U) [!].nes";
    //std::string romFileName   =  "games/MMC5/Bandit Kings of Ancient China (U) [!].nes";
    //std::string romFileName   =  "games/MMC5/L'Empereur (J).nes";
    //std::string romFileName   =  "games/MMC5/Just Breed (J) [!].nes";

    //std::string romFileName   =  "games/MMC5/Castlevania III - Dracula's Curse (USA).nes";
    std::string romFileName   =  "games/MMC5/Shin 4 Nin Uchi Mahjong - Yakuman Tengoku (J) [!].nes";


    //std::string romFileName   =  "games/allpads/allpads.nes";
    //std::string romFileName   =  "games/MMC5/Metal Slader Glory (Japan).nes";
    //std::string romFileName   =  "games/MMC5/mmc5exram.nes";

    std::string saveStatePath = "SaveState";
    Cartridge cart(romFileName);
    saveStatePath.append(getBaseRomName(romFileName));
    saveStatePath.append(".sta");

    //printf("\nSave State path : %s", saveStatePath.c_str());

    /*Create the instances of the 6502 CPU, the Cartridge interface and the PPU*/
    CPU cpu (*cart.mapper);
    PPU ppu (cpu.io, *cart.mapper);
    cpu.setPPUPtr(&ppu);
    cpu.reset();
    ppu.reset();

    #ifdef DEBUGGER
        Debugger debuggerServer(&cpu, &ppu);
        debuggerServer.InitServer();
        //debuggerServer.InitAndWaitHandshake();
        //debuggerServer.handleRequests();
    #endif // DEBUGGER

    int pendCycles = 0;
    unsigned lastTimeTick = SDL_GetTicks();

    while (cpu.isRunning){
        #ifdef DEBUGGER
            if(!debuggerServer.connected)
            {
                if(debuggerServer.PollForDebugger())
                {
                    debuggerServer.handleRequests();
                }
            }
        #endif // DEBUGGER

        SDL_Event event;
        bool windowClosed = false;
        while(SDL_PollEvent(&event))
        {
            const uint8_t* state = SDL_GetKeyboardState(NULL);
            if(event.type == SDL_QUIT)
            {
                windowClosed = true;
            }
            if (state[SDL_SCANCODE_F7]){
                cpu.isPaused = !cpu.isPaused;
            }
            if (state[SDL_SCANCODE_F8]){
                cpu.reset();
                ppu.reset();
            }
            if (state[SDL_SCANCODE_F10]){
                FILE * file = fopen (saveStatePath.c_str(), "rb");
                if (file != NULL){
                    cart.mapper->loadState(file);
                    cpu.loadState(file);
                    ppu.loadState(file);
                    printf("\nLoaded state \"%s\"", saveStatePath.c_str());
                    fclose(file);
                } else {
                    printf("Error loading state file '%s'", saveStatePath.c_str());
                }
            }
            if (state[SDL_SCANCODE_F11]){
                FILE * file = fopen (saveStatePath.c_str(), "wb");
                if (file != NULL){
                    cart.mapper->saveState(file);
                    cpu.saveState(file);
                    ppu.saveState(file);
                    fclose(file);
                    printf("\nSaved state \"%s\"", saveStatePath.c_str());
                } else {
                    printf("Error creating state file '%s'", saveStatePath.c_str());
                }
            }
            if (state[SDL_SCANCODE_F2]){
                //cart.mapper->ppuStatus.debug = !cart.mapper->ppuStatus.debug;
            }
        }

        pendCycles = cpu.run(cycles + pendCycles);
        frameCtr ++;
        unsigned now = SDL_GetTicks();
        timediff = now - lastTimeTick;
        countDelay += delayFloat;
        int thisFrameTimeInMilis = countDelay;
        countDelay -= thisFrameTimeInMilis;
        sleeptime = thisFrameTimeInMilis - timediff;

        if (sleeptime > 0)
        {
            SDL_Delay(sleeptime);
        }
        else
            ++underrun;
        lastTimeTick = now + sleeptime;

        #if BENCH == 1
        //Benchmark to file
        bench.LogWithPrefix("Benchmark", "%d, %6lf, %d\n", underrun, timediff*100/thisFrameTimeInMilis, frameCtr);
        #endif
        if (windowClosed){
            cpu.isRunning = false;
            break;
        }
    }

    return 0;
}

/********************************************************/
/*                 Helper Functions                     */
/********************************************************/

std::string getBaseRomName(std::string tmpRomName){
    std::string fileNameBase;
    int extIndex = tmpRomName.find_last_of(".");
    tmpRomName.replace(tmpRomName.begin() + extIndex, tmpRomName.end(), "");
    int pathSepIndex = tmpRomName.find_last_of("/");
    tmpRomName.replace(tmpRomName.begin(), tmpRomName.begin() + pathSepIndex, "");
    fileNameBase = tmpRomName;
    return fileNameBase;
}
