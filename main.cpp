#include "headers/imports.hpp"

float(__fastcall* oGetFireRateModifier)(UObject*);
float __fastcall GetFireRateModifier(UObject* pPlayerWeapon)
{
    if (globals::fire_rate)
        return globals::fire_rate_value;

    return oGetFireRateModifier(pPlayerWeapon);
}

float(__fastcall* oGetDamageMultiplier)(UObject*, UObject*);
float __fastcall GetDamageMultiplier(UObject* pPlayerCharacter, UObject* Weapon)
{
    if (globals::damage_modifier)
        return globals::damage_modifier_value;

    return oGetDamageMultiplier(pPlayerCharacter, Weapon);
}

void(__fastcall* oDrawTransition)(uint64_t, UCanvas*);
void __fastcall DrawTransition(uint64_t pGameViewport, UCanvas* pCanvas) // + 0x310
{
    oDrawTransition(pGameViewport, pCanvas);

    if (!GWorld.World)
        return;

    auto PersistentLevel = *(uint64_t*)(GWorld.World + 0x38);
    if (!PersistentLevel)
        return;

    auto OwningGameInstance = *(uint64_t*)(GWorld.World + 0x198);
    if (!OwningGameInstance)
        return;

    auto LocalPlayers = *(TArray<uint64_t>*)(OwningGameInstance + 0x38);
    auto LocalPlayer = LocalPlayers[0];
    if (!LocalPlayer)
        return;

    auto PlayerController = *(APlayerController**)(LocalPlayer + 0x30);
    if (!PlayerController)
        return;

    auto AcknowledgedPawn = *(uint64_t*)((uint64_t)PlayerController + 0x330);
    if (AcknowledgedPawn)
    {
        // Godmode/Demi Godmode
        if (globals::godmode)
        {
            auto HealthComponent = *(uint64_t*)(AcknowledgedPawn + 0x668);
            if (HealthComponent)
            {
                auto Health = *(float*)(HealthComponent + 0x2AC);

                if (globals::godmode_type == globals::EGodMode::Partial)
                {
                    if (Health < 9 / 2)
                    {
                        *(float*)(HealthComponent + 0x2AC) = 9;
                    }
                }
                else if (globals::godmode_type == globals::EGodMode::Full)
                {
                    *(float*)(HealthComponent + 0x2AC) = 9;
                }
            }
        }

        // Speed Multiplier
        if (globals::speed_multiplier)
        {
            *(float*)(AcknowledgedPawn + 0x620) = globals::speed_multiplier_value; // MovementSpeedMetaMultiplier
        }

        // Sprint Multiplier
        if (globals::sprint_multiplier)
        {
            *(float*)(AcknowledgedPawn + 0x624) = globals::sprint_multiplier_value; // SprintSpeedMetaMultiplier
        }

        // Omni Walk
        *(bool*)(AcknowledgedPawn + 0x2EE6A) = globals::omni_walk; // bRotationLocked

        // Gravity Scale
        if (globals::gravity_scale)
        {
            *(float*)(AcknowledgedPawn + 0x2EDE8) = globals::gravity_scale_value; // ActiveGravityScale
        }

        // Moon Walk
        *(bool*)(AcknowledgedPawn + 0xBE8) = globals::moon_walk; // bIsRevivingCharacter

        /*
        auto CurrentGun = *(uint64_t*)(AcknowledgedPawn + 0x1028);
        if (CurrentGun)
        {

        }
        */
    }

    auto Actors = *(TArray<uint64_t>*)(PersistentLevel + 0x98);

    for (int i = 0; i < Actors.Num(); i++)
    {
        if (!Actors.IsValidIndex(i)) continue;

        auto Actor = Actors[i];
        if (!Actor || Actor == AcknowledgedPawn) continue;

        auto RootComponent = *(uint64_t*)(Actor + 0x1C0);
        if (!RootComponent) continue;

        auto RelativeLocation = *(FVector*)(RootComponent + 0x1AC);
        auto ScreenLocation = PlayerController->ProjectWorldLocationToScreen(RelativeLocation);

        if (ScreenLocation.X && ScreenLocation.Y)
        {
            //pCanvas->K2_DrawLine({ 3440 / 2, 1440 }, ScreenLocation);

            auto ActorName = UKismetSystemLibrary::Instance()->GetObjectName((UObject*)Actor);
            auto ActorNameAsStr = ActorName.ToString();
            FLinearColor TextColor = FLinearColor{ 1.f, 1.f, 1.f, 1.f };

            if (ActorNameAsStr.find("BP_PlayerCharacter_C") != std::string::npos)
            {
                TextColor = FLinearColor{ 28.f / 255.f, 255.f / 255.f, 115.f / 255.f, 1.f };
                ActorName = L"Player";
            }
            else if (ActorNameAsStr.find("BP_AlienForestDoorMainPath_C") != std::string::npos)
            {
                TextColor = FLinearColor{ 28.f / 255.f, 225.f / 255.f, 255.f / 255.f, 1.f };
                ActorName = L"Main Path Door";
            }
            else if (ActorNameAsStr.find("BP_AlienForestDoorSecondaryPath_C") != std::string::npos)
            {
                TextColor = FLinearColor{ 28.f / 255.f, 165.f / 255.f, 255.f / 255.f, 1.f };
                ActorName = L"Secondary Path Door";
            }
            else if (ActorNameAsStr.find("BP_ForestChaserSmall_C") != std::string::npos)
            {
                TextColor = FLinearColor{ 255.f / 255.f, 255.f / 255.f, 0.f / 255.f, 1.f };
                ActorName = L"Chaser Small";
            }
            else if (ActorNameAsStr.find("BPEC_PopcornSmallDefaultFootstep_C") != std::string::npos)
            {
                TextColor = FLinearColor{ 255.f / 255.f, 255.f / 255.f, 0.f / 255.f, 1.f };
                ActorName = L"Popcorn Small";
            }
            else if (ActorNameAsStr.find("BP_AlienForestDoorLocked_C") != std::string::npos)
            {
                TextColor = FLinearColor{ 255.f / 255.f, 28.f / 255.f, 28.f / 255.f, 1.f };
                ActorName = L"Locked Door";
            }
            else if (ActorNameAsStr.find("BP_ColCur_Small_C") != std::string::npos)
            {
                TextColor = FLinearColor{ 195.f / 255.f, 255.f / 255.f, 35.f / 255.f, 1.f };
                ActorName = L"ColCur Coin";
            }
            else if (ActorNameAsStr.find("BP_PlayerCharacter_C") != std::string::npos)
            {
                TextColor = FLinearColor{ 200.f / 255.f, 30.f / 255.f, 255.f / 255.f, 1.f };
                ActorName = L"Player";
            }
            else if (ActorNameAsStr.find("BP_ForestTeleporter_C") != std::string::npos)
            {
                TextColor = FLinearColor{ 220.f / 255.f, 50.f / 255.f, 235.f / 255.f, 1.f };
                ActorName = L"Teleporter";
            }
            else
                continue;

            pCanvas->K2_DrawText(pFont, ActorName, ScreenLocation, TextColor);
        }
    }
}

