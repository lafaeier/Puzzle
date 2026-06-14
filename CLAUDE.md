# CLAUDE.md

This file provides guidance to Claude Code when working in this repository.
**Claude is responsible for maintaining this file and all files under `docx/` — update them proactively as the project evolves to reflect current state, progress, constraints, and errors.**

---

## Project Identity

| Item | Detail |
|---|---|
| Game | First-person puzzle AVG (room escape) |
| Engine | Unreal Engine 5.7 |
| Module | `Puzzle` (single runtime module) |
| Platform | Windows |
| Controls | WASD move, mouse look, F interact, Tab inventory, Esc pause |

## Key Documentation (read when starting work)

| File | Content |
|---|---|
| `docx/项目开发章程与大纲.md` | **Authoritative** — architecture, dev phases, code↔scene connection points, test criteria |
| `docx/游戏策划文档.md` | Game design: worldview, art style, level flow |
| `docx/游戏详细流程.md` | Detailed interaction flow, data flow between systems |
| `docx/操作映射表.md` | Key bindings |
| `docx/项目计划书.md` | Timeline, milestones, team members |
| `docx/项目目录.md` | Target file/directory structure |
| `docx/错误记录与解法.md` | **Error log** — every error encountered, root cause, and fix. Read before debugging. |
| `docx/类设计文档.md` | Class designs with field lists, method pseudocode, and Java↔UE analogy |

## Build Commands

```bash
# Engine installed at: F:\UE\UE_5.7

# Editor target (daily development)
F:\UE\UE_5.7\Engine\Build\BatchFiles\Build.bat PuzzleEditor Win64 Development -Project="E:\subject\UE\Puzzle\Puzzle.uproject"

# Game target (packaging)
F:\UE\UE_5.7\Engine\Build\BatchFiles\Build.bat Puzzle Win64 Development -Project="E:\subject\UE\Puzzle\Puzzle.uproject"
```

No automated tests exist. Verify by PIE (Play In Editor) or manual testing.

---

## Reference: Existing Code Layout

### Base Layer (`Source/Puzzle/`)

| Class | UE Base | Purpose |
|---|---|---|
| `APuzzleCharacter` | `ACharacter` | Abstract first-person character. First-person mesh, camera. Binds jump/move/look via EnhancedInput. Virtual `DoAim`/`DoMove`/`DoJumpStart`/`DoJumpEnd`. |
| `APuzzlePlayerController` | `APlayerController` | Manages EnhancedInput mapping contexts. Spawns optional UMG touch controls. Forces `APuzzleCameraManager`. |
| `APuzzleGameMode` | `AGameModeBase` | Minimal stub. |
| `APuzzleCameraManager` | `APlayerCameraManager` | View pitch limits (-70° to +80°). |

### Shooter Variant (`Source/Puzzle/Variant_Shooter/`) — NOT part of this project

Unused template code: `AShooterCharacter`, `AShooterWeapon`, `AShooterProjectile`, `AShooterPickup`, `IShooterWeaponHolder`, AI subsystem (`AShooterNPC`, `AShooterAIController`, `AShooterNPCSpawner`), UI (`UShooterUI`, `UShooterBulletCounterUI`). **Do not modify or depend on these.**

### Horror Variant (`Source/Puzzle/Variant_Horror/`) — NOT part of this project

Unused template code: `AHorrorCharacter` (stamina sprint + spotlight), `UHorrorUI`. **Do not modify or depend on these.**

### Key Dependencies (from Build.cs)

`Core`, `CoreUObject`, `Engine`, `InputCore`, `EnhancedInput`, `AIModule`, `StateTreeModule`, `GameplayStateTreeModule`, `UMG`, `Slate`

---

## Target Code Structure (to be built)

```
Source/Puzzle/
├── Core/                        # Phase 1 — MUST build first
│   ├── RoomGameInstance.h/.cpp       # Cross-level persistent state (bHasKey, bCabinetOpened, etc.)
│   ├── RoomGameModeBase.h/.cpp       # Base GameMode
│   ├── RoomGameState.h/.cpp          # Game state
│   └── RoomSaveGame.h/.cpp           # Save/Load data
│
├── Character/                   # Phase 2
│   ├── RoomPlayerCharacter.h/.cpp    # F-key line trace → IInteractable dispatch, InventoryComponent ref
│   └── RoomPlayerController.h/.cpp   # Input mapping, UI management
│
├── Interaction/                 # Phase 3 — CORE gameplay
│   ├── IInteractable.h              # Pure virtual: Interact_Implementation(), GetInteractPrompt()
│   ├── InteractableActor.h/.cpp     # Base interactable
│   ├── PickupItem.h/.cpp            # Pickable item (key, bulb, note)
│   ├── StorageCabinet.h/.cpp        # Cabinet: open → spawn key → write GameInstance
│   ├── LightSocket.h/.cpp           # (side quest — defer)
│   └── PasswordDrawer.h/.cpp        # (side quest — defer)
│
├── Inventory/                   # Phase 2
│   └── InventoryComponent.h/.cpp    # ActorComponent, AddItem/RemoveItem/HasItem
│
├── Triggers/                    # Phase 4
│   └── DoorTrigger.h/.cpp           # Check GameInstance for key → OpenLevel or show hint
│
└── UI/                          # Phase 5+ (defer)
    ├── PasswordInputWidget.h/.cpp
    └── NoteTextWidget.h/.cpp
```

---