BOOL DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return false;

    AllocConsole();
    FILE* fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);

    CoreBase = (uint64_t)GetModuleHandleA("Returnal-Core-Win64-Shipping.dll");
    if (!CoreBase)
        return false;

    printf("CoreBase: 0x%p\n", CoreBase);
    
    UObjectBase = (uint64_t)GetModuleHandleA("Returnal-CoreUObject-Win64-Shipping.dll");
    if (!UObjectBase)
        return false;

    printf("UObjectBase: 0x%p\n", UObjectBase);

    EngineBase = (uint64_t)GetModuleHandleA("Returnal-Engine-Win64-Shipping.dll");
    if (!EngineBase)
        return false;

    ReturnalBase = (uint64_t)GetModuleHandleA("Returnal-Returnal-Win64-Shipping.dll");
    if (!ReturnalBase)
        return false;

    printf("EngineBase: 0x%p\n", EngineBase);

    bool bNamePoolInitialized = *(bool*)(CoreBase + 0x5C2938); // C6 05 ? ? ? ? ? C5 F8 10 03
    if (!bNamePoolInitialized)
        return false;

    printf("bNamePoolInitialized: %i\n", bNamePoolInitialized);

    //auto NamePoolData = *(uint64_t*)(CoreBase + 0x5C2940); // 48 8D 05 ? ? ? ? EB ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? C5 F8 10 03
    //if (!NamePoolData)
    //    return false;

    //printf("NamePoolData: 0x%p\n", NamePoolData);

    auto GUObjectArray = *(FUObjectArray*)(UObjectBase + 0x2F6D18); // 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 48 83 C4 ? E9 ? ? ? ? 48 83 EC ? 48 8D 0D ? ? ? ? FF 15
    if (!GUObjectArray.ObjObjects.NumElements)
        return false;

    printf("GUObjectArray: 0x%p\n", GUObjectArray);

    GWorld = *(UWorldProxy*)(EngineBase + 0x15204F8); // 48 8B 05 ? ? ? ? 48 3B C3 48 0F 44 C6
    if (!GWorld.World)
        return false;

    printf("GUObjectArray: 0x%p\n", GWorld.World);

    auto GEngine = *(UEngine**)(EngineBase + 0x151CD68); // 48 8B 0D ? ? ? ? 48 8B D0 E8 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? 48 89 5C 24 70 48 8B 98 20 02 00 00 48 89 7C 24 78
    if (!GEngine)
        return false;

    printf("GEngine: 0x%p\n", GEngine);

    pFont = *(UObject**)(GEngine + 0x70); // MediumFont
    if (!pFont)
        return false;

    printf("pFont: 0x%p\n", pFont);

    auto OwningGameInstance = *(uint64_t*)(GWorld.World + 0x198);
    if (!OwningGameInstance)
        return false;

    printf("OwningGameInstance: 0x%p\n", OwningGameInstance);

    auto LocalPlayers = *(TArray<uint64_t>*)(OwningGameInstance + 0x38);
    auto LocalPlayer = LocalPlayers[0];
    if (!LocalPlayer)
        return false;

    printf("LocalPlayer: 0x%p\n", LocalPlayer);

    auto ViewportClient = *(uint64_t*)(LocalPlayer + 0x70);
    if (!ViewportClient)
        return false;

    printf("ViewportClient: 0x%p\n", ViewportClient);

    // Hook Functions
    oGetFireRateModifier = decltype(oGetFireRateModifier)(ReturnalBase + 0x71A8E0);
    oGetDamageMultiplier = decltype(oGetDamageMultiplier)(ReturnalBase + 0x3CD760);

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(LPVOID&)oGetFireRateModifier, (PVOID)GetFireRateModifier);
    DetourAttach(&(LPVOID&)oGetDamageMultiplier, (PVOID)GetDamageMultiplier);
    DetourTransactionCommit();

    //util::memory::vmt(ViewportClient, 0x61, PostRender, (void**)&oPostRender);
    util::memory::vmt(ViewportClient, 0x62, DrawTransition, (void**)&oDrawTransition);

    FreeConsole();

    return true;
}