## Mandatory Development Order

**Do not skip phases. Each phase depends on the previous.**

| Phase | Deliverable | Acceptance Check | Status |
|---|---|---|---|---|
| 1 — Data | `URoomGameInstance`, `URoomSaveGame`, `ARoomGameModeBase` | GameInstance created at startup, state variables readable/writable via debug log | ✅ DONE (2026-06-14) |
| 2 — Character | `ARoomPlayerCharacter`, `ARoomPlayerController`, `UInventoryComponent`, `IInteractable` | WASD move, mouse look, F-key line trace hits objects (log hit actor name) | ← NEXT |
| 3 — Interaction | `AInteractableActor`, `APickupItem`, `AStorageCabinet` | Cabinet opens → key spawns → key pickable → GameInstance updated | Pending |
| 4 — Level Switch | `ADoorTrigger` | With key: OpenLevel to LivingRoom. Without key: hint text shown, no level switch | Pending |
| 5 — Scene | Blueprint subclasses + level layout | Full flow playable: bedroom explore → cabinet → key → door → living room | Pending |
| 6 — Side Quests | PasswordDrawer, LightSocket, UI widgets | Only if time allows | Pending |

---

## Code↔Scene Connection Points

Every C++ class bridges to the scene via Blueprint subclass → level actor placement:

1. **C++ defines** behavior + exposes `UPROPERTY(EditAnywhere)` config knobs
2. **Blueprint subclass** sets: mesh/model, material, UPROPERTY values, animation refs, sound cues
3. **Level (.umap)** places the Blueprint actor at a specific transform with specific collision setup

Key connection UPROPERTY examples:
- `AStorageCabinet::SpawnItemClass` → Blueprint sets to `BP_Item_Key`
- `AStorageCabinet::SpawnTransform` → Blueprint offsets relative to cabinet
- `ADoorTrigger::RequiredKeyID` → Blueprint sets to `"KeyToLivingRoom"`
- `ADoorTrigger::TargetLevel` → Blueprint sets to `"Level_LivingRoom"`
- `APickupItem::ItemID` / `ItemName` → Blueprint sets per item type

Complex logic lives in C++. Blueprints only handle visuals, parameter configuration, and simple event wiring.

---

## Constraints

### Code Constraints
- UE prefix rules: `A`=Actor, `U`=UObject/Component, `I`=Interface. File name drops prefix: `StorageCabinet.h` contains `AStorageCabinet`.
- Bool members start with `b`: `bOpened`, `bHasKey`.
- Every `UPROPERTY` must have a `Category = "xxx"` specifier.
- New `.h/.cpp` files → verify `Puzzle.Build.cs` has required module dependencies.
- Never manually edit `.generated.h` files (auto-generated by UHT).
- All puzzle state lives in `URoomGameInstance` — never store critical state in level actors that get destroyed on level transition.
- Interaction flow: `APlayerCharacter::OnInteract()` → LineTrace → `IInteractable::Interact_Implementation()`. Do not hardcode per-actor interaction logic in the character class.

### Scene/Asset Constraints
- `.uasset` and `.umap` are binary — two people editing the same file simultaneously = guaranteed conflict with no merge path.
- Each `.umap` level file is edited by exactly one person at a time.
- Blueprint classes do NOT contain core logic — only mesh assignment, UPROPERTY config, animation/sound wiring.
- Do not delete or rename existing Content assets from template variants unless explicitly instructed.

### Build Constraints
- Any `.h` change requires recompilation before the change takes effect in the editor.
- Compilation must pass before pushing. A broken build blocks the entire team.
- Do not add new module dependencies to `Build.cs` without confirming they are available in the engine install.

---

## Quality Checks (run before claiming any phase complete)

1. **Compilation**: `Build.bat PuzzleEditor Win64 Development` exits with zero errors.
2. **PIE smoke test**: Editor launches, level loads, character spawns, WASD/mouse work, no crash.
3. **Interaction trace**: F key line trace logs the name of the hit actor (verify via Output Log).
4. **GameInstance persistence**: Set a test bool in GameInstance during Bedroom → trigger level switch → verify bool survives in LivingRoom.
5. **Interaction idempotency**: Already-opened cabinet re-interacted → no duplicate key spawn, no state corruption.
6. **No-key door guard**: Trigger door without key → text hint displayed, level does NOT change.

---

## Version Control Rules

- `.gitignore` must exclude: `Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/`, `*.sln`, `*.suo`, `.vs/`, `.idea/`.
- `.gitattributes` must mark as binary (LFS): `*.uasset`, `*.umap`, `*.fbx`, `*.png`, `*.wav`.
- Commit granularity: one logical change per commit. Do not batch unrelated changes.
- Commit messages must describe **what resource was changed and why** — binary files have no readable diff.
- Before editing any `.uasset`, confirm via team communication that no one else has it locked.

---

## Claude's Responsibilities

- **Maintain this file** and all files under `docx/` — update them as the project evolves. Stale documentation is worse than no documentation.
- **Track progress** against the 6-phase development order. When a phase's acceptance checks pass, note it here.
- **Collect errors and constraints** encountered during development. If a non-obvious bug is fixed or a new constraint is discovered, add it to the Constraints section.
- **Before starting any task**, cross-reference `docx/项目开发章程与大纲.md` and this file to understand current state.
- **After completing any task**, update this file if: progress advanced, a new constraint was discovered, an error was fixed that has reuse value, or a file pointer needs updating.